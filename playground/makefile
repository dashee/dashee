include makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, helloworld udpserver)

all: $(BINARIES)

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(BINDIR)/helloworld: src/helloworld.cpp $(BINDIR)
	$(CC) $< -o $@

$(BINDIR)/udpserver: src/udpserver.cpp $(BINDIR)
	$(CC) $< -o $@

clean:
	@$(RM) $(BINDIR)
