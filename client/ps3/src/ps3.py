#!/usr/bin/python
#
# This program is designed to read from a playstation remote control
# and send its values back to Pi

import datetime
import io
import socket
import sys
import time

# Print usage on commandline invalid arguments
if (len(sys.argv) < 4):
    print "Program requires three arguments"
    print sys.argv[0], "<device>", "<ipaddress>", "<port>", "<type>"
    sys.exit(1)

# The buffer used to read from the controller and store into variable
bufferCommand = bytearray(49)
bufferServer = bytearray(3);

# Initilize our socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ipaddress = sys.argv[2]
port = int(sys.argv[3])

# Set the model type
if (len(sys.argv) == 5):
    modelType = sys.argv[4]
else:
    modelType = "Car"

# Choose buffer type
if (modelType == "Car"):
    bufferServer = bytearray(3)
elif (modelType == "Plane"):
    bufferServer = bytearray(5)
else:
    print "Invalid model, try Car or Plane"
    sys.exit(2)

# Initilize our general variables
TIMEOUT = 0.020
lastTime = time.time();

# Open the controller
controller = io.open(sys.argv[1], 'rb')

# Keep looping and reading the pscontroller
while True:

    # Read from the playstation controller
    controller.readinto(bufferCommand)

    # Update the currentTime
    currentTime = time.time();

    # If timeout is reached, send to the Pi
    if ((currentTime - lastTime) > TIMEOUT):

        # Great for debugging
        print "{0:-3d}".format(bufferCommand[7]), "{0:-3d}".format(bufferCommand[6]), "{0:-3d}".format(bufferCommand[8]),\
                "{0:-3d}".format(bufferCommand[9]), ((bufferCommand[19]+bufferCommand[18]))

        bufferServer[0] = 0

        # Car only takes Yaw and Throttle
        if (modelType == "Car"):
            bufferServer[1] = bufferCommand[6]
            bufferServer[2] = bufferCommand[9]
        # Plane takes Pitch, Roll, Yaw and Throttle
        elif(modelType == "Plane"):
            bufferServer[1] = bufferCommand[7]
            bufferServer[2] = bufferCommand[6]
            bufferServer[3] = bufferCommand[8]
            bufferServer[4] = bufferCommand[9]
            #bufferServer[4] = 50
	else:
	    continue

        # Send to the pi
        sock.sendto(bufferServer, (ipaddress, port))

        # Update the lastTime
        lastTime = currentTime
