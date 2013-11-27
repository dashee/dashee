include ../makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, servoUSB servoUART udpserver GPIO ps3HexDump pthread)

all: $(BINARIES)

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(LIBDIR):
	@echo "Directory '$@' linked."
	ln -snf ../$(LIBDIR)

$(BINDIR)/servoUSB: src/servoUSB.cpp | $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/servoUART: src/servoUART.cpp | $(BINDIR)
	$(CC) $< -o $@

$(BINDIR)/udpserver: src/udpserver.cpp | $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/GPIO: src/GPIO.cpp | $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/ps3HexDump: src/ps3HexDump.sh | $(BINDIR)
	install --mode=770 $< $@

$(BINDIR)/pthread: src/pthread.cpp | $(BINDIR) $(LIBDIR)
	$(CC) -g -I../include -L$(LIBDIR) -pthread $< -o $@ -ldashee

clean:
	@$(RM) $(BINDIR)
	unlink $(LIBDIR)
