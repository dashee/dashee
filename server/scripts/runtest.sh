#!/bin/bash
# 
# This program is a simple wrapper that runs programs
# which it find by argument, and checks there exit code
# if all is well prints a pass, otherwise fail and moves
# along to the next one.
#
# @author Shahmir Javaid

# Change the test to run depending on the first
# argument variable
RUN_TYPE=${1-dummy}

# Set the return Error code to 0 representing good
# It is only changed by the failed tests, so 1 will
# represent atleast one test failed
RETURN_EC=0

# List of all tests to run
TEST_GENERAL=
TEST_PI="testGPIO testUART"
TEST_DUMMY="testDummy testConfig"

# The directory where all the tests are stored
TESTDIR=./bin/tests

##
# Prints the status in a colorfull format
# 
# @param $1 the String representing "PASSED" or "FAILED"
# @param $2 the String representing the test
# 
printstatus()
{
    if [ $# -ne 2 ]; then
        echo "Invalid arguments to printstatus $@";
        exit 1;
    fi

    case "$1" in
        "PASSED" | "P" | "p" | 0)
            echo -en "\E[0;32;1mPASSED\E[0m"
            ;;
        *)
            echo -en "\E[0;31;1mFAILED\E[0m"
            ;;
    esac

    echo " '$2'"
}

runtest()
{
    # If the test does not exist skip
    if [ ! -f $TESTDIR/$1 ]; then
	echo "Tests '$1' not found skipping..."
	continue;
    fi;

    # Run the test
    $TESTDIR/$@
    TEST_EC=$?

    if [ $TEST_EC -ne 0 ]; then
	RETURN_EC=1
    fi

    printstatus $TEST_EC $1

}

##
# Run the set of test given by $@
#
# The parameters represents the tests to be ran.
# Adding this to the function makes life easier
#
# @param $@ the array of test values
#
# @returns 0 if all tests passed 1 if one failed
# @retval 0 All tests passed
# @retval 0 Atleast one test failed
#
runtests()
{
    # Go through each test and run it
    for t in "$@"; 
    do
        # Skip empty strings
        if [ "$t" == "" ]; then
            continue;
        fi

	runtest $t

    done;
}

# Run the general test that are not
# OS dependant
runtests $TEST_GENERAL

# Run the tests represented by the parameter
# $RUN_TYPE, default will exit out with fail
case "$RUN_TYPE" in 
    "pi")
        runtests $TEST_PI
	runtest testModelCar UART /dev/ttyAMA0 UDP 2097
        ;;
    "dummy")
        runtests $TEST_DUMMY
	runtest testModelCar dummy data/Servo.bin UDP 2097
        ;;
    *)
        echo "RUN_TYPE is not defined" >&2
        exit 1
        ;;
esac

exit $RETURN_EC;
