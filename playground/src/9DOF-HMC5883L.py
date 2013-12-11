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
time.sleep(0.01)

while True:

    bus.write_byte(address, 0x03)

    valX = (bus.read_byte_data(address, 0x03) << 8) | bus.read_byte_data(address, 0x04)
    valY = (bus.read_byte_data(address, 0x05) << 8) | bus.read_byte_data(address, 0x06)
    valZ = (bus.read_byte_data(address, 0x07) << 8) | bus.read_byte_data(address, 0x08)

    valX = twosToInt(valX, 16);
    valY = twosToInt(valY, 16);
    valZ = twosToInt(valZ, 16);

    radians = math.atan2(round(valX * 1.3, 4), round(valY * 1.3, 4))

    if radians < 0:
        radians += 2*math.pi
    elif radians > 2*math.pi:
        radians -= 2*math.pi

    print "{0:-3f}".format(radians * (180/math.pi))

#    print math.atan2(valX, valY);
    
    time.sleep(0.01)
