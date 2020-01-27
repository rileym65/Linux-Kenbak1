#ifndef _HEADER_H
#define _HEADER_H

#ifdef MAIN
#define LINK
#else
#define LINK extern
#endif

#include <SmrFramework.h>
#include <SmrAppFramework.h>

using namespace SmrFramework;

#include "cpu.h"
#include "MainWindow.h"

LINK Cpu          *cpu;
LINK Application  *app;
LINK MainWindow   *window;
LINK Image        *blackButton;
LINK Image        *blackButtonPressed;
LINK Image        *whiteButton;
LINK Image        *whiteButtonPressed;
LINK Image        *whiteLampOn;
LINK Image        *whiteLampOff;
LINK Image        *yellowLampOn;
LINK Image        *yellowLampOff;

#endif

