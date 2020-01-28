#include <stdio.h>
#include <string.h>
#include <SmrFramework.h>

using namespace SmrFramework;

#define AM_IMMEDIATE         3
#define AM_MEMORY            4
#define AM_INDIRECT          5
#define AM_INDEXED           6
#define AM_INDIRECTINDEXED   7

typedef struct {
  String *name;
  Int32  value;
  UInt32 line;
  List<UInt32> *references;
  } LABEL;

List<LABEL*>  *labels;
List<String*> *tokens;
List<String*> *source;
int     pass;
int     address;
String  results;
int     errors;
Boolean showSymbolTable;
Boolean crossReference;
Boolean showMemoryMap;
int     lineNumber;
String  outputLine;
Boolean labelFound;
String  lastLabel;
Boolean dsectMode;
int     linesAssembled;
int     bytesAssembled;
int     startAddress;
Byte   *memory;
char   *memoryMap;
int     minAddress;
int     maxAddress;
Byte    opcodeAddress;
String  separators("!@#$%^&*()_+`'-=<>,./?[]{}\\| \t;:~");
Boolean showMmap;
Boolean showCref;
StreamWriter *outFile;
String        hexLine;

void init() {
  UInt32 i;
  memory = new Byte[256];
  memoryMap = new char[256];
  for (i=0; i<256; i++) {
    memory[i] = 0x00;
    memoryMap[i] = '.';
    }
  }

void error(char* msg) {
  if (pass == 2) {
    errors++;
    printf("%s\n",msg);
    }
  }

void sortLabels() {
  UInt32  i;
  LABEL  *temp;
  Boolean flag;
  flag = true;
  while (flag) {
    flag = false;
    for (i = 0; i < labels->Count()-1; i++) {
      if (labels->At(i)->name->CompareTo(labels->At(i+1)->name) > 0) {
        temp = labels->At(i);
        labels->AtPut(i, labels->At(i+1));
        labels->AtPut(i+1, temp);
        flag = true;
        }
      }
    }
  }

Boolean addLabel(String label, Int32 value) {
  UInt32 i;
  LABEL *newEntry;
  LABEL *entry;
  lastLabel = label;
  for (i=0; i<labels->Count(); i++) {
    entry = labels->At(i);
    if (label.ToUpper().Equals(entry->name->ToUpper())) {
      entry->value = value;
      labels->AtPut(i, entry);
      return true;
      }
    }
  newEntry = new LABEL;
  newEntry->name = new String(label);
  newEntry->value = value;
  newEntry->line = lineNumber;
  newEntry->references = new List<UInt32>();
  labels->Add(newEntry);
  return false;
  }

Int32 findLabel(String label) {
  UInt32 i;
  LABEL  *entry;
  labelFound = false;
  for (i=0; i<labels->Count(); i++) {
    entry = labels->At(i);
    if (label.ToUpper().Equals(entry->name->ToUpper())) {
      labelFound = true;
      if (pass == 2) {
        entry->references->Add(lineNumber);
        labels->AtPut(i,entry);
        }
      return entry->value;
      }
    }
  return -1;
  }


Boolean isHex(String *value) {
  return Tests::IsHex(value);
  }

Boolean isDecimal(String *value) {
  return Tests::IsNumeric(value);
  }

Boolean isOctal(String *value) {
  return Tests::IsOctal(value);
  }

Boolean isBinary(String *value) {
  return Tests::IsBinary(value);
  }

String* hexToDecimal(String *input) {
  UInt32 i;
  Int32 value;
  value = 0;
  for (i=0; i<input->Length(); i++) {
    if (input->CharAt(i) >= '0' && input->CharAt(i) <= '9') value = (value << 4) + input->CharAt(i) - '0';
    if (input->CharAt(i) >= 'A' && input->CharAt(i) <= 'F') value = (value << 4) + input->CharAt(i) - 'A' + 10;
    if (input->CharAt(i) >= 'a' && input->CharAt(i) <= 'f') value = (value << 4) + input->CharAt(i) - 'a' + 10;
    }
  return new String(Convert::ToString(value));
  }

