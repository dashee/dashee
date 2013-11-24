##
# Build script, allows one step builds, to get started, try
#
# make all
# make INSTALLDIR=$(mktemp -d) install
# make clean
# 
# try the `-s` option to make for pretty print
#
# @author Shahmir Javaid

# Include a common set of options
include makefile.common

# The directories to build
DIRECTORIES:= $(BINDIR) $(LIBDIR) $(DATADIR) $(TESTDIR) $(INITDIR)

# All the objects that are built
OBJECTS := $(addprefix src/,)
OBJECTSLIB := $(addprefix src/, Log.o Config.o GPIO.o Servo.o \
    		Servo/Dummy.o Servo/USB.o Servo/UART.o Server.o \
		ServoController.o ServoController/Dummy.o ServoController/USB.o \
		ServoController/UART.o Server/UDP.o common.o daemon.o signal.o \
		Vehicle.o Vehicle/Car.o Vehicle/Multirotor.o Vehicle/Multirotor/Quad.o \
		Vehicle/Multirotor/Quad/X.o)
OBJECTSTEST := $(addprefix tests/, dashee.o ServoController.o ServoController/Dummy.o\
    		 ServoController/UART.o GPIO.o Servo.o Servo/UART.o Servo/Dummy.o \
		 Config.o Vehicle.o Vehicle/Car.o)

# All the binaries which will be built
LIBRARIES := $(addprefix $(LIBDIR)/, libdashee.so)
BINARIES := $(addprefix $(BINDIR)/, servo servod)
TESTS := $(addprefix $(TESTDIR)/, testConfig testUART testGPIO testDummy testVehicleCar)

# Certain global variables used for packaging and installing
REVISIONID?=$(shell svn info | grep -E '^Revision' | awk '{print $$2}')
BUILDID?=$(REVISIONID)
INSTALLROOT?=./dashee-$(BUILDID)-$(BIT)

# Create all required binaries, but in debug mode
# Use `make release`
all: debug
libraries: $(LIBRARIES)

# Creates the binaries, in non debug mode
release: $(BINARIES) $(LIBRARIES)

# A helpfull function for debug configurations
debug: CFLAGS:=-g -DDEBUG $(CFLAGS)
debug: LFLAGS:=-g -DDEBUG $(LFLAGS)
debug: test $(BINARIES)

# This is our main handler for created directories,
# To add a directory to the list modify the DIRECTORIES
# Variable
$(DIRECTORIES):
	$(MKDIR) $@
	$(call print,"Building","directory","$@")

# All of our objects are passed through this, To add a new object
# Add to the OBJECTS directory
$(OBJECTSTEST): CFLAGS+=-Wno-overflow -Itests
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

# Build and run all the tests
test: testbuild binfile
	@echo "\nRUNNING TESTS"
	bin/runtest $(TYPE) 2> /dev/null
	@echo ""

# BUILD all the tests
test: CFLAGS:=-g -DDEBUG $(CFLAGS) -Itests
testbuild: $(TESTS) $(BINDIR)/runtest

$(BINDIR)/runtest: $(SCRIPTSDIR)/runtest.sh
	$(call print,"Building","script","$@")
	install --mode=775 $< $@

$(TESTDIR)/testDummy: tests/testDummy.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testUART: tests/testUART.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testGPIO: tests/testGPIO.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testConfig: tests/testConfig.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

$(TESTDIR)/testVehicleCar: tests/testVehicleCar.cpp \
    $(LIBRARIES) $(OBJECTS) $(OBJECTSTEST) | $(TESTDIR)
	$(call print,"Building","tests","$@")
	$(CC) $(CFLAGS) $< $(OBJECTS) $(OBJECTSTEST) -ldashee -lcppunit -o $@

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

