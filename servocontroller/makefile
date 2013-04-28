include makefile.common

CC=g++
MKDIR=mkdir -p
RM=rm -Rfv

CFLAGS=-Wall -Iinclude

BINDIR=bin
LIBDIR=lib64
DATADIR=data

DIRECTORIES:= $(BINDIR) $(LIBDIR) $(DATADIR)
OBJECTS := $(addprefix src/, Servo.o Servo/USB.o Servo/Dummy.o Server.o Server/UDP.o Log.o)
BINARIES := $(addprefix $(BINDIR)/, servocontroller)

##
# Create all required binaries, This will build every thing but the test
all: $(BINARIES)
	ctags -R

## 
# This is our main handler for created directories,
# To add a directory to the list modify the DIRECTORIES
# Variable
$(DIRECTORIES):
	@$(MKDIR) $@
	@echo "Directory '$@' Created"

## 
# All of our objects are passed through this, To add a new object
# Add to the OBJECTS directory
$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

##
# Our main program that uses the objects
$(BINDIR)/servocontroller: src/servocontroller.cpp $(BINDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@

###
# Our test build, builds the dummy bin file, called Servo.bin
# Inside our bin directory
test: $(DATADIR) $(DATADIR)/Servo.bin

## 
# This is a test bin directory, that is set as null of 38 bytes
# It represents our dump servo, for testing
$(DATADIR)/Servo.bin:
	dd if=/dev/zero of=$(DATADIR)/Servo.bin bs=1 count=0 seek=38

##
# This will remove our data/Servo.bin file, to build it again 
cleantest:
	@$(RM) $(DATADIR)/Servo.bin

##
# Cleans all the .o files from our src directory
# And finally cleans all directories.
clean:
	@$(RM) $(shell find src -name "*.o")
	@$(RM) $(DIRECTORIES)
	@$(RM) tags
