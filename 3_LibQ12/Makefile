#-------------------------------------------------------------------------------
# Example Makefile to build a library and to test the functions of each module
# Authors: Santiago Romani, Pere Millán
# Date: April 2021, March 2022
#-------------------------------------------------------------------------------
#	Programador/a 1: xxx.xxx@estudiants.urv.cat
#	Programador/a 2: yyy.yyy@estudiants.urv.cat
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# options for code generation
#-------------------------------------------------------------------------------
ARCH	:= -march=armv5te -mlittle-endian
INCL    := -I./includes
ASFLAGS	:= $(ARCH) $(INCL) -g
CCFLAGS	:= -Wall -gdwarf-3 -O0 $(ARCH) $(INCL)
LDFLAGS := -z max-page-size=0x8000

#-------------------------------------------------------------------------------
# make commands
#-------------------------------------------------------------------------------
libQ12.a: build/Q12.o
	arm-none-eabi-ar -rs libQ12.a build/Q12.o

build/Q12.o: sources/Q12.s includes/Q12.h
	arm-none-eabi-as $(ASFLAGS) -c sources/Q12.s -o build/Q12.o


#-------------------------------------------------------------------------------
# test making commands
#-------------------------------------------------------------------------------
test_Q12.elf : tests/test_Q12.c includes/Q12.h libQ12.a
	arm-none-eabi-gcc $(CCFLAGS) -c tests/test_Q12.c -o build/test_Q12.o
	arm-none-eabi-ld $(LDFLAGS) build/test_Q12.o tests/startup.o \
					libQ12.a tests/libfoncompus.a -o test_Q12.elf

demo.elf : tests/demo.c includes/Q12.h libQ12.a
	arm-none-eabi-gcc $(CCFLAGS) -c tests/demo.c -o build/demo.o
	arm-none-eabi-ld $(LDFLAGS) build/demo.o tests/startup.o \
					libQ12.a tests/libfoncompus.a -o demo.elf


#-------------------------------------------------------------------------------
# clean commands
#-------------------------------------------------------------------------------
clean : 
	@rm -fv build/*
	@rm -fv *.elf


#-----------------------------------------------------------------------------
# run commands
#-----------------------------------------------------------------------------
run : demo.elf
	arm-eabi-insight demo.elf &


#-----------------------------------------------------------------------------
# debug commands
#-----------------------------------------------------------------------------
debug : test_Q12.elf
	arm-eabi-insight test_Q12.elf &
