# Dashee
Dashee is in place replacements for conventional Radio transmission. It is designed to provide long range communications through protocols such as 3G.

Dashee contains a program called `servo` which provides a UDP server commands can be sent through using the Dashee protocol.

## Getting started
The program is mainly built in C++ so you will need to build the software using make and then you can run it using docker

### To build try:

    $ make clean all -s

### Starting the program (in dummy mode)

    $ bin/servod --config=files/examples/servod-dummy.conf

You can run the servo program inside [docker](https://github.com/dashee/dashee/wiki/Docker).

---

For more see the wiki https://github.com/dashee/dashee/wiki.
