include makefile.common

# Set directories as variables
BINDIR=bin
TESTDIR=$(BINDIR)/tests
LIBDIR=lib
ifeq ($(shell getconf LONG_BIT), 64)
        LIBDIR=lib64
endif   
DATADIR=data
DIRECTORIES:= $(BINDIR) $(LIBDIR) $(DATADIR) $(TESTDIR)

# All the objects that are built
OBJECTS := $(addprefix src/, Config/Servod.o)
OBJECTSLIB := $(addprefix src/, Log.o Config.o Common.o GPIO.o Servo.o \
    		Servo/Dummy.o Servo/USB.o Servo/UART.o Server.o \
		ServoController.o ServoController/Dummy.o ServoController/USB.o \
		ServoController/UART.o Server/UDP.o)
OBJECTSTEST := $(addprefix tests/, dashee.o ServoController.o ServoController/Dummy.o\
    		 ServoController/UART.o GPIO.o Servo.o Servo/Dummy.o)

# All the binaries which will be built
#SO := $(addprefix lib/,)
LIBRARIES := $(addprefix $(LIBDIR)/, libdashee.so)
BINARIES := $(addprefix $(BINDIR)/, servod)
TESTS := $(addprefix $(TESTDIR)/, testUART testGPIO testDummy)

# Compiler options
WOPTIONS=-Wall -fPIC
INCLUDES=-Iinclude -L$(LIBDIR)
CFLAGS=$(WOPTIONS) $(INCLUDES)
LFLAGS=-shared

# Release ID
RELEASEID?=$(shell svn info | grep -E '^Revision' | awk '{print $$2}')

# Create all required binaries, but in debug mode
# Use `make release`
all: debug
libraries: $(LIBRARIES)

# Creates the binaries, in non debug mode
release: $(BINARIES)

# A helpfull function for debug configurations
debug: CFLAGS+=-g -DDEBUG
debug: LFLAGS+=-g -DDEBUG
debug: test $(BINARIES)

# Create a compressed tar archive file, usefull for releases
# and packaging
tar:
	if [ -f dashee-$(RELEASEID).tar.gz ]; then \
	    echo "Tar file 'dashee-src-$(RELEASEID).tar.gz' already exist!";\
	    exit 1;\
	fi
	tar -zcf dashee-src-$(RELEASEID).tar.gz --exclude='*.o' src makefile makefile.common include tests
	@echo "Tar archive 'dashee-src-$(RELEASEID).tar.gz' created."

# This is our main handler for created directories,
# To add a directory to the list modify the DIRECTORIES
# Variable
$(DIRECTORIES):
	$(MKDIR) $@
	@echo "Directory '$@' Created"

# All of our objects are passed through this, To add a new object
# Add to the OBJECTS directory
$(OBJECTSTEST): CFLAGS+=-Wno-overflow
$(OBJECTSTEST): INCLUDES+=-Itests
$(OBJECTS) $(OBJECTSLIB) $(OBJECTSTEST): %.o: %.cpp
	@echo "Building object '$@'"
	$(CC) $(CFLAGS) -c $< -o $@

# Log shared object
$(LIBDIR)/libdashee.so: $(LIBDIR) $(OBJECTSLIB) | $(LIBDIR)
	@echo "Building lib 'libdashee.so'"
	$(CC) $(LFLAGS) -Wl,-soname,$@ -o $@ $(OBJECTSLIB)

# Our main program that uses the objects
$(BINDIR)/servod: src/servod.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	@echo "Building binary 'servod'"
	$(CC) $(CFLAGS) $(OBJECTS) -ldashee $< -o $@

# Build and run all the tests
test: testbuild binfile
	@echo "\nRUNNING TESTS"
	bin/runtest dummy 2> /dev/null
	@echo ""

# BUILD all the tests
testbuild: $(TESTS) $(BINDIR)/runtest

$(BINDIR)/runtest:
	install --mode=775 tests/runtest.sh $@

$(TESTDIR)/testDummy: tests/testDummy.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	@echo "Building test:binary 'testDummy'"
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testUART: tests/testUART.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	@echo "Building test:binary 'testDummy'"
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testGPIO: tests/testGPIO.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	@echo "Building test:binary 'testGPIO'"
	$(CC) $(CFLAGS) -Itests -Wno-overflow $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

# Our test build, builds the dummy bin file, called Servo.bin
# Inside our bin directory
binfile: $(DATADIR)/Servo.bin

# This is a test bin directory, that is set as null of 38 bytes
# It represents our dump servo, for testing
$(DATADIR)/Servo.bin: | $(DATADIR)
	@echo "Building data 'data/Servo.bin'"
	dd if=/dev/zero of=$(DATADIR)/Servo.bin bs=1 count=0 seek=38 >/dev/null

# Builds the documentation
documentation:
	@echo "Building documentation 'docs/doxygen.conf'"
	doxygen docs/doxygen.conf > /dev/null

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
clean: cleantest
	@echo "Deleting 'src/*.o' files recursively"
	$(RM) $(shell find src -name "*.o")
	$(RM) $(shell find tests -name "*.o")
	@echo "Deleting binary and library directories"
	$(RM) $(BINDIR) $(LIBDIR)
	@echo "Deleting 'tags'"
	$(RM) tags

cleanall: clean
	@echo "Deleting all directories"
	$(RM) $(DIRECTORIES)
	@echo "Deleting 'etc'"
	@echo "Deleting documentation"
	$(RM) docs/html
	$(RM) docs/xml
