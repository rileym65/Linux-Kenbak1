#define MAIN

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "header.h"
#include "cpu.h"
#include "images.h"

int main(int argc, char** argv) {
  UInt32 i;
  Image* kenbak;
  Boolean debugMode;

  debugMode = false;
  for (i=0; i<argc; i++) {
    if (strcmp(argv[i],"-d") == 0) debugMode = true;
    }
  
  app = new Application();
  if (app == NULL) {
    printf("Could not create application object.  Aborting\n");
    exit(1);
    }
  app->LoopDelay(1000);

  kenbak = new Image(new MemoryStream(Kenbak, Kenbak_length));
  blackButton = new Image(new MemoryStream(BlackButton, BlackButton_length));
  blackButtonPressed = new Image(new MemoryStream(BlackButtonPressed, BlackButtonPressed_length));
  whiteButton = new Image(new MemoryStream(WhiteButton, WhiteButton_length));
  whiteButtonPressed = new Image(new MemoryStream(WhiteButtonPressed, WhiteButtonPressed_length));
  whiteLampOn = new Image(new MemoryStream(WhiteLightOn, WhiteLightOn_length));
  whiteLampOff = new Image(new MemoryStream(WhiteLightOff, WhiteLightOff_length));
  yellowLampOn = new Image(new MemoryStream(YellowLightOn, YellowLightOn_length));
  yellowLampOff = new Image(new MemoryStream(YellowLightOff, YellowLightOff_length));

  cpu = new Cpu();
  cpu->DebugMode(debugMode);
  window = new MainWindow(cpu, 1024, 240);
  window->BackgroundImage(kenbak);
  window->Text("Kenbak-I");
  app->AddForm(window);
  window->Visible(true);


  cpu->Start(NULL);
  try {
    app->Run();
    }
  catch (Exception &e) {
    printf("Exception caught: %s\n",e.Message());
    if (e.Sender() != NULL) printf("  Type: %s\n",e.Sender()->Type());
      else printf("Sender is NULL\n");
    fflush(stdout);
    }
  cpu->Terminate();
  sleep(1);
  delete(cpu);
  delete(app);
  return 0;
  }

