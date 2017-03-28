#	This is a Makefile for AVR KURS,
#	attempting to provide support for compiling and flashing AtTiny817 from Linux (2017-03-07)
#	Author: magne.hov@gmail.com
#	
#	Guide for programming AVR AtTiny817 in Linux  
#		To compile for AVR AtTiny817 we need some utilities for AVR, install these:
#			'sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc' for aptitude distros
#			or 'pacman -S gcc-avr binutils-avr gdb-avr avr-libc' for Arch distro
#
#			We also need an Atmel AtTiny Series Device Support package, which cannot easily
#			be extracted on Linux and is easiest copied from a friend or AVR kurs studass.
#			If copying from Windows, the Attiny folder should be located somewhere like this:
#  			"C:\Program Files (x86)\Atmel\Studio\7.0\packs\atmel\Attiny_DFP\1.2.112" ...
#  			... after being unpacked by Atmel Studio.
#			Make sure to put this package at the place where DFP_DIR in this file is directed
#
#		To program the AtTiny on Linux, an unofficial tool called pyUPDI can be used.
#			It can be downloaded from https://github.com/mraardvark/pyupdi through git:
#			'git clone https://github.com/mraardvark/pyupdi'
#			in f.ex /home/user/repos.
#
#		pyUPDI depends on python 2.7, and some python 2.7 packages, install these with
#			'pip2 install pyserial intelhex'
#			Note: if you don't have pip2, install it with
#				'sudo apt-get install python-pip' for aptitude repos etc.
#				or 'sudo pacman -S python2-pip' for Arch etc.
#
#		Remember to edit HOME_DIR in this file to point to your home directory, and to modifiy
#		DFP_DIR and PYUPDI_DIR in this file to point to the directories where you placed the 
#		Support package and pyUPDI.
#
#		When all of these dependencies are taken care of, you should be able to run 'sudo make' from the folder with the source files and MakeFile.

# ###
# Dependency directories and binaries
HOME_DIR = /home/magne/
DFP_DIR = $(HOME_DIR)avr/dfp/1.2.112/
PYUPDI_DIR = $(HOME_DIR)repos/pyupdi/

AVR-GCC = avr-gcc
AVR-OBJCOPY = avr-objcopy

# ####
# Project files and flags

#Source files, add more files to SRC if needed: main.c uart.c ...
SRC = main.c
OBJ = $(SRC:.c=.o)

#Target name
TARGET = out

#Compiler and Linker flags
MCU = attiny817
CFLAGS = -B $(DFP_DIR)gcc/dev/attiny817 -I $(DFP_DIR)include -mmcu=$(MCU) -Os
LDFLAGS = -B $(DFP_DIR)gcc/dev/attiny817 -I $(DFP_DIR)include -mmcu=$(MCU) #-Wl,-Map=$(TARGET).map

# ####
# Make rules
all: compile flash clean

compile: $(TARGET).hex

flash: compile
	python2 $(PYUPDI_DIR)pyupdi.py /dev/ttyACM0 tiny817 $(TARGET).hex

clean:
	rm -f $(OBJ) $(TARGET).{elf,hex}

# ####
# Compiler rules
%.hex: %.elf
	$(AVR-OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.elf: $(OBJ)
	$(AVR-GCC) $^ $(LDFLAGS) -o $@

%.o : %.c
	$(AVR-GCC) $(CFLAGS) -o $@ -c $<
