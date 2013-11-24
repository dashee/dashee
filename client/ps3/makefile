##
# @author Shahmir Javaid

# Include a common set of options
include makefile.common

BINDIR=bin
SRCDIR=src

all: ps3

$(BINDIR):
	mkdir -p $(BINDIR)

ps3: | $(BINDIR)
	install --mode=755 $(SRCDIR)/ps3.py $(BINDIR)/ps3

clean:
	$(RM) $(BINDIR)
