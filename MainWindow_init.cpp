#include "MainWindow.h"
#include "header.h"

void MainWindow::InitializeComponent() {
  dataButton7 = new Button(this, 85, 125, 40, 40);
  dataButton7->Visible(true);
  dataButton7->BorderWidth(0);
  dataButton7->BackgroundImage(blackButton);
  dataButton7->PressedImage(blackButtonPressed);
  dataButton7->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton7);

  dataButton6 = new Button(this, 130, 125, 40, 40);
  dataButton6->Visible(true);
  dataButton6->BorderWidth(0);
  dataButton6->BackgroundImage(blackButton);
  dataButton6->PressedImage(blackButtonPressed);
  dataButton6->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton6);

  dataButton5 = new Button(this, 175, 125, 40, 40);
  dataButton5->Visible(true);
  dataButton5->BorderWidth(0);
  dataButton5->BackgroundImage(blackButton);
  dataButton5->PressedImage(blackButtonPressed);
  dataButton5->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton5);

  dataButton4 = new Button(this, 220, 125, 40, 40);
  dataButton4->Visible(true);
  dataButton4->BorderWidth(0);
  dataButton4->BackgroundImage(blackButton);
  dataButton4->PressedImage(blackButtonPressed);
  dataButton4->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton4);

  dataButton3 = new Button(this, 265, 125, 40, 40);
  dataButton3->Visible(true);
  dataButton3->BorderWidth(0);
  dataButton3->BackgroundImage(whiteButton);
  dataButton3->PressedImage(whiteButtonPressed);
  dataButton3->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton3);

  dataButton2 = new Button(this, 310, 125, 40, 40);
  dataButton2->Visible(true);
  dataButton2->BorderWidth(0);
  dataButton2->BackgroundImage(whiteButton);
  dataButton2->PressedImage(whiteButtonPressed);
  dataButton2->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton2);

  dataButton1 = new Button(this, 355, 125, 40, 40);
  dataButton1->Visible(true);
  dataButton1->BorderWidth(0);
  dataButton1->BackgroundImage(whiteButton);
  dataButton1->PressedImage(whiteButtonPressed);
  dataButton1->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton1);

  dataButton0 = new Button(this, 400, 125, 40, 40);
  dataButton0->Visible(true);
  dataButton0->BorderWidth(0);
  dataButton0->BackgroundImage(whiteButton);
  dataButton0->PressedImage(whiteButtonPressed);
  dataButton0->OnPress(new EventHandler(MainWindow::_DataButtonPressed, this));
  this->Add(dataButton0);

  clearButton = new Button(this, 455, 125, 40, 40);
  clearButton->Visible(true);
  clearButton->BorderWidth(0);
  clearButton->BackgroundImage(blackButton);
  clearButton->PressedImage(blackButtonPressed);
  clearButton->OnPress(new EventHandler(MainWindow::_ClearButtonPressed, this));
  this->Add(clearButton);

  displayAddressButton = new Button(this, 510, 125, 40, 40);
  displayAddressButton->Visible(true);
  displayAddressButton->BorderWidth(0);
  displayAddressButton->BackgroundImage(whiteButton);
  displayAddressButton->PressedImage(whiteButtonPressed);
  displayAddressButton->OnPress(new EventHandler(MainWindow::_DisplayAddressButtonPressed, this));
  this->Add(displayAddressButton);

  setAddressButton = new Button(this, 565, 125, 40, 40);
  setAddressButton->Visible(true);
  setAddressButton->BorderWidth(0);
  setAddressButton->BackgroundImage(blackButton);
  setAddressButton->PressedImage(blackButtonPressed);
  setAddressButton->OnPress(new EventHandler(MainWindow::_SetAddressButtonPressed, this));
  this->Add(setAddressButton);

  readMemoryButton = new Button(this, 620, 125, 40, 40);
  readMemoryButton->Visible(true);
  readMemoryButton->BorderWidth(0);
  readMemoryButton->BackgroundImage(whiteButton);
  readMemoryButton->PressedImage(whiteButtonPressed);
  readMemoryButton->OnPress(new EventHandler(MainWindow::_ReadMemoryButtonPressed, this));
  this->Add(readMemoryButton);

  writeMemoryButton = new Button(this, 675, 125, 40, 40);
  writeMemoryButton->Visible(true);
  writeMemoryButton->BorderWidth(0);
  writeMemoryButton->BackgroundImage(blackButton);
  writeMemoryButton->PressedImage(blackButtonPressed);
  writeMemoryButton->OnPress(new EventHandler(MainWindow::_StoreMemoryButtonPressed, this));
  this->Add(writeMemoryButton);

  startButton = new Button(this, 730, 125, 40, 40);
  startButton->Visible(true);
  startButton->BorderWidth(0);
  startButton->BackgroundImage(whiteButton);
  startButton->PressedImage(whiteButtonPressed);
  startButton->OnPress(new EventHandler(MainWindow::_StartButtonPressed, this));
  this->Add(startButton);

  stopButton = new Button(this, 785, 125, 40, 40);
  stopButton->Visible(true);
  stopButton->BorderWidth(0);
  stopButton->BackgroundImage(blackButton);
  stopButton->PressedImage(blackButtonPressed);
  stopButton->OnPress(new EventHandler(MainWindow::_StopButtonPressed, this));
  this->Add(stopButton);
 
  dataLamp7 = new Panel(this, 91, 51, 24, 24);
  dataLamp7->Visible(true);
  dataLamp7->BorderWidth(0);
  dataLamp7->BackgroundImage(whiteLampOff);
  this->Add(dataLamp7);
 
  dataLamp6 = new Panel(this, 136, 51, 24, 24);
  dataLamp6->Visible(true);
  dataLamp6->BorderWidth(0);
  dataLamp6->BackgroundImage(whiteLampOff);
  this->Add(dataLamp6);
 
  dataLamp5 = new Panel(this, 181, 51, 24, 24);
  dataLamp5->Visible(true);
  dataLamp5->BorderWidth(0);
  dataLamp5->BackgroundImage(whiteLampOff);
  this->Add(dataLamp5);
 
  dataLamp4 = new Panel(this, 226, 51, 24, 24);
  dataLamp4->Visible(true);
  dataLamp4->BorderWidth(0);
  dataLamp4->BackgroundImage(whiteLampOff);
  this->Add(dataLamp4);
 
  dataLamp3 = new Panel(this, 271, 51, 24, 24);
  dataLamp3->Visible(true);
  dataLamp3->BorderWidth(0);
  dataLamp3->BackgroundImage(whiteLampOff);
  this->Add(dataLamp3);
 
  dataLamp2 = new Panel(this, 316, 51, 24, 24);
  dataLamp2->Visible(true);
  dataLamp2->BorderWidth(0);
  dataLamp2->BackgroundImage(whiteLampOff);
  this->Add(dataLamp2);
 
  dataLamp1 = new Panel(this, 361, 51, 24, 24);
  dataLamp1->Visible(true);
  dataLamp1->BorderWidth(0);
  dataLamp1->BackgroundImage(whiteLampOff);
  this->Add(dataLamp1);
 
  dataLamp0 = new Panel(this, 406, 51, 24, 24);
  dataLamp0->Visible(true);
  dataLamp0->BorderWidth(0);
  dataLamp0->BackgroundImage(whiteLampOff);
  this->Add(dataLamp0);
 
  inputLamp = new Panel(this, 461, 51, 24, 24);
  inputLamp->Visible(true);
  inputLamp->BorderWidth(0);
  inputLamp->BackgroundImage(yellowLampOff);
  this->Add(inputLamp);
 
  addressLamp = new Panel(this, 571, 51, 24, 24);
  addressLamp->Visible(true);
  addressLamp->BorderWidth(0);
  addressLamp->BackgroundImage(yellowLampOff);
  this->Add(addressLamp);
 
  memoryLamp = new Panel(this, 681, 51, 24, 24);
  memoryLamp->Visible(true);
  memoryLamp->BorderWidth(0);
  memoryLamp->BackgroundImage(yellowLampOff);
  this->Add(memoryLamp);
 
  runLamp = new Panel(this, 791, 51, 24, 24);
  runLamp->Visible(true);
  runLamp->BorderWidth(0);
  runLamp->BackgroundImage(yellowLampOff);
  this->Add(runLamp);

  timer = new Timer();
  timer->OnTick(new EventHandler(MainWindow::_TimerTick, this));
  timer->Interval(1);
  timer->StopOnTick(true);
  timer->Start();
  }

void MainWindow::_ClearButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->ClearButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_DataButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->DataButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_DisplayAddressButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->DisplayAddressButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_ReadMemoryButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->ReadMemoryButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_SetAddressButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->SetAddressButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_StartButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->StartButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_StopButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->StopButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_StoreMemoryButtonPressed(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->StoreMemoryButtonPressed(sender, (MouseEventArgs&)args);
  }

void MainWindow::_TimerTick(void* obj, void* sender, EventArgs args) {
  ((MainWindow*)obj)->TimerTick(sender);
  }

