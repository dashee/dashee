include ../makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, servoUSB servoUART udpserver GPIO)

all: $(BINARIES)

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(BINDIR)/servoUSB: src/servoUSB.cpp $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/servoUART: src/servoUART.cpp $(BINDIR)
	$(CC) $< -o $@

$(BINDIR)/udpserver: src/udpserver.cpp $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/GPIO: src/GPIO.cpp $(BINDIR)
	$(CC) -g $< -o $@

clean:
	@$(RM) $(BINDIR)
