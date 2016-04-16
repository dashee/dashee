# Dashee
This is the dashee server, it is a collection of C++ libraries with a
program called `servod`. The `servod` program uses the library and runs
a server so commands can be sent down a UDP protocol

---

## Getting started
The program is mainly built in C++ so you will need to build the software using make and then you can run it using docker

### To build try:

    $ make clean all -s

### Starting the program (in dummy mode)

    $ bin/servod --config=files/examples/servod-dummy.conf

### Running inside a **docker** container:
Dashee can run inside docker (great for those with a mac like me :D).
To do this build the image once

    $ docker build -t dashee:dev .

Then start a shell so you can run the commands:

    $ docker run -it --rm -v $(pwd):/code dashee:dev

Please see https://github.com/dashee-bot/dashee/wiki
for for more detailed information
