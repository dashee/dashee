##
# Make file which builds the following bin files located
# in $(BINDIR):
#
#   - libdashee.so
#   - servo
#   - servod
#   - runtest
#   - test/testServo
#   - test/testServoController
#
# @author Shahmir Javaid

# Include a common set of options
include makefile.common

# Set directories as variables
BINDIR=bin
TESTDIR=$(BINDIR)/tests
LIBDIR=lib
ifeq ($(shell getconf LONG_BIT), 64)
        LIBDIR=lib64
endif
SCRIPTSDIR=scripts/
DATADIR=data
DIRECTORIES:= $(BINDIR) $(LIBDIR) $(DATADIR) $(TESTDIR) $(INITDIR)

# All the objects that are built
OBJECTS := $(addprefix src/,)
OBJECTSLIB := $(addprefix src/, Log.o Config.o GPIO.o Servo.o \
    		Servo/Dummy.o Servo/USB.o Servo/UART.o Server.o \
		ServoController.o ServoController/Dummy.o ServoController/USB.o \
		ServoController/UART.o Server/UDP.o common.o daemon.o signal.o \
		Model.o Model/Car.o)
OBJECTSTEST := $(addprefix tests/, dashee.o ServoController.o ServoController/Dummy.o\
    		 ServoController/UART.o GPIO.o Servo.o Servo/UART.o Servo/Dummy.o Config.o Model.o Model/Car.o)

# All the binaries which will be built
#SO := $(addprefix lib/,)
LIBRARIES := $(addprefix $(LIBDIR)/, libdashee.so)
BINARIES := $(addprefix $(BINDIR)/, servo servod telemetry telemetryd)
TESTS := $(addprefix $(TESTDIR)/, testUART testGPIO testDummy testConfig testModelCar)

# Compiler options
WOPTIONS=-Wall -fPIC
INCLUDES=-Iinclude -L$(LIBDIR)
CFLAGS=$(WOPTIONS) $(INCLUDES)
LFLAGS=-shared -fpic

# Release ID
RELEASEID?=$(shell svn info | grep -E '^Revision' | awk '{print $$2}')

# Create all required binaries, but in debug mode
# Use `make release`
all: test debug
libraries: $(LIBRARIES)

# Creates the binaries, in non debug mode
release: $(BINARIES)

# A helpfull function for debug configurations
debug: CFLAGS+=-g -DDEBUG
debug: LFLAGS+=-g -DDEBUG
debug: $(BINARIES)

# Create a compressed tar archive file, usefull for releases
# and packaging
tar:
	if [ -f dashee-$(RELEASEID).tar.gz ]; then \
	    echo "Tar file 'dashee-src-$(RELEASEID).tar.gz' already exist!";\
	    exit 1;\
	fi
	tar -zcf dashee-src-$(RELEASEID).tar.gz --exclude='*.o' src makefile makefile.common include tests
	$(call print,"Building","file","dashee-src-$(RELEASEID).tar.gz")

# This is our main handler for created directories,
# To add a directory to the list modify the DIRECTORIES
# Variable
$(DIRECTORIES):
	$(MKDIR) $@
	$(call print,"Building","directory","$@")

# All of our objects are passed through this, To add a new object
# Add to the OBJECTS directory
$(OBJECTSTEST): CFLAGS+=-Wno-overflow
$(OBJECTSTEST): INCLUDES+=-Itests
$(OBJECTS) $(OBJECTSLIB) $(OBJECTSTEST): %.o: %.cpp
	$(call print,"Building","object","$@")
	$(CC) $(CFLAGS) -c $< -o $@

# Log shared object
$(LIBDIR)/libdashee.so: $(LIBDIR) $(OBJECTSLIB) | $(LIBDIR)
	$(call print,"Building","lib","$@")
	$(CC) $(LFLAGS) -Wl,-soname,$@ -o $@ $(OBJECTSLIB)

# The ServoController program
$(BINDIR)/servo: src/servod.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	$(call print,"Building","binary","$@")
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@ -ldashee

# Our main program that uses the objects
$(BINDIR)/servod: CFLAGS+=-DDAEMON
$(BINDIR)/servod: src/servod.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	$(call print,"Building","binary","$@")
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@ -ldashee

# The ServoController program
$(BINDIR)/telemetry: src/telemetryd.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	$(call print,"Building","binary","$@")
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@ -ldashee

