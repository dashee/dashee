#!/usr/bin/python

'''
This python program reads the compas HMC5883L and returns the current degrees 
the compass is pointing to.

TODO: still need to fix the actual values, I believe the values are off
'''
import smbus
import time
import math

# Define some Globals
bus = smbus.SMBus(1)
address = 0x1e

# Set up the program to continious mode, and give it time to do this by sleeping
# the program
bus.write_byte_data(address, 0x02, 0x00)
time.sleep(0.01)

# For every 0.02 of a second read the updated buffer and convert it into
# radians for printing
while True:

    # Get the values from the server
    valX = (bus.read_byte_data(address, 0x03) << 8) \
        | bus.read_byte_data(address, 0x04)
    valY = (bus.read_byte_data(address, 0x05) << 8) \
        | bus.read_byte_data(address, 0x06)
    valZ = (bus.read_byte_data(address, 0x07) << 8) \
        | bus.read_byte_data(address, 0x08)

    # Update the values to be of two compliemnt
    valX = twosToInt(valX, 16);
    valY = twosToInt(valY, 16);
    valZ = twosToInt(valZ, 16);

    # Change valX and valY to radians
    radians = math.atan2(valY, valX)
    radians += -0.0197

    # Compensate for errors
    if radians < 0:
        radians += 2*math.pi
    if radians > 2*math.pi:
        radians -= 2*math.pi

    # Turn radians into degrees
    degrees = math.floor(radians * 180 / math.pi)

    # Print the value to the output
    print "{0:-3f}".format(radians), "{0:-3f}".format(degrees)
    
    # Sleep to try to keep a steady tick
    time.sleep(0.02)
