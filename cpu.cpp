#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cpu.h"

Cpu::Cpu() : Thread() {
  memory = new Byte[256];
  running = false;
  powered = true;
  lampMode = LAMPS_INPUT;
  addressRegister = 0;
  debugMode = 0;
  }

Cpu::~Cpu() {
  delete memory;
  }

void Cpu::clearMem() {
  UInt32 i;
  for (i = 0; i < 256; i++) memory[i] = 0;
  }

char* Cpu::regToString(Byte reg) {
  static char buffer[3];
  strcpy(buffer,"");
  if (reg == 0) strcpy(buffer, "A");
  if (reg == 1) strcpy(buffer, "B");
  if (reg == 2) strcpy(buffer, "X");
  return buffer;
  }

char* Cpu::addressToString(Byte mode, Byte ea) {
  static char buffer[64];
  strcpy(buffer,"");
  switch (mode) {
    case 3: sprintf(buffer, "C=$%02x", memory[ea]); break;
    case 4: sprintf(buffer, "$%02x", ea); break;
    case 5: sprintf(buffer, "($%02x)", ea); break;
    case 6: sprintf(buffer, "$%02x,X", ea); break;
    case 7: sprintf(buffer, "($%02x),X", ea); break;
    }
  return buffer;
  }

void Cpu::doJump() {
  Byte ea;
  Byte value;
  Boolean jump;
  char    buffer[64];
  jump = false;
  ea = memory[(memory[REG_P]+1) & 0xff];
  if (debugMode) {
    printf("%s", (((inst & 0x10) == 0) ? "JP" : "JM"));
    printf("%s", (((inst & 0x08) == 0) ? "D " : "I "));
    switch (inst & 0xc0) {
      case 0x00: printf("A"); break;
      case 0x40: printf("B"); break;
      case 0x80: printf("X"); break;
      }
    printf(" ");
    if ((inst & 0xc0) != 0xc0) {
      switch (inst & 0x07) {
        case 0x03: printf("NZ,"); break;
        case 0x04: printf("Z,"); break;
        case 0x05: printf("M,"); break;
        case 0x06: printf("P,"); break;
        case 0x07: printf("PNZ,"); break;
        }
      }
    if ((inst & 0x08) == 0x00) printf("%02x",ea);
      else printf("(%02x)",ea);
    }
  if ((inst & 0x08) != 0) ea = memory[ea];
  if (reg == 3) jump = true;                                   // unconditional
  else {
    switch (reg) {
      case 0: value = memory[REG_A]; break;
      case 1: value = memory[REG_B]; break;
      case 2: value = memory[REG_X]; break;
      default: value = 0; break;
      }
    switch (mode) {
       case 3:
           if (value != 0) jump = true;
           break;
       case 4:
           if (value == 0) jump = true;
           break;
       case 5:
           if (value >= 0x80) jump = true;
           break;
       case 6:
           if (value < 0x80) jump = true;
           break;
       case 7: if (value > 0 && value < 0x80) jump = true;
           break;
       }
    }
  if (jump) {
    if ((inst & 0x10) != 0) {
      memory[ea] = (memory[REG_P] + 2) & 0xff;
      memory[REG_P] = (Byte)(ea+1);
      }
    else {
      memory[REG_P] = ea;
      }
    }
  else memory[REG_P] += 2;
  }

void Cpu::doHalt() {
  running = false;
  lampMode = LAMPS_NONE;
  if (debugMode) printf("HALT");
  memory[REG_P]++;
  }

void Cpu::doNop() {
  if (debugMode) printf("NOP");
  memory[REG_P]++;
  }

void Cpu::doShift() {
  UInt32 i;
  int count;
  Byte bit;
  count = (inst >> 3) & 0x3;
  if (count == 0) count = 4;
  reg = (Byte)((inst >> 5) & 1);
  if (debugMode) {
    printf("%s", (((inst & 0x40) != 0) ? "ROT" : "SFT"));
    printf("%s", (((inst & 0x80) != 0) ? "L" : "R"));
    printf(" %s,%d",regToString(reg),count);
    }
  if ((inst & 0x80) == 0) {                         // Right
    for (i = 0; i < count; i++) {
      bit = (Byte)((memory[reg] & 1) << 7);
      memory[reg] = (Byte)((memory[reg] >> 1) & 0x7f);
      if ((inst & 0x40) == 0x00) {              // Shift
        memory[reg] |= (Byte)((memory[reg] << 1) & 0x80);
        }
      else {                                    // Rotate
        memory[reg] |= bit;
        }
      }
    }
  else {                                            // Left
    for (i = 0; i < count; i++) {
      bit = (Byte)((memory[reg] & 0x80) >> 7);
      memory[reg] = (Byte)((memory[reg] << 1) & 0xfe);
      if ((inst & 0x40) == 0x00) {              // Shift
        }
      else {                                    // Rotate
        memory[reg] |= bit;
        }
      }
    }
  memory[REG_P]++;
  }

