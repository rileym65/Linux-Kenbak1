#include <stdio.h>
#include "MainWindow.h"
#include "header.h"
#include "cpu.h"

MainWindow::MainWindow(Cpu* c, int w, int h) : Form(NULL, 0, 0, w, h) {
  cpu = c;
  dataLamps = 0;
  statLamps = 0;
  InitializeComponent();
  }

MainWindow::~MainWindow() {
  }

void MainWindow::ClearButtonPressed(void* sender, MouseEventArgs args) {
  cpu->ClearButton();
  }

void MainWindow::DataButtonPressed(void* sender, MouseEventArgs args) {
  if (sender == dataButton7) cpu->DataButton(128);
  if (sender == dataButton6) cpu->DataButton(64);
  if (sender == dataButton5) cpu->DataButton(32);
  if (sender == dataButton4) cpu->DataButton(16);
  if (sender == dataButton3) cpu->DataButton(8);
  if (sender == dataButton2) cpu->DataButton(4);
  if (sender == dataButton1) cpu->DataButton(2);
  if (sender == dataButton0) cpu->DataButton(1);
  }

void MainWindow::DisplayAddressButtonPressed(void* sender, MouseEventArgs args) {
  cpu->DisplayAddressButton();
  }

void MainWindow::ReadMemoryButtonPressed(void* sender, MouseEventArgs args) {
  cpu->MemoryReadButton();
  }

void MainWindow::SetAddressButtonPressed(void* sender, MouseEventArgs args) {
  cpu->SetAddressButton();
  }

void MainWindow::StartButtonPressed(void* sender, MouseEventArgs args) {
  cpu->StartButton();
  }

void MainWindow::StopButtonPressed(void* sender, MouseEventArgs args) {
  cpu->StopButton();
  }

void MainWindow::StoreMemoryButtonPressed(void* sender, MouseEventArgs args) {
  cpu->MemoryWriteButton();
  }

void MainWindow::TimerTick(void* sender) {
  Byte data;
  data = cpu->Lamps();
  if ((data & 0x80) != (dataLamps & 0x80)) {
    if (data & 0x80) dataLamp7->BackgroundImage(whiteLampOn);
      else dataLamp7->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x40) != (dataLamps & 0x40)) {
    if (data & 0x40) dataLamp6->BackgroundImage(whiteLampOn);
      else dataLamp6->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x20) != (dataLamps & 0x20)) {
    if (data & 0x20) dataLamp5->BackgroundImage(whiteLampOn);
      else dataLamp5->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x10) != (dataLamps & 0x10)) {
    if (data & 0x10) dataLamp4->BackgroundImage(whiteLampOn);
      else dataLamp4->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x08) != (dataLamps & 0x08)) {
    if (data & 0x08) dataLamp3->BackgroundImage(whiteLampOn);
      else dataLamp3->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x04) != (dataLamps & 0x04)) {
    if (data & 0x04) dataLamp2->BackgroundImage(whiteLampOn);
      else dataLamp2->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x02) != (dataLamps & 0x02)) {
    if (data & 0x02) dataLamp1->BackgroundImage(whiteLampOn);
      else dataLamp1->BackgroundImage(whiteLampOff);
    }
  if ((data & 0x01) != (dataLamps & 0x01)) {
    if (data & 0x01) dataLamp0->BackgroundImage(whiteLampOn);
      else dataLamp0->BackgroundImage(whiteLampOff);
    }
  dataLamps = data;
  data = cpu->LampMode();
  if (data != statLamps) {
    switch (statLamps) {
      case 1: inputLamp->BackgroundImage(yellowLampOff); break;
      case 2: addressLamp->BackgroundImage(yellowLampOff); break;
      case 3: memoryLamp->BackgroundImage(yellowLampOff); break;
      case 4: runLamp->BackgroundImage(yellowLampOff); break;
      }
    statLamps = data;
    switch (statLamps) {
      case 1: inputLamp->BackgroundImage(yellowLampOn); break;
      case 2: addressLamp->BackgroundImage(yellowLampOn); break;
      case 3: memoryLamp->BackgroundImage(yellowLampOn); break;
      case 4: runLamp->BackgroundImage(yellowLampOn); break;
      }
    }
  timer->Start();
  }

