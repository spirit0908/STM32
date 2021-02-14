# setup

COMPILE_OPTS = -mcpu=cortex-m3 -mthumb -Wall -g -O0
INCLUDE_DIRS = -I . -I lib/inc -I obj
LIBRARY_DIRS = -L lib

CC = arm-none-eabi-gcc
CFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

CXX = arm-none-eabi-g++
CXXFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS)

AS = arm-none-eabi-gcc
ASFLAGS = $(COMPILE_OPTS) -c

LD = arm-none-eabi-gcc
LDFLAGS = -Wl,--gc-sections,-Map=$(OUT_PATH)/$(MAIN_OUT).map,-cref,-u,Reset_Handler $(INCLUDE_DIRS) $(LIBRARY_DIRS) -T stm32f103c8t6.ld

OBJCP = arm-none-eabi-objcopy
OBJCPFLAGS = -O binary

AR = arm-none-eabi-ar
ARFLAGS = cr

OBJ_PATH = obj
OUT_PATH = out

MAIN_OUT = main
MAIN_OUT_ELF = $(OUT_PATH)/$(MAIN_OUT).elf
MAIN_OUT_BIN = $(OUT_PATH)/$(MAIN_OUT).bin

# all

all: $(MAIN_OUT_ELF) $(MAIN_OUT_BIN)

# main
MODULES_PATH=../../modules
#MODULES_PATH=./modules

SRC_FILES = \
  main.c \
  $(MODULES_PATH)/nokia/n3310.c \
  $(MODULES_PATH)/Teleinfo/teleinfo.c \
  $(MODULES_PATH)/Fifo/Fifo.c \
  $(MODULES_PATH)/Fifo/Fifo_Cfg.c \
  $(MODULES_PATH)/TaskMan/Task_cfg.c \
  $(MODULES_PATH)/TaskMan/Task.c \
  $(MODULES_PATH)/OrderMgt/Order_mgt.c \
  $(MODULES_PATH)/Light/Light.c \
  $(MODULES_PATH)/LcdMenu/LcdMenu.c \
  $(MODULES_PATH)/PushButton/PushButton.c \
  $(MODULES_PATH)/LedStrip/LedStrip.c \
  $(MODULES_PATH)/Heating/Heating.c \
  $(MODULES_PATH)/Security/Security.c \
  serial.c

INC_FILES = \
  Std_Types.h \
  $(MODULES_PATH)/nokia/n3310.h \
  $(MODULES_PATH)/nokia/picture.h \
  $(MODULES_PATH)/Teleinfo/teleinfo.h \
  $(MODULES_PATH)/Fifo/Fifo.h \
  $(MODULES_PATH)/Fifo/Fifo_Cfg.h \
  $(MODULES_PATH)/TaskMan/Task.h \
  $(MODULES_PATH)/TaskMan/Task_cfg.h \
  $(MODULES_PATH)/OrderMgt/Order_mgt.h \
  $(MODULES_PATH)/Light/Light.h \
  $(MODULES_PATH)/LcdMenu/LcdMenu.h \
  $(MODULES_PATH)/PushButton/PushButton.h \
  $(MODULES_PATH)/LedStrip/LedStrip.h \
  $(MODULES_PATH)/Heating/Heating.h \
  $(MODULES_PATH)/Security/Security.h \
  serial.h

$(MAIN_OUT_ELF): updateIncFiles $(SRC_FILES:%.c=%.o) stm32f10x_it.o lib/libstm32.a
	$(LD) $(LDFLAGS) $(SRC_FILES:%.c=%.o) stm32f10x_it.o lib/libstm32.a --output $@

$(MAIN_OUT_BIN): $(MAIN_OUT_ELF)
	$(OBJCP) $(OBJCPFLAGS) $< $@

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I build/inc -I lib/inc

updateIncFiles:
	mkdir -p build/src
	mkdir -p build/inc
	mkdir -p out/
	cp $(SRC_FILES) build/src
	cp $(INC_FILES) build/inc

# flash

#flash: $(MAIN_OUT)
#	@cp $(MAIN_OUT_ELF) jtag/flash
#	@cd jtag; openocd -f flash.cfg
#	@rm jtag/flash

flash: $(MAIN_OUT_BIN)
	st-flash write $(MAIN_OUT_BIN) 0x8000000

#Debug
debug: $(MAIN_OUT_BIN)
	#Launch st-util in a new terminal
	gnome-terminal -e st-util
	#Then launch gdb
	arm-none-eabi-gdb -tui out/main.elf -x "target extended-remote localhost:4242"


#Test
test: $(MAIN_OUT_BIN)
	rm -f out/tests/*.xml
	(cd modules/Teleinfo/tests; make runtest)
	(cd modules/Heating/tests; make runtest)
#	(cd modules/pinCode/tests; make runtest)
#	(cd out/tests; ./combine_xml.sh test_results.xml)
#	(cd out/tests; xsltproc test_report_generator.xsl test_results.xml > Test_results.html )

#Execute tests and generate report
testreport: test
	(cd out/tests; ../../../../tools/test_report_generator/combine_xml.sh test_results.xml)
	(cd out/tests; xsltproc ../../../../tools/test_report_generator/test_report_generator.xsl test_results.xml > Test_results.html )

# libstm32.a

LIBSTM32_OUT = lib/libstm32.a

LIBSTM32_OBJS = \
 lib/src/stm32f10x_adc.o \
 lib/src/stm32f10x_bkp.o \
 lib/src/stm32f10x_can.o \
 lib/src/stm32f10x_dma.o \
 lib/src/stm32f10x_exti.o \
 lib/src/stm32f10x_flash.o \
 lib/src/stm32f10x_gpio.o \
 lib/src/stm32f10x_i2c.o \
 lib/src/stm32f10x_iwdg.o \
 lib/src/stm32f10x_lib.o \
 lib/src/stm32f10x_nvic.o \
 lib/src/stm32f10x_pwr.o \
 lib/src/stm32f10x_rcc.o \
 lib/src/stm32f10x_rtc.o \
 lib/src/stm32f10x_spi.o \
 lib/src/stm32f10x_systick.o \
 lib/src/stm32f10x_tim.o \
 lib/src/stm32f10x_tim1.o \
 lib/src/stm32f10x_usart.o \
 lib/src/stm32f10x_wwdg.o \
 lib/src/cortexm3_macro.o \
 lib/src/stm32f10x_vector.o

$(LIBSTM32_OUT): $(LIBSTM32_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIBSTM32_OBJS)

$(LIBSTM32_OBJS): stm32f10x_conf.h


clean:
#	-rm lib/src/*.o obj/*.o out/*.map $(LIBSTM32_OUT) $(MAIN_OUT_ELF) $(MAIN_OUT_BIN)
	rm build/src/*.c
	rm build/inc/*.h
	find . -type f -name '*.o' -delete
	rm out/main.bin
	rm out/main.elf
	rm out/main.map
	rm out/tests/*.xml


