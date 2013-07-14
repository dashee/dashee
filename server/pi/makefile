include makefile.common

WOPTIONS=-Wall -fPIC
INCLUDES=-Iinclude -Llib64
CFLAGS=$(WOPTIONS) $(INCLUDES)
LFLAGS=-shared

# Set directories as variables
BINDIR=bin
LIBDIR=lib
LIB64DIR=lib64
DATADIR=data
DIRECTORIES:= $(BINDIR) $(LIBDIR) $(LIB64DIR) $(DATADIR) 

# All the objects that are built
OBJECTS := $(addprefix src/, Servo.o Servo/USB.o Servo/Dummy.o Server.o\
		Server/UDP.o ServoController.o ServoController/USB.o \
		ServoController/Dummy.o Config/Servod.o\
		ServoController/UART.o Servo/UART.o)
OBJECTSLIB := $(addprefix src/, Log.o Config.o Common.o)

# All the binaries which will be built
#SO := $(addprefix lib/,)
SO64 := $(addprefix lib64/, libdashee.so)
BINARIES := $(addprefix $(BINDIR)/, servod)

RELEASEID?=$(shell svn info | grep -E '^Revision' | awk '{print $$2}')

# Create all required binaries, but in debug mode
# Use `make release`
all: debug
libraries: $(SO)
libraries64: $(SO64)

# Creates the binaries, in non debug mode
release: $(BINARIES)

# A helpfull function for debug configurations
debug: CFLAGS += -g -DDEBUG 
debug: LFLAGS += -g -DDEBUG
debug: $(BINARIES)

# Create a compressed tar archive file, usefull for releases
# and packaging
tar: 
	@if [ -f dashee-$(RELEASEID).tar.gz ]; then \
	    echo "Tar file 'dashee-$(RELEASEID).tar.gz' already exist!";\
	    exit 1;\
	fi
	@tar -zcf dashee-$(RELEASEID).tar.gz --exclude='*.o' src makefile makefile.common include tests
	@echo "Tar archive 'dashee-$(RELEASEID).tar.gz' created."

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
$(LIB64DIR)/libdashee.so: $(LIB64DIR) $(OBJECTSLIB)
	@echo "Building lib 'libdashee.so'"
	@$(CC) $(LFLAGS) -Wl,-soname,$@ -o $@ $(OBJECTSLIB)

# Our main program that uses the objects
$(BINDIR)/servod: src/servod.cpp $(BINDIR) $(SO64) $(OBJECTS)
	@echo "Building binary 'servod'"
	@$(CC) $(CFLAGS) $(OBJECTS) -ldashee $< -o $@

# Make the tests
test: $(OBJECTS) $(BINDIR) $(SO64)
	@mkdir -p $(BINDIR)/tests
	@echo "Building test:binary 'ServoControllerUART'"
	@$(CC) $(CFLAGS) -Isrc tests/ServoControllerUART.cpp \
	    src/Servo.o src/Servo/UART.o src/ServoController.o src/ServoController/UART.o \
	    -ldashee \
	    -o $(BINDIR)/tests/ServoControllerUART
	@echo "Building test:binary 'ServerUDP'"
	@$(CC) $(CFLAGS) -Isrc -ldashee tests/ServerUDP.cpp \
	    src/Server.o src/Server/UDP.o \
	    -ldashee \
	    -o $(BINDIR)/tests/ServerUDP

# Remove only the tests
cleantest:
	@$(RM) $(BINDIR)/tests

# Our test build, builds the dummy bin file, called Servo.bin
# Inside our bin directory
binfile: $(DATADIR) $(DATADIR)/Servo.bin

# This is a test bin directory, that is set as null of 38 bytes
# It represents our dump servo, for testing
$(DATADIR)/Servo.bin:
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
	@echo "Deleting directories"
	@$(RM) $(DIRECTORIES)
	@echo "Deleting 'tags'"
	@$(RM) tags
