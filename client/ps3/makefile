##
# @author Shahmir Javaid

# Include a common set of options
include ../../makefile.common

all: ps3

$(BINDIR):
	mkdir -p $(BINDIR)

ps3: | $(BINDIR)
	install --mode=755 src/ps3.py $(BINDIR)/ps3

clean:
	$(RM) $(BINDIR)
