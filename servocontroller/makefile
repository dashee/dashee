include ../makefile.common

BINDIR=bin
OBJDIR=obj
LIBDIR=lib64

BINARIES := $(addprefix $(BINDIR)/, servocontroller)
OBJECTS := $(addprefix $(OBJDIR)/, Servo.o)

all: $(OBJECTS) $(BINARIES)

$(BINDIR):
	$(MKDIR) $(BINDIR)

$(LIBDIR): 
	$(MKDIR) $(LIBDIR)

$(OBJDIR): 
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/Servo.o: $(OBJDIR) src/Servo.cpp
	$(CC) -c src/Servo.cpp -o $(OBJDIR)/Servo.o

$(BINDIR)/servocontroller: $(BINDIR) src/Servo.cpp src/servocontroller.cpp
	$(CC) $(OBJDIR)/Servo.o src/servocontroller.cpp -o $(BINDIR)/servocontroller

clean:
	$(RM) $(BINDIR)
	$(RM) $(OBJDIR)
	$(RM) $(LIBDIR)
