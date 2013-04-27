include makefile.common

CC=g++
MKDIR=mkdir -p
RM=rm -Rfv


CFLAGS=-Iinclude

BINDIR=bin
LIBDIR=lib64
DIRECTORIES:= $(BINDIR) $(LIBDIR)

BINARIES := $(addprefix $(BINDIR)/, servocontroller)
OBJECTS := $(addprefix src/, Servo.o Servo/USB.o Servo/Dummy.o Server.o Server/UDP.o Log.o)

all: $(BINARIES)

$(DIRECTORIES):
	@$(MKDIR) $@
	@echo "Directory '$@' Created"

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/servocontroller: src/servocontroller.cpp $(BINDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@

clean:
	@$(RM) $(shell find src -name "*.o")
	@$(RM) $(DIRECTORIES)
