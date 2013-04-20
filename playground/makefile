include ../makefile.common

BINDIR=bin

all: $(BINDIR)/helloworld

$(BINDIR):
	$(MKDIR) bin

$(BINDIR)/helloworld: $(BINDIR) src/helloworld.cpp
	$(CC) src/helloworld.cpp -o $(BINDIR)/helloworld

clean:
	$(RM) $(BINDIR)
