include ../makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, helloworld udpserver udpclient.jar)

all: $(BINARIES)

$(BINDIR):
	$(MKDIR) bin

$(BINDIR)/helloworld: $(BINDIR) src/helloworld.cpp
	$(CC) src/helloworld.cpp -o $(BINDIR)/helloworld

$(BINDIR)/udpserver: $(BINDIR) src/udpserver.cpp
	$(CC) src/udpserver.cpp -o $(BINDIR)/udpserver

clean:
	$(RM) $(BINDIR)
