#!/bin/bash
# 
# This program is a simple wrapper that runs programs
# which it find by argument, and checks there exit code
# if all is well prints a pass, otherwise fail and moves
# along to the next one.
# 
#
# @compiled - bin/runtests
# @author Shahmir Javaid

# Go through each test and run it
for t in "$@"; 
do
    BASE=$(basename $t);

    # If the test does not exist skip
    if [ ! -f $t ]; then
        echo "Tests '$t' not found skipping..."
        continue;
    fi;

    # Run the test
    ./$t

    # Check exit status
    if [ $? -ne 0 ]; then
        echo "Test '$BASE' failed!";
    else
        echo "Test '$BASE' passed.";
    fi
done;
