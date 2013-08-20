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
OBJECTS := $(addprefix src/, Servo.o Servo/USB.o Servo/Dummy.o Server.o\
		Server/UDP.o ServoController.o ServoController/USB.o \
		ServoController/Dummy.o Config/Servod.o\
		ServoController/UART.o Servo/UART.o)
OBJECTSLIB := $(addprefix src/, Log.o Config.o Common.o GPIO.o)

# All the binaries which will be built
#SO := $(addprefix lib/,)
LIBRARIES := $(addprefix $(LIBDIR)/, libdashee.so)
BINARIES := $(addprefix $(BINDIR)/, servod)
TESTS := $(addprefix $(TESTDIR)/, testServoControllerDummy testServoControllerUART)

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
debug: CFLAGS += -g -DDEBUG 
debug: LFLAGS += -g -DDEBUG
debug: $(BINARIES) tests

# Create a compressed tar archive file, usefull for releases
# and packaging
tar:
	@if [ -f dashee-$(RELEASEID).tar.gz ]; then \
	    echo "Tar file 'dashee-src-$(RELEASEID).tar.gz' already exist!";\
	    exit 1;\
	fi
	@tar -zcf dashee-src-$(RELEASEID).tar.gz --exclude='*.o' src makefile makefile.common include tests
	@echo "Tar archive 'dashee-src-$(RELEASEID).tar.gz' created."

# This is our main handler for created directories,
# To add a directory to the list modify the DIRECTORIES
# Variable
$(DIRECTORIES):
	@$(MKDIR) $@
	@echo "Directory '$@' Created"

# All of our objects are passed through this, To add a new object
# Add to the OBJECTS directory
$(OBJECTS) $(OBJECTSLIB): %.o: %.cpp
	@echo "Building object '$@'"
	@$(CC) $(CFLAGS) -c $< -o $@

# Log shared object
$(LIBDIR)/libdashee.so: $(LIBDIR) $(OBJECTSLIB) | $(LIBDIR)
	@echo "Building lib 'libdashee.so'"
	@$(CC) $(LFLAGS) -Wl,-soname,$@ -o $@ $(OBJECTSLIB)

# Our main program that uses the objects
$(BINDIR)/servod: src/servod.cpp $(LIBRARIES) $(OBJECTS) | $(BINDIR)
	@echo "Building binary 'servod'"
	@$(CC) $(CFLAGS) $(OBJECTS) -ldashee $< -o $@

# Tests
tests: CFLAGS += -g -DDEBUG 
tests: $(TESTS)
	install --mode=775 src/runtest.sh bin/runtest

$(TESTDIR)/testServoControllerDummy: tests/testServoControllerDummy.cpp $(LIBRARIES) $(OBJECTS) | $(TESTDIR)
	@echo "Building test:binary 'testServoControllerDummy'"
	@$(CC) $(CFLAGS) -Wno-overflow -Isrc $< \
	    src/ServoController/Dummy.o src/ServoController.o src/Servo.o src/Servo/Dummy.o \
	    -ldashee -lcppunit -o $@
$(TESTDIR)/testServoControllerUART: tests/testServoControllerUART.cpp $(LIBRARIES) $(OBJECTS) | $(TESTDIR)
	@echo "Building test:binary 'testServoControllerUART'"
	@$(CC) $(CFLAGS) -Wno-overflow -Isrc $< \
	    src/ServoController/UART.o src/ServoController.o src/Servo.o src/Servo/UART.o \
	    -ldashee -lcppunit -o $@


# Remove only the tests
cleantest:
	@$(RM) $(BINDIR)/tests

# Our test build, builds the dummy bin file, called Servo.bin
# Inside our bin directory
binfile: $(DATADIR)/Servo.bin

# This is a test bin directory, that is set as null of 38 bytes
# It represents our dump servo, for testing
$(DATADIR)/Servo.bin: | $(DATADIR)
	dd if=/dev/zero of=$(DATADIR)/Servo.bin bs=1 count=0 seek=38

# This will remove our data/Servo.bin file, to build it again 
cleandata:
	@$(RM) $(DATADIR)/Servo.bin

# Will generate ctags for vim
tags:
	@ctags-exuberant -R .
    
# Cleans all the .o files from our src directory
# And finally cleans all directories.
clean: cleantest
	@echo "Deleting 'src/*.o' files recursively"
	@$(RM) $(shell find src -name "*.o")
	@echo "Deleting binary and library directories"
	@$(RM) $(BINDIR) $(LIBDIR)
	@echo "Deleting 'tags'"
	@$(RM) tags

cleanall: clean
	@echo "Deleting all directories"
	@$(RM) $(DIRECTORIES)
	@echo "Deleting 'etc'"
	@$(RM) etc
