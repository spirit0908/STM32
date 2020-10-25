# setup

COMPILE_OPTS = -W -Wall -ansi -pedantic -std=c99 -g
INCLUDE_DIRS = -I../ -I../../../lib/inc -I../../../
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
  test_main.c \
  ../*.c \
  stubs.c

#INC_FILES = \
  Std_Types.h


test_main:
	$(CC) $(CFLAGS) test_main.c ../pinCode.c -o test_main


test: test_main
	./test_main

runtest: test_main
	./test_main > test_exec.log
	perl generate_test_report.pl test_exec.log test_result_pinCode.xml
	mkdir -p ../../../out/tests
	cp test_result_pinCode.xml ../../../out/tests/test_result_pinCode.xml

debug: test
	gdb -tui test_main test_main.c

clean:
	rm -f test_main
	rm -f test_exec.log
	rm -f test_result_*.xml

