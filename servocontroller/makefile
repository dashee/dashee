include ../makefile.common

BINDIR=bin
LIBDIR=lib64
DIRECTORIES:= $(BINDIR) $(LIBDIR)

BINARIES := $(addprefix $(BINDIR)/, servocontroller)
OBJECTS := $(addprefix src/, Servo.o Server.o Server/UDP.o)

all: $(BINARIES)

$(DIRECTORIES):
	@$(MKDIR) $@
	@echo "Directory '$@' Created"

$(OBJECTS): %.o: %.cpp
	$(CC) -c $< -o $@

$(BINDIR)/servocontroller: src/servocontroller.cpp $(BINDIR) $(OBJECTS)
	$(CC) $(OBJECTS) $< -o $@

clean:
	@$(RM) $(shell find src -name "*.o")
	@$(RM) $(DIRECTORIES)