String* octalToDecimal(String *input) {
  UInt32 i;
  Int32 value;
  value = 0;
  for (i=0; i<input->Length(); i++) {
    if (input->CharAt(i) >= '0' && input->CharAt(i) <= '7') value = (value << 3) + input->CharAt(i) - '0';
    }
  return new String(Convert::ToString(value));
  }

Byte hexToInt(String input) {
  UInt32 i;
  Int32  value;
  value = 0;
  for (i=0; i<input.Length(); i++) {
    if (input[i] >= '0' && input[i] <= '9') value = (value << 4) + input[i] - '0';
    if (input[i] >= 'A' && input[i] <= 'F') value = (value << 4) + input[i] - 'A' + 10;
    if (input[i] >= 'a' && input[i] <= 'f') value = (value << 4) + input[i] - 'a' + 10;
    }
  return (Byte)value;
  }

Int32 decimalToInt(String input) {
  UInt32 i;
  Int32 value;
  value = 0;
  for (i=0; i<input.Length(); i++) {
    if (input[i] >= '0' && input[i] <= '9') value = (value * 10) + (input[i] - '0');
    }
  return value;
  }

Int32 octalToInt(String input) {
  UInt32 i;
  Int32 value;
  value = 0;
  for (i=0; i<input.Length(); i++) {
    if (input[i] >= '0' && input[i] <= '7') value = (value << 3) + (input[i] - '0');
    }
  return value;
  }

String* binaryToDecimal(String *input) {
  UInt32 i;
  Int32 value;
  value = 0;
  for (i=0; i<input->Length(); i++) {
    if (input->CharAt(i) == '0') value = (value << 1) + 0;
    if (input->CharAt(i) == '1') value = (value << 1) + 1;
    }
  return new String(Convert::ToString(value));
  }

Boolean isLabel(String input) {
  UInt32 i;
  if (input.Length() < 1) return false;
  if (input.ToUpper().Equals("A")) return false;
  if (input.ToUpper().Equals("B")) return false;
  if (input.ToUpper().Equals("X")) return false;
  if (input.ToUpper().Equals("P")) return false;
  if (input.ToUpper().Equals("I")) return false;
  if (input.ToUpper().Equals("O")) return false;
  for (i=0; i<input.Length(); i++) {
    if (input[i] >= 'a' && input[i] <= 'z') return true;
    if (input[i] >= 'A' && input[i] <= 'Z') return true;
    if (input[i] == '_') return true;
    }
  return false;
  }


void writeByte(Byte value) {
  char tmp[20];
  sprintf(tmp," %02x",value);
  outputLine = outputLine + String(tmp);
   if (pass == 2) {
     if (hexLine.Length() < 1) {
//       hexLine = Convert::ToString(address,"X04") + String(":");
       sprintf(tmp,"%04x:",address);
       hexLine = String(tmp);
       }
//     hexLine = hexLine + String(" ") + Convert::ToString(value,"X02");
     sprintf(tmp," %02x",value);
     hexLine = hexLine + String(tmp);
     if (hexLine.Length() > 70) {
       outFile->WriteLine(hexLine);
       hexLine = String("");
       }
     memory[address] = value;
     memoryMap[address] = '*';
     bytesAssembled++;
     }
   address++;
   }

Byte convertValue(String *value) {
  Int32 v;
  if (value->Equals("A") || value->Equals("a")) return 0;
  if (value->Equals("B") || value->Equals("b")) return 1;
  if (value->Equals("X") || value->Equals("x")) return 2;
  if (value->Equals("P") || value->Equals("p")) return 3;
  if (value->Equals("I") || value->Equals("i")) return 0xff;
  if (value->Equals("O") || value->Equals("o")) return 0x80;
  if (isDecimal(value)) return (Byte)decimalToInt(value);
  if (isLabel(value)) {
    v = findLabel(value);
    if (v < 0) {
      if (pass == 2) error((char*)"Label not found");
      return 0xff;
      }
    return (Byte)(v & 0xff);
    }
  return 0xff;
  }

