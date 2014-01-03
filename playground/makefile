include ../makefile.common

BINDIR=bin

BINARIES := $(addprefix $(BINDIR)/, servoUSB servoUART udpserver GPIO \
    ps3HexDump pthread queue 9DOF-HMC5883L 9DOF-ADXL345 9DOF-IDG-3200 9DOF-i2c \
    dashee-ADXL345)

all: $(BINARIES)

CFLAGS= -I../server/include -L$(LIBDIR) -std=c++0x

$(BINDIR):
	@echo "Directory '$@' created."
	@$(MKDIR) $@

$(LIBDIR):
	@echo "Directory '$@' linked."
	ln -snf ../server/$(LIBDIR)

$(BINDIR)/%: src/%.cpp | $(BINDIR) $(LIBDIR)
	$(CC) $(CFLAGS) -g $< -o $@ -ldashee

$(BINDIR)/%: src/%.py | $(BINDIR)
	install --mode=770 $< $@

$(BINDIR)/%: src/%.sh | $(BINDIR)
	install --mode=770 $< $@

$(BINDIR)/pthread: src/pthread.cpp | $(BINDIR) $(LIBDIR)
	$(CC) -g -I../server/include -L$(LIBDIR) $< -o $@ -ldashee

clean:
	@$(RM) $(BINDIR)
	unlink $(LIBDIR)
