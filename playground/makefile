
CC=g++
BINDIR=bin

all: $(BINDIR)/helloworld

$(BINDIR):
	mkdir -p bin

$(BINDIR)/helloworld: $(BINDIR) src/helloworld.cpp
	$(CC) src/helloworld.cpp -o $(BINDIR)/helloworld

clean:
	rm -Rfv $(BINDIR)