Byte getAddressingMode(int pos) {
  if (tokens->Count() <= pos) return 0xff;
  if (tokens->At(pos)->Equals("(")) {
    pos++;
    if (tokens->Count() <= pos) return 0xff;
      opcodeAddress = convertValue(tokens->At(pos));
      pos++;
      if (tokens->Count() <= pos) return 0xff;
      if (!tokens->At(pos)->Equals(")")) return 0xff;
      pos++;
      if (tokens->Count() <= pos) {
        return AM_INDIRECT;
        }
      if (tokens->Count() <= pos) return 0xff;
      if (!tokens->At(pos)->Equals(",")) return 0xff;
      pos++;
      if (tokens->Count() <= pos) return 0xff;
      if (!tokens->At(pos)->ToUpper().Equals("X")) return 0xff;
        return AM_INDIRECTINDEXED;
      }
    if (tokens->At(pos)->ToUpper().Equals("C")) {
      pos++;
      if (tokens->Count() <= pos) return 0xff;
      if (tokens->At(pos)->Equals("=")) {
        pos++;
        if (tokens->Count() <= pos) return 0xff;
        opcodeAddress = convertValue(tokens->At(pos));
        return AM_IMMEDIATE;
        }
        return 0xff;
      }
    opcodeAddress = convertValue(tokens->At(pos));
    pos++;
    if (tokens->Count() <= pos) {
      return AM_MEMORY;
      }
    if (!tokens->At(pos)->Equals(",")) return 0xff;
    pos++;
    if (!tokens->At(pos)->ToUpper().Equals("X")) return 0xff;
    return AM_INDEXED;
  }

void reduce() {
  int pos;
  pos = 0;
  while (pos < tokens->Count()) {
    if (tokens->At(pos)->Equals("$")) {
      if (isHex(tokens->At(pos+1))) {
        tokens->AtPut(pos+1, hexToDecimal(tokens->At(pos+1)));
        delete(tokens->At(pos));
        tokens->RemoveAt(pos);
        }
      else {
        if (pass == 2) error((char*)"Invalid hex constant");
        }
      }
    else if (tokens->At(pos)->Equals("%")) {
      if (isBinary(tokens->At(pos + 1))) {
        tokens->AtPut(pos + 1, binaryToDecimal(tokens->At(pos + 1)));
        delete(tokens->At(pos));
        tokens->RemoveAt(pos);
        }
      else {
        if (pass == 2) error((char*)"Invalid hex constant");
        }
      }
    else if (tokens->At(pos)->Equals("!")) {
      if (isOctal(tokens->At(pos + 1))) {
        tokens->AtPut(pos + 1, octalToDecimal(tokens->At(pos + 1)));
        delete(tokens->At(pos));
        tokens->RemoveAt(pos);
        }
      else {
        if (pass == 2) error((char*)"Invalid hex constant");
        }
      }
    else pos++;
    }
  }

void assembleType1(Byte opcode) {
  Byte mode;
  int pos;
  String tmp;
  pos = 2;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  tmp = tokens->At(2)->ToUpper();
  if (tmp.Equals("A")) opcode += 0x00;
  else if (tmp.Equals("B")) opcode += 0x40;
  else if (tmp.Equals("X")) opcode += 0x80;
  else {
    if (pass == 2) error((char*)"Missing register");
    return;
    }
  mode = getAddressingMode(pos+1);
  if (mode == 0xff) {
    if (pass == 2) error((char*)"Invalid addressing mode");
    return;
    }
  opcode += mode;
  writeByte(opcode);
  writeByte(opcodeAddress);
  }

