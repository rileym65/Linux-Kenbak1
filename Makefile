PROJECT=kenbak
CC=g++
DEFS= -std=c++11 -pthread
INCDIR= -I/usr/include/freetype2
INCS=
LIBDIR=
#LIBS= -lSmrFramework -lSmrAppFramework -lX11 -lXft
LIBS= -lSmrFramework -lSmrAppFramework -lX11
OBJS= \
	cpu.o \
	MainWindow.o \
	MainWindow_init.o \
	main.o

all: $(PROJECT) asm

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

asm: asm.o
	$(CC) $(DEFS) $(LIBDIR) asm.o $(LIBS) -o asm

.cpp.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)
	-rm asm

cpu.o:       header.h cpu.h cpu.cpp
main.o:      header.h MainWindow.h cpu.h main.cpp
MainWindow.o: header.h MainWindow.h cpu.h MainWindow.cpp
MainWindow_init.o: header.h MainWindow.h cpu.h MainWindow_init.cpp