# Our main program that uses the objects
$(BINDIR)/telemetryd: CFLAGS+=-DDAEMON
$(BINDIR)/telemetryd: src/telemetryd.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	$(call print,"Building","binary","$@")
	$(CC) $(CFLAGS) $(OBJECTS) $< -o $@ -ldashee

# Build and run all the tests
test: testbuild binfile
	@echo -e "\nRUNNING TESTS"
	bin/runtest dummy 2> /dev/null
	@echo ""

# BUILD all the tests
testbuild: $(TESTS) $(BINDIR)/runtest

$(BINDIR)/runtest: $(SCRIPTSDIR)/runtest.sh
	$(call print,"Building","script","$@")
	install --mode=775 $< $@

$(TESTDIR)/testDummy: tests/testDummy.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testUART: tests/testUART.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testGPIO: tests/testGPIO.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testConfig: tests/testConfig.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testModelCar: tests/testModelCar.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

# Build our init scripts
$(INITDIR)/dashee-servod: src/servod.init.sh | $(INITDIR)
	$(call print,"Building","init-script","$@")
	install --mode=755 $< $@

# Our test build, builds the dummy bin file, called Servo.bin
# Inside our bin directory
binfile: $(DATADIR)/Servo.bin

# This is a test bin directory, that is set as null of 38 bytes
# It represents our dump servo, for testing
$(DATADIR)/Servo.bin: | $(DATADIR)
	$(call print,"Building","data","$@")
	dd if=/dev/zero of=$(DATADIR)/Servo.bin bs=1 count=0 seek=38 >/dev/null

# Builds the documentation
documentation:
	$(call print,"Building","data","$@")
	doxygen docs/doxygen.conf > /dev/null

install: $(BINDIR)/servod $(LIBDIR)/libdashee.so
	if [ "$(shell whoami)" != "root" ]; then echo "Need to be root to perform install"; exit 1; fi;
	$(call print,"Installing","binary","dashee-servod")
	install --owner=root --group=root --mode=755 $(LIBDIR)/libdashee.so /$(LIBDIR)/libdashee.so
	$(call print,"Installing","library","libdashee.so")
	install --owner=root --group=root --mode=755 $(BINDIR)/servod /usr/bin/dashee-servod
	$(call print,"Installing","directory","/var/log/dashee")
	[ -d /var/log/dashee ] || mkdir /var/log/dashee
	$(call print,"Installing","file","/var/log/dashee/servod.log")
	touch /var/log/dashee/servod.log
	$(call print,"Installing","file","/etc/init.d/dashee-servod")
	install --owner=root --group=root --mode=755 $(SCRIPTSDIR)/init.d/dashee-servod /etc/init.d/dashee-servod
	$(call print,"Installing","directory","/etc/dashee")
	[ -d /etc/dashee ] || mkdir /etc/dashee
	$(call print,"Installing","file","/etc/dashee/servod.conf")
	touch /etc/dashee/servod.conf
	$(call print,"Installing","directory","/var/run/dashee")
	[ -d /var/run/dashee ] || mkdir /var/run/dashee

# Remove only the tests
cleantest:
	$(RM) $(BINDIR)/tests

# This will remove our data/Servo.bin file, to build it again 
cleandata:
	$(RM) $(DATADIR)/Servo.bin

# Will generate ctags for vim
tags:
	@ctags-exuberant -R .
    
# Cleans all the .o files from our src directory
# And finally cleans all directories.
clean: cleanobjects cleantest
	$(RM) $(shell find src -name "*.o")
	$(RM) $(shell find tests -name "*.o")
	$(call print,"Deleting","directory","$(BINDIR)")
	$(RM) $(BINDIR)
	$(call print,"Deleting","directory","$(LIBDIR)")
	$(RM) $(LIBDIR)
	$(call print,"Deleting","file","tags")
	$(RM) tags

cleanobjects:
	for i in  $(OBJECTS) $(OBJECTSLIB) $(OBJECTSTEST); do \
		$(call print,"Deleting","objects","$$i");\
		$(RM) $$i;\
	done;


cleanall: clean
	$(call print,"Deleting","directory","$(DIRECTORIES)")
	$(RM) $(DIRECTORIES)
	$(call print,"Deleting","directory","etc")
	$(RM) etc
	$(call print,"Deleting","directory","doc/html")
	$(RM) docs/html
	$(call print,"Deleting","directory","doc/xml")
	$(RM) docs/xml
	$(call print,"Deleting","objects","find *.o")
	find src/ -name "*.o" -type f -delete
	find tests/ -name "*.o" -type f -delete