void assembleType2(Byte opcode) {
  Byte mode;
  int pos;
  pos = 2;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  mode = getAddressingMode(pos);
  if (mode == 0xff) {
    if (pass == 2) error((char*)"Invalid addressing mode");
    return;
    }
  opcode += mode;
  writeByte(opcode);
  writeByte(opcodeAddress);
  }

void assembleShifts(Byte opcode) {
  Byte mode;
  int pos;
  String tmp;
  pos = 2;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
      return;
      }
  tmp = tokens->At(2)->ToUpper();
  if (tmp.Equals("A")) opcode += 0x00;
  else if (tmp.Equals("B")) opcode += 0x20;
  else {
    if (pass == 2) error((char*)"Missing register");
    return;
    }
  pos++;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Missing shift count");
    return;
    }
  mode = convertValue(tokens->At(pos));
  if (mode < 1 || mode > 4) {
    if (pass == 2) error((char*)"Invalid shift count");
    return;
    }
  if (mode == 4) mode = 0;
  opcode |= (Byte)(mode << 3);
  writeByte(opcode);
  }

void assembleSet(Byte opcode) {
  int pos;
  Byte mode;
  Byte addr;
  pos = 2;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  mode = convertValue(tokens->At(pos));
  if (mode < 0 || mode > 7) {
    if (pass == 2) error((char*)"Invalid bit position");
    return;
    }
  mode <<= 3;
  opcode |= mode;
  pos++;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  if (!tokens->At(pos)->Equals(",")) {
    if (pass == 2) error((char*)"Syntax error");
    return;
    }
  pos++;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  addr = convertValue(tokens->At(pos));
  writeByte(opcode);
  writeByte(addr);
  }

void assembleJumps(Byte opcode) {
  int pos;
  Byte reg;
  Byte mode;
  Byte addr;
  String tmp;
  pos = 2;
  if (tokens->Count() <= pos) {
    if (pass == 2) error((char*)"Incomplete line");
    return;
    }
  reg = 0xc0;
  mode = 0x03;
  tmp = tokens->At(pos)->ToUpper();
  if (tmp.Equals("A")) reg = 0x00;
  else if (tmp.Equals("B")) reg = 0x40;
  else if (tmp.Equals("X")) reg = 0x80;
  opcode |= reg;
  if (reg != 0xc0) {
    pos++;
    if (tokens->Count() <= pos) {
      if (pass == 2) error((char*)"Incomplete line");
      return;
      }
    tmp = tokens->At(pos)->ToUpper();
    if (tmp.Equals("NZ")) mode = 0x03;
    else if (tmp.Equals("Z")) mode = 0x04;
    else if (tmp.Equals("M")) mode = 0x05;
    else if (tmp.Equals("P")) mode = 0x06;
    else if (tmp.Equals("PNZ")) mode = 0x07;
    pos++;
    if (tokens->Count() <= pos) {
      if (pass == 2) error((char*)"Incomplete line");
      return;
      }
    if (!tokens->At(pos)->Equals(",")) {
      if (pass == 2) error((char*)"Syntax error");
      return;
      }
    pos++;
    if (tokens->Count() <= pos) {
      if (pass == 2) error((char*)"Incomplete line");
      return;
      }
    }
  if ((opcode & 0x08) != 0) {
    if (!tokens->At(pos)->Equals("(")) {
      if (pass == 2) error((char*)"Indirect jump requires indirect address");
      return;
      }
    pos++;
    if (tokens->Count() <= pos) {
      if (pass == 2) error((char*)"Syntax error");
      return;
      }
    addr = convertValue(tokens->At(pos));
    pos++;
    if (!tokens->At(pos)->Equals(")")) {
      if (pass == 2) error((char*)"Syntax error");
      return;
      }
    }
  else {
    if (tokens->At(pos)->Equals("(")) {
      if (pass == 2) error((char*)"Direct jump requires a direct address");
      return;
      }
    addr = convertValue(tokens->At(pos));
    }
  opcode |= mode;
  writeByte(opcode);
  writeByte(addr);
  }

