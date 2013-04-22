include ../makefile.common

BINDIR=bin
LIBDIR=lib64
DIRECTORIES:= $(BINDIR) $(LIBDIR)

BINARIES := $(addprefix $(BINDIR)/, servocontroller)
OBJECTS := $(addprefix src/, Servo.o)

all: $(BINARIES)

$(DIRECTORIES):
	@$(MKDIR) $@
	@echo "Directory '$@' Created"

$(OBJECTS): %.o: %.cpp
	$(CC) -c $< -o $@

$(BINDIR)/servocontroller: src/servocontroller.cpp $(BINDIR) src/Servo.o
	$(CC) src/Servo.o $< -o $@

clean:
	@$(RM) $(shell find src -name "*.o")
	@$(RM) $(DIRECTORIES)
