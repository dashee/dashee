#!/bin/bash

# Go through each test and run it
for t in $1; 
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