void assembleData() {
  if (tokens->Count() <= 2) {
    if (pass == 2) error((char*)"Invalid format for DATA");
    return;
    }
  writeByte(convertValue(tokens->At(2)));
  }

void assembleOrg() {
  if (tokens->Count() <= 2) {
    if (pass == 2) error((char*)"Invalid format for ORG");
    return;
    }
  address = (convertValue(tokens->At(2)) & 0xff);
  if (pass == 2 && hexLine.Length() > 0) {
    outFile->WriteLine(hexLine);
    hexLine = String("");
    }
  }

void assembleStart() {
  char temp[64];
  if (tokens->Count() <= 2) {
    if (pass == 2) error((char*)"Invalid format for ORG");
    return;
    }
  memory[3] = (Byte)(convertValue(tokens->At(2)) & 0xff);
  if (pass == 2) {
    if (hexLine.Length() > 0) {
      outFile->WriteLine(hexLine);
      hexLine = String("");
      }
    sprintf(temp,"0003: %02x",memory[3]);
    outFile->WriteLine(temp);
    }
  }


void tokenize(String input) {
  String current;
  tokens = new List<String*>();
  if (input.Length() < 1) return;
  if (input[0] == 32 || input[0] == 9) {
    tokens->Add(new String(""));
    }
  input = input.Trim();
  current = String("");
  while (input.Length() > 0) {
    if (separators.IndexOf(input[0]) >= 0) {
      if (current.Length() > 0) {
        tokens->Add(new String(current));
        current = String("");
        }
      if (input[0] == ';') {
        input = String(" ");
        }
      else if (input[0] != ' ' && input[0] != '\t')
        tokens->Add(new String(input.Substring(0,1)));
      }
    else {
      current = current + input.Substring(0,1);
      }
    input = input.Substring(1);
    }
  if (current.Length() > 0) tokens->Add(new String(current));
  }

void assembleLine(String line) {
  String label;
  String opcode;
  Boolean result;
  char    buffer[64];
  linesAssembled++;
  sprintf(buffer,"%4d [%02x] ",lineNumber,address);
  outputLine = String(buffer);
  tokenize(line);
  reduce();
  if (tokens->Count() < 1) return;
  if (tokens->At(0)->Length() > 0) {
    label = String(tokens->At(0));
    result = addLabel(label, address);
    if (pass == 1 && result) {
      errors++;
      printf("Error: Line %d Multiply defined label: %s\n",lineNumber, label.AsCharArray());
      }
    }
  if (tokens->Count() < 2) return;
    opcode = tokens->At(1)->ToUpper();
    if (opcode.ToUpper().Equals("ADD")) assembleType1(0x00);
    else if (opcode.Equals("SUB")) assembleType1(0x08);
    else if (opcode.Equals("LOAD")) assembleType1(0x10);
    else if (opcode.Equals("STORE")) assembleType1(0x18);
    else if (opcode.Equals("AND")) assembleType2(0xd0);
    else if (opcode.Equals("OR")) assembleType2(0xc0);
    else if (opcode.Equals("LNEG")) assembleType2(0xd8);
    else if (opcode.Equals("SFTL")) assembleShifts(0x81);
    else if (opcode.Equals("SFTR")) assembleShifts(0x01);
    else if (opcode.Equals("ROTL")) assembleShifts(0xc1);
    else if (opcode.Equals("ROTR")) assembleShifts(0x41);
    else if (opcode.Equals("SET0")) assembleSet(0x02);
    else if (opcode.Equals("SET1")) assembleSet(0x42);
    else if (opcode.Equals("SKP0")) assembleSet(0x82);
    else if (opcode.Equals("SKP1")) assembleSet(0xc2);
    else if (opcode.Equals("JPD")) assembleJumps(0x20);
    else if (opcode.Equals("JPI")) assembleJumps(0x28);
    else if (opcode.Equals("JMD")) assembleJumps(0x30);
    else if (opcode.Equals("JMI")) assembleJumps(0x38);
    else if (opcode.Equals("NOOP")) writeByte(0x80);
    else if (opcode.Equals("HALT")) writeByte(0x00);
    else if (opcode.Equals("DATA")) assembleData();
    else if (opcode.Equals("ORG")) assembleOrg();
    else if (opcode.Equals("END")) assembleStart();
    if (pass == 2) {
      while (outputLine.Length() < 20) outputLine = outputLine + String(" ");
      printf("%s%s\n",outputLine.AsCharArray(), line.AsCharArray());
    }
  }

