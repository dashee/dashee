include makefile.common

BINDIR=bin
LIBDIR=lib64

BINARIES := $(addprefix $(BINDIR)/, servocontroller)

all: $(BINARIES)

$(BINDIR):
	$(MKDIR) $(BINDIR)

$(LIBDIR): 
	$(MKDIR) $(LIBDIR)

$(BINDIR)/servocontroller: $(BINDIR) src/servocontroller.cpp
	$(CC) src/servocontroller.cpp -o $(BINDIR)/servocontroller

.PHONY: playground
playground:
	cd playground; make

clean:
	$(RM) $(BINDIR)
	$(RM) $(LIBDIR)
	cd playground; make clean
