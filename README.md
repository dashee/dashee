# Dashee
Dashee is in place replacements for conventional Radio transmission.
It is designed to provide long range communications through protocols such
as 3G.

Dashee contains a program called `servo` which provides a UDP server
commands can be sent through using the Dashee protocol.

## Getting started
The program is mainly built in C++ so you will need to build the
software using make and then you can run it using docker

### Create a `build` directory
So we don't ruin our **source root**, and it is easy to clean by just
deleting the build directory

    $ mkdir build
    $ cd build

### To build try:

    $ cmake ..
    $ make

### Starting the program (in dummy mode). This is inside the build directory
    
    $ ./servod --config=files/examples/servod-dummy.conf

You can run the servo program inside
[docker](https://github.com/dashee/dashee/wiki/Docker).

---

For more see the wiki https://github.com/dashee/dashee/wiki.
