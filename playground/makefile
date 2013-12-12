include ../makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, servoUSB servoUART udpserver GPIO \
    ps3HexDump pthread queue 9DOF-HMC5883L)

all: $(BINARIES)

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(LIBDIR):
	@echo "Directory '$@' linked."
	ln -snf ../server/$(LIBDIR)

$(BINDIR)/%: src/%.cpp | $(BINDIR)
	$(CC) -g $< -o $@

$(BINDIR)/%: src/%.py | $(BINDIR)
	install --mode=770 $< $@

$(BINDIR)/%: src/%.sh | $(BINDIR)
	install --mode=770 $< $@

$(BINDIR)/pthread: src/pthread.cpp | $(BINDIR) $(LIBDIR)
	$(CC) -g -I../server/include -L$(LIBDIR) $< -o $@ -ldashee

clean:
	@$(RM) $(BINDIR)
	unlink $(LIBDIR)
