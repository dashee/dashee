#!/usr/bin/python

import smbus
import time
import math

def twosToInt(val, len):
 
    # Convert twos compliment to integer
    if(val & (1 << len - 1)):
        val = val - (1<<len)

    return val

bus = smbus.SMBus(1)
address = 0x1e

#bus.write_byte_data(address, 0x00, 0x00)
#bus.write_byte_data(address, 0x01, 0x00)
bus.write_byte_data(address, 0x02, 0x00)

# Important for setup
time.sleep(0.01)

while True:

    # Get the values from the server
    valX = (bus.read_byte_data(address, 0x03) << 8) | bus.read_byte_data(address, 0x04)
    valY = (bus.read_byte_data(address, 0x05) << 8) | bus.read_byte_data(address, 0x06)
    valZ = (bus.read_byte_data(address, 0x07) << 8) | bus.read_byte_data(address, 0x08)

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

    # Print the value to the output
    print "{0:-3f}".format(radians), "{0:-3f}".format(math.floor(radians * 180 / math.pi))
    
    bus.write_byte(address, 0x03)

    
    time.sleep(0.02)