void Cpu::doSkip() {
  Byte mask;
  Byte value;
  Byte ea;
  if (debugMode) {
    printf("SKP%s",(((reg & 1) == 1) ? "1" : "0"));
    printf(" %d,%s",middle,addressToString(4,memory[(memory[REG_P]+1)&0xff]));
    }
  ea = memory[(memory[REG_P]+1) & 0xff];
  mask = (Byte)(1 << middle);
  value = memory[ea] & mask;
  if ((reg & 1) == 0) {
    if (value == 0) memory[REG_P] += 4;
      else memory[REG_P] += 2;
    }
  if ((reg & 1) == 1) {
    if (value != 0) memory[REG_P] += 4;
      else memory[REG_P] += 2;
    }
  }

void Cpu::doSet() {
  Byte mask;
  Byte value;
  Byte ea;
  mask = (Byte)(1 << middle);
  ea = memory[(memory[REG_P]+1) & 0xff];
  if (debugMode) {
    printf("SET%s", (((reg & 1) == 1) ? "1" : "0"));
    printf(" %d,%s",middle,addressToString(4,ea));
    }
  value = memory[ea];
  if ((reg & 1) == 1) value |= mask;
  else value &= (Byte)(~mask);
  memory[ea] = value;
  memory[REG_P] += 2;
  }

void Cpu::doGroup1(Byte ea) {
  Byte a, b;
  int temp;
  switch (middle) {
    case 0:                                      // ADD
         if (debugMode)
           printf("ADD %s %s",regToString(reg),addressToString(mode, ea));
         a = memory[reg];
         b = memory[ea];
         temp = a + b;
         memory[reg] = (Byte)(temp);
         memory[REG_AF + reg] = 0x00;
         if (temp > 0xff) memory[REG_AF + reg] |= 2;
         if ((a & 0x80) == (b & 0x80)) {
           if ((temp & 0x80) != (a & 0x80)) memory[REG_AF + reg] |= 1;
           }
         break;
    case 1:                                      // SUB
         if (debugMode)
           printf("SUB %s %s",regToString(reg),addressToString(mode, ea));
         a = memory[reg];
         b = (Byte)(~memory[ea] + 1);
         temp = a + b;
         memory[reg] = (Byte)(temp);
         memory[REG_AF + reg] = 0x00;
         if (temp > 0xff) memory[REG_AF + reg] |= 2;
         if ((a & 0x80) == (b & 0x80)) {
           if ((temp & 0x80) != (a & 0x80)) memory[REG_AF + reg] |= 1;
           }
         memory[REG_AF + reg] ^= 2;
         break;
    case 2:                                      // LOAD
         if (debugMode)
           printf("LOAD %s %s",regToString(reg), addressToString(mode, ea));
         memory[reg] = memory[ea];
         break;
    case 3:                                      // STORE
         if (debugMode)
           printf("STORE %s %s",regToString(reg), addressToString(mode, ea));
         memory[ea] = memory[reg];
         break;
    }
  memory[REG_P] += 2;
  }

void Cpu::doGroup2(Byte ea) {
  switch (middle) {
    case 0:                                      // OR
         if (debugMode)
           printf("OR %s",addressToString(mode, ea));
         memory[REG_A] |= memory[ea];
         break;
    case 2:                                      // AND
         if (debugMode)
           printf("AND %s",addressToString(mode, ea));
         memory[REG_A] &= memory[ea];
         break;
    case 3:                                      // LNEG
         if (debugMode)
           printf("LNEG %s",addressToString(mode, ea));
         memory[REG_A] = (Byte)(~memory[ea] + 1);
         break;
    }
  memory[REG_P] += 2;
  }