String* expandTabs(String *input) {
  UInt32 i;
  UInt32 l;
  char line[1024];
  char c;
  String ret;
  strcpy(line,"");
  ret = String("");
  for (i=0; i<input->Length(); i++) {
    c = input->CharAt(i);
    if (c == 9) {
      strcat(line, " ");
      while (strlen(line) % 8 != 0) strcat(line, " ");
      }
    else {
       l = strlen(line);
       line[l++] = c;
       line[l] = 0;
       }
    }
  return new String(line);
  }

void assemblyPass(int n, List<String*> *lines) {
  UInt32 i;
  String* line;
  pass = n;
  address = 0;
  lineNumber = 0;
  linesAssembled = 0;
  bytesAssembled = 0;
  printf("Pass %d:\n", pass);
  hexLine = String("");
  for (i=0; i<lines->Count(); i++) {
    lineNumber++;
    line = expandTabs(lines->At(i));
    assembleLine(line);
    delete(line);
    }
  if (pass == 2) {
    if (hexLine.Length() > 0) outFile->WriteLine(hexLine);
    }
  }

void Assemble(List<String*> *lines) {
  UInt32 i;
  UInt32 j;
  LABEL *label;
  init();
  errors = 0;
  startAddress = 0x0000;
  labels = new List<LABEL*>();
  assemblyPass(1, lines);
  assemblyPass(2, lines);
  printf("\n");
  
  if (showMmap) {
    for (i=0; i<256; i++) {
      if (i % 16 == 0) printf("\n%02x: ",i);
      else if (i % 8 == 0) printf(" ");
      printf("%c",memoryMap[i]);
      }
    printf("\n\n");
    }

  if (showCref) {
    for (i=0; i<labels->Count(); i++) {
      label = labels->At(i);
      printf("%-20s  <%02x>  ", label->name->AsCharArray(),
                             label->value);
      for (j=0; j<label->references->Count(); j++)
        printf(" %d",label->references->At(j));
      printf("\n");
      }
    }

  printf("\n");

  printf("Lines Assembled: %d\n", linesAssembled);
  printf("Bytes Assembled: %d\n", bytesAssembled);
  printf("Errors         : %d\n", errors);
  }

int main(int argc, char** argv) {
  UInt32 i;
  Int32 fpos;
  String line;
  StreamReader *file;
  String        inName;
  String        outName;
  fpos = -1;
  showMmap = false;
  showCref = false;
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i],"-m") == 0) showMmap = true;
    else if (strcmp(argv[i],"-c") == 0) showCref = true;
    else fpos = i;
    }
  if (fpos < 0) {
    printf("Usage: asm {options} source-file\n");
    exit(1);
    }
  inName = String(argv[fpos]);
  if (!File::Exists(inName)) {
    inName = inName + String(".asm");
    }
  if (!File::Exists(inName)) {
    printf("Source file does not exist.\n");
    exit(1);
    }
  file = new StreamReader(inName);
  if (file == NULL) {
    printf("Could not open source file.\n");
    exit(1);
    }
  source = new List<String*>();
  while (!file->EndOfStream()) {
    line = file->ReadLine();
    source->Add(new String(line));
    }
  delete(file);
  outName = File::Basename(inName) + String(".hex");
  outFile = new StreamWriter(outName);
  Assemble(source);
  delete(outFile);
  return 0;
  }

