#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <SmrFramework.h>
#include <SmrAppFramework.h>

using namespace SmrFramework;

#include "cpu.h"

class MainWindow : public Form {
  protected:
    Cpu *cpu;
    Button *dataButton0;
    Button *dataButton1;
    Button *dataButton2;
    Button *dataButton3;
    Button *dataButton4;
    Button *dataButton5;
    Button *dataButton6;
    Button *dataButton7;
    Button *clearButton;
    Button *displayAddressButton;
    Button *setAddressButton;
    Button *readMemoryButton;
    Button *writeMemoryButton;
    Button *startButton;
    Button *stopButton;
    Panel  *dataLamp0;
    Panel  *dataLamp1;
    Panel  *dataLamp2;
    Panel  *dataLamp3;
    Panel  *dataLamp4;
    Panel  *dataLamp5;
    Panel  *dataLamp6;
    Panel  *dataLamp7;
    Panel  *inputLamp;
    Panel  *addressLamp;
    Panel  *memoryLamp;
    Panel  *runLamp;
    Timer  *timer;
    Byte    dataLamps;
    Byte    statLamps;
    void InitializeComponent();
    void ClearButtonPressed(void* sender, MouseEventArgs args);
    void DataButtonPressed(void* sender, MouseEventArgs args);
    void DisplayAddressButtonPressed(void* sender, MouseEventArgs args);
    void ReadMemoryButtonPressed(void* sender, MouseEventArgs args);
    void SetAddressButtonPressed(void* sender, MouseEventArgs args);
    void StoreMemoryButtonPressed(void* sender, MouseEventArgs args);
    void StartButtonPressed(void* sender, MouseEventArgs args);
    void StopButtonPressed(void* sender, MouseEventArgs args);
    void TimerTick(void* sender);
    void static _ClearButtonPressed(void* obj, void* sender, EventArgs args);
    void static _DataButtonPressed(void* obj, void* sender, EventArgs args);
    void static _DisplayAddressButtonPressed(void* obj, void* sender, EventArgs args);
    void static _ReadMemoryButtonPressed(void* obj, void* sender, EventArgs args);
    void static _SetAddressButtonPressed(void* obj, void* sender, EventArgs args);
    void static _StartButtonPressed(void* obj, void* sender, EventArgs args);
    void static _StopButtonPressed(void* obj, void* sender, EventArgs args);
    void static _StoreMemoryButtonPressed(void* obj, void* sender, EventArgs args);
    void static _TimerTick(void* obj, void* sender, EventArgs args);

  public:
    MainWindow(Cpu* c, int w, int h);
    ~MainWindow();
  };

#endif
