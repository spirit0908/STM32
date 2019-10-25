# setup

COMPILE_OPTS = -W -Wall -ansi -pedantic
INCLUDE_DIRS = -I../../lib/inc -I../../ -I../../modules/Teleinfo/ -I../../modules/Fifo
#LIBRARY_DIRS = -L lib

CC = gcc
CFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

CXX = g++
CXXFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

AS = gcc
ASFLAGS = $(COMPILE_OPTS) -c

LD = gcc
#LDFLAGS = -Wl,--gc-sections,-Map=$(OUT_PATH)/$(MAIN_OUT).map,-cref,-u,Reset_Handler $(INCLUDE_DIRS) $(LIBRARY_DIRS) -T stm32f103c8t6.ld


MAIN_OUT = main

# all
#all: $(MAIN_OUT_ELF) $(MAIN_OUT_BIN)

# main
SRC_FILES = \
  main.c \
  ../../modules/Teleinfo/teleinfo.c \
  stubs.c

#INC_FILES = \
  Std_Types.h

#test:
#	$(CC) $(CCFLAGS) main.c ../../modules/Teleinfo/teleinfo.c stubs.c -o main

test:
	$(CC) -I../../lib/inc -I../../ -I../../modules/Teleinfo/ -I../../modules/Fifo main.c ../../modules/Teleinfo/teleinfo.c stubs.c -o main



runtest: test
	./main

clean:
	rm main
