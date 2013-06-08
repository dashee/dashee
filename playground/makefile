include makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, helloworld udpserver uart)

all: $(BINARIES)

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(BINDIR)/helloworld: src/helloworld.cpp $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/uart: src/uart.cpp $(BINDIR)
	$(CC) $< -o $@

$(BINDIR)/udpserver: src/udpserver.cpp $(BINDIR)
	$(CC) -g $< -o $@

clean:
	@$(RM) $(BINDIR)
