#-------------------------------------------------------------------------------
# Example Makefile to build a library and to test the functions of each module
# Authors: Santiago Romani, Pere Millan
# Date: March 2021, March 2022
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# options for code generation
#-------------------------------------------------------------------------------
ARCH	:= -march=armv5te -mlittle-endian
ASFLAGS	:= $(ARCH) -g
CCFLAGS	:= -Wall -gdwarf-3 -O0 $(ARCH) -I./include
LDFLAGS := -z max-page-size=0x8000 -Lp_lib

#-------------------------------------------------------------------------------
# make commands
#-------------------------------------------------------------------------------
geotemp.elf: build/geotemp.o build/avgmaxmintemp.o build/data.o  
	arm-none-eabi-ld $(LDFLAGS) build/geotemp.o build/avgmaxmintemp.o build/data.o  \
			p_lib/CelsiusFahrenheit.o p_lib/libfoncompus.a p_lib/startup.o -o geotemp.elf
	
build/avgmaxmintemp.o: source/avgmaxmintemp.s include/avgmaxmintemp.i
	arm-none-eabi-as $(ASFLAGS) -c source/avgmaxmintemp.s -o build/avgmaxmintemp.o
	
build/data.o: source/data.c include/geotemp.h include/data.h
	arm-none-eabi-gcc $(CCFLAGS) -c source/data.c -o build/data.o

build/geotemp.o: source/geotemp.c include/geotemp.h include/data.h include/avgmaxmintemp.h
	arm-none-eabi-gcc $(CCFLAGS) -c source/geotemp.c -o build/geotemp.o

test_geotemp.elf: build/test_geotemp.o build/avgmaxmintemp.o
	arm-none-eabi-ld $(LDFLAGS) build/test_geotemp.o build/avgmaxmintemp.o \
			p_lib/CelsiusFahrenheit.o p_lib/startup.o p_lib/libfoncompus.a -o test_geotemp.elf

build/test_geotemp.o: tests/test_geotemp.c include/geotemp.h include/avgmaxmintemp.h
	arm-none-eabi-gcc $(CCFLAGS) -c tests/test_geotemp.c -o build/test_geotemp.o


#-------------------------------------------------------------------------------
# clean commands
#-------------------------------------------------------------------------------
clean : 
	@rm -fv build/*
	@rm -fv *.elf


#-----------------------------------------------------------------------------
# run commands
#-----------------------------------------------------------------------------
run : geotemp.elf
	arm-eabi-insight geotemp.elf &


#-----------------------------------------------------------------------------
# debug commands
#-----------------------------------------------------------------------------
debug : test_geotemp.elf
	arm-eabi-insight test_geotemp.elf &
