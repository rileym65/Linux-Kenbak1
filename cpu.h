#ifndef _CPU_H
#define _CPU_H

#include <SmrFramework.h>

using namespace SmrFramework;

#define LAMPS_NONE      0
#define LAMPS_INPUT     1
#define LAMPS_ADDRESS   2
#define LAMPS_MEMORY    3
#define LAMPS_RUN       4
#define REG_A           0
#define REG_B           1
#define REG_X           2
#define REG_P           3
#define REG_OUT      0x80
#define REG_AF       0x81
#define REG_BF       0x82
#define REG_XF       0x83
#define REG_IN       0xff

class Cpu : public Thread {
  protected:
    Byte inst;
    Byte reg; 
    Byte mode;
    Byte middle;
    Boolean debugMode;
    char* addressToString(Byte mode, Byte ea);
    void clearMem();
    void doGroup1(Byte ea);
    void doGroup2(Byte ea);
    void doHalt();
    void doJump();
    void doNop();
    void doSet();
    void doShift();
    void doSkip();
    Byte fetch();
    char* regToString(Byte reg);
    virtual void execute(void* arg);
  public:
    Byte *memory;
    Boolean running;
    Boolean powered;
    int lampMode;
    Byte addressRegister;
    Byte memoryValue;
    Cpu();
    ~Cpu();
    void Cycle();
    void ClearButton();
    void DataButton(Byte b);
    void DebugMode(Boolean b);
    void DisplayAddressButton();
    void SetAddressButton();
    void MemoryReadButton();
    void MemoryWriteButton();
    void StartButton();
    void StopButton();
    Byte Lamps();
    Byte LampMode();
  };


#endif

