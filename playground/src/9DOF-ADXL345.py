#!/usr/bin/python

'''
This python program sets the ADXL345 and reads the Acceleration values from it.
Full documentation of the ADXL345 accelerometer can be found on:
    https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf

The example of the source code is morphed from 
https://github.com/pimoroni/adxl345-python
'''

import smbus
import time
import math

##
# Gets the two's int into the correct value required
#
# @param val the value to convert
# @param len the length of the value
#
# @returns the converted value
def twosToInt(val, len):
 
    # Convert twos compliment to integer
    if(val & (1 << len - 1)):
        val = val - (1<<len)

    return val

##
# Enable the measurement value
#
# @param bus to write
# @param address the device address
def enableMeasurement(bus, address):
    bus.write_byte_data(address, 0x2D, 0x08)

##
# Set the bandwidth rate
#
# @param bus to write
# @param address the device address
# @param rate_flag The value of the bandwidth
def setBandwidthRate(bus, address, hz):
    bus.write_byte_data(address, 0x2C, hz)

##
# Set the measurement range for 10-bit readings
#
# @param bus to write
# @param address of the bus
# @param range_flag The range [ 0, 1, 2, 3 ] to set the system
def setRange(bus, address, range_flag):

    # Read
    register = 0x31

    # Read old values from the server
    value = bus.read_byte_data(address, register)

    # Wipe the first 4 bit register values
    value &= ~0x0F;

    # Change the range byte1 + byte0
    value |= (range_flag & 0x03);

    # Enable full resolution
    value |= 0x08;

    # Write to the server
    bus.write_byte_data(address, register, value)


##
# Reads from our accelerometer and returns the exact acceleration values
# represented in acceleration m/s^2 values in each given axis [ X, Y, Z ]
#
# @param bus to read/write
# @param address of the bus
def getValue(bus, address):
    # Get 6 bytes from the data register (0x32)
    bytes = bus.read_i2c_block_data(address, 0x32, 6)

    valX = bytes[0] | (bytes[1] << 8)
    valY = bytes[2] | (bytes[3] << 8)
    valZ = bytes[4] | (bytes[5] << 8)

    valX = twosToInt(valX, 16);
    valY = twosToInt(valY, 16);
    valZ = twosToInt(valZ, 16);

    # How many g's am I accelerating, 0.00415 mg seems
    # to be the most nominal value to get the correct bearings
    #valX *= 0.00390625
    #valY *= 0.00390625
    #valZ *= 0.00390625

    # Given earths gravity what is my acceleration m/s^2
    #valX *= 9.80665
    #valY *= 9.80665
    #valZ *= 9.80665

    # Get some rounding going before returning home
    valX = round(valX, 7)
    valY = round(valY, 7)
    valZ = round(valZ, 7)
    
    return [ valX, valY, valZ ]

# Set some globals
bus = smbus.SMBus(1)
address = 0x53

setBandwidthRate(bus, address, 0x0B);
setRange(bus, address, 0x01);
enableMeasurement(bus, address);

# Loop through and get the values
while True:
    
    (valX, valY, valZ) = getValue(bus, address);

    print \
        "{0: 12f}".format(valX), \
        "{0: 12f}".format(valY), \
        "{0: 12f}".format(valZ)

    time.sleep(0.04)