# Install the executables
install: $(BINDIR)/servod $(LIBDIR)/libdashee.so documentation
	$(call print,"Installing","library","$(INSTALLROOT)/$(LIBDIR)/libdashee.so")
	[ -d $(INSTALLROOT)/$(LIBDIR) ] || $(MKDIR) $(INSTALLROOT)/$(LIBDIR)
	install --mode=755 $(LIBDIR)/libdashee.so \
	    $(INSTALLROOT)/$(LIBDIR)/libdashee.so
	
	$(call print,"Installing","binary","$(INSTALLROOT)/usr/bin/dashee-servod")
	[ -d $(INSTALLROOT)/usr/bin/ ] || $(MKDIR) -p $(INSTALLROOT)/usr/bin
	install --mode=755 $(BINDIR)/servod \
	    $(INSTALLROOT)/usr/bin/dashee-servod
	
	$(call print,"Installing","file","$(INSTALLROOT)/var/log/dashee/servod.log")
	[ -d $(INSTALLROOT)/var/log/dashee ] || $(MKDIR) -p $(INSTALLROOT)/var/log/dashee
	touch $(INSTALLROOT)/var/log/dashee/servod.log
	
	$(call print,"Installing","file","$(INSTALLROOT)/etc/init.d/dashee-servod")
	[ -d $(INSTALLROOT)/etc/init.d ] || $(MKDIR) -p $(INSTALLROOT)/etc/init.d
	install --mode=755 \
	    $(SCRIPTSDIR)/init.d/dashee-servod $(INSTALLROOT)/etc/init.d/dashee-servod
	
	$(call print,"Installing","file","$(INSTALLROOT)/etc/dashee/servod.conf")
	[ -d $(INSTALLROOT)/etc/dashee ] || $(MKDIR) $(INSTALLROOT)/etc/dashee
	touch $(INSTALLROOT)/etc/dashee/servod.conf
	
	$(call print,"Installing","directory","$(INSTALLROOT)/var/run/dashee")
	[ -d $(INSTALLROOT)/var/run/dashee ] || $(MKDIR) -p $(INSTALLROOT)/var/run/dashee
	
	$(call print,"Installing","doc","$(INSTALLROOT)/usr/share/doc/libdashee/")
	[ -d $(INSTALLROOT)/usr/share/doc/libdashee ] || $(MKDIR) \
	    $(INSTALLROOT)/usr/share/doc/libdashee
	cp -R docs/html $(INSTALLROOT)/usr/share/doc/libdashee/.
	install --mode=644 files/LICENSE $(INSTALLROOT)/usr/share/doc/libdashee/.
	echo "Date: $$(date)" > $(INSTALLROOT)/usr/share/doc/libdashee/VERSION
	echo "Machine: $$(hostname -f)" >> $(INSTALLROOT)/usr/share/doc/libdashee/VERSION
	svn info | grep "Last Changed Rev:" | awk '{print "Last Revision: " $$4}' >> \
	    $(INSTALLROOT)/usr/share/doc/libdashee/VERSION
	svn info | grep "Last Changed Date:" | \
	    awk '{print "Last Revision Date: " $$4 " " $$5 " " $$6}' >> \
	    $(INSTALLROOT)/usr/share/doc/libdashee/VERSION

# Create a compressed tar archive file, usefull for releases
# and packaging
#
# Build a package of binaries
package: INSTALLROOT=./dashee-$(BUILDID)-$(BIT)
package: FILE=dashee-$(BUILDID)-$(BIT)
package: clean test install release
	$(call print,"Building","file","$(FILE).tar.$(COMPRESSTYPE)")
	tar -acf $(FILE).tar.$(COMPRESSTYPE) $(INSTALLROOT)
	$(RM) $(INSTALLROOT)

# Build only the nightly build, it has no rev number just Revision id
package-nightly: FILE=dashee-$(BUILDID)-$(BIT)
package-nightly: package
	$(call print,"Building","file","$(FILE)-nightly.tar.$(COMPRESSTYPE)")
	mv $(FILE).tar.$(COMPRESSTYPE) $(FILE)-nightly.tar.$(COMPRESSTYPE)

# Build a package with all source code, but add a subfolder using xform to encapsulate
# the files so when extracted all files are held inside a folder
package-src:
	$(call print,"Building","file","dashee-src-$(BUILDID).tar.$(COMPRESSTYPE)")
	# Tar up temporarily, so it can be extracted to a folder
	tar --xform='s%^%dashee-$(BUILDID)-src/%' --exclude='*.o' \
	    -acf dashee-$(BUILDID)-src.tar.$(COMPRESSTYPE) \
	   src makefile makefile.common include tests files docs scripts

# Publish changes to a server given by .PUBLISH_HOST, if no .PUBLISH_HOST file
# exists the build will fail
publish: .PUBLISH_HOST package
publish-nightly: .PUBLISH_HOST package-nightly
publish-src: .PUBLISH_HOST package-src

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
	$(call print,"Deleting","directory","doc/html")
	$(RM) docs/html
	$(call print,"Deleting","directory","doc/xml")
	$(RM) docs/xml

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
	$(call print,"Deleting","objects","find *.o")
	find src/ -name "*.o" -type f -delete
	find tests/ -name "*.o" -type f -delete