void Cpu::Cycle() {
  Byte ea;
  char buffer[64];
  if (!powered) return;
  if (!running) return;
  if (debugMode) {
    printf("[%02x] ",memory[REG_P]);
    }
  inst = memory[memory[REG_P]];
  if (debugMode) {
    printf("%02x ",inst);
    }
  reg = (Byte)((inst >> 6) & 0x3);
  mode = (Byte)(inst & 0x7);
  middle = (Byte)((inst >> 3) & 0x7);
  if (middle >= 4 && mode >= 3) doJump();
  else switch (mode) {
    case 0: if (reg > 1) doNop(); else doHalt();
        break;
    case 1: doShift();
        break;
    case 2: if (reg > 1) doSkip(); else doSet();
        break;
    case 3:
        ea = (memory[REG_P] + 1) & 0xff;
        if (reg != 3) doGroup1(ea); else doGroup2(ea);
        break;
    case 4:
        ea = memory[(memory[REG_P]+1) & 0xff];
        if (reg != 3) doGroup1(ea); else doGroup2(ea);
        break;
    case 5:
        ea = memory[(memory[REG_P]+1) & 0xff];
        ea = memory[ea];
        if (reg != 3) doGroup1(ea); else doGroup2(ea);
        break;
    case 6:
        ea = memory[(memory[REG_P]+1) & 0xff];
        ea = (ea + memory[REG_X]) & 0xff;
        if (reg != 3) doGroup1(ea); else doGroup2(ea);
        break;
    case 7:
        ea = memory[(memory[REG_P]+1) & 0xff];
        ea = (memory[ea] + memory[REG_X]) & 0xff;
        if (reg != 3) doGroup1(ea); else doGroup2(ea);
        break;
    }
  if (debugMode) printf("\n");
  }

void Cpu::DataButton(Byte b) {
  memory[0xff] |= b;
  if (!running) lampMode = LAMPS_INPUT;
  }

void Cpu::ClearButton() {
  memory[0xff] = 0;
  if (!running) lampMode = LAMPS_INPUT;
  }

void Cpu::DisplayAddressButton() {
  if (!running) lampMode = LAMPS_ADDRESS;
  }

void Cpu::SetAddressButton() {
  addressRegister = memory[0xff];
  if (!running) lampMode = LAMPS_ADDRESS;
  }

void Cpu::MemoryReadButton() {
  if (!running) {
    lampMode = LAMPS_MEMORY;
    memoryValue = memory[addressRegister++];
    }
  }

void Cpu::MemoryWriteButton() {
  if (!running) {
    memory[addressRegister] = memory[0xff];
    addressRegister++;
    }
  }

void Cpu::StartButton() {
  running = true;
  lampMode = LAMPS_RUN;
  }

void Cpu::StopButton() {
  running = false;
  lampMode = LAMPS_NONE;
  }

Byte Cpu::Lamps() {
  switch (lampMode) {
    case LAMPS_NONE: return memory[0x80];
    case LAMPS_INPUT: return memory[0xff];
    case LAMPS_ADDRESS: return addressRegister;
    case LAMPS_MEMORY: return memoryValue;
    case LAMPS_RUN: return memory[0x80];
    }
  return memory[0x80];
  }

Byte Cpu::LampMode() {
  return lampMode;
  }

void Cpu::execute(void* arg) {
  HrTimer timer;
  timer.Restart();
  while (!terminate) {
    while (timer.Microseconds() < 1000) {
      usleep(100);
      }
    timer.Restart();
    Cycle();
    }
  }

void Cpu::DebugMode(Boolean b) {
  debugMode = b;
  }

void Cpu::Load(char* filename) {
  UInt32        i;
  char          c;
  Byte          address;
  Byte          value;
  Boolean       valid;
  StreamReader *file;
  String        line;
  if (!File::Exists(filename)) {
    printf("File %s does not exist\n",filename);
    return;
    }
  file = new StreamReader(filename);
  address = 0;
  value = 0;
  valid = false;
  while (!file->EndOfStream()) {
    line = file->ReadLine().ToUpper().Trim();
    for (i=0; i<line.Length(); i++) {
      c = line.CharAt(i);
      if (c >= '0' && c <= '9') {
        value = (value << 4) | (c - '0');
        valid = true;
        }
      if (c >= 'A' && c <= 'F') {
        value = (value << 4) | (c - 'A' + 10);
        valid = true;
        }
      if (c == ':') {
        address = value;
        value = 0;
        valid = false;
        }
      if (c == ' ' && valid) {
        memory[address++] = value;
        value = 0;
        valid = false;
        }
      }
    if (valid) {
      memory[address++] = value;
      value = 0;
      valid = false;
      }
    }
  delete(file);
  }

