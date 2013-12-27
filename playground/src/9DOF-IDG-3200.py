#!/usr/bin/python

'''
This python program sets the ADXL345 and reads the Acceleration values from it.
Full documentation of the IDG-3200 gyro can be found on:
    https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf

The example of the source code is morphed from 
https://github.com/beli-sk/IMU_sensors/blob/master/itg3200.py
'''

import smbus
import time
import math

##
# Given the value of a word provided by X, transform it into readable values
# 
# @param x The word value to convert
#
def int_sw_swap(x):
    """Interpret integer as signed word with bytes swapped"""
    xl = x & 0xff
    xh = x >> 8
    xx = (xl << 8) + xh
    return xx - 0xffff if xx > 0x7fff else xx

##
# Set the sample rate for the Low Pass Filter and the Rate Divider
#
# @param bus The bus to write to
# @param address The bus address to write to
# @param lowPassFilter The value of the lpf
# @param rateDivider the value of the divider
#
def setSampleRate(bus, address, lowPassFilter, rateDivider):
    if not (lowPassFilter >= 0 and lowPassFilter <= 0x6):
        raise ValueError("Invalid low pass filter code (0-6).")
    if not (rateDivider >= 0 and rateDivider <= 0xff):
        raise ValueError("Invalid sample rate divider (0-255).")
    bus.write_byte_data(address, 0x15, rateDivider-1)
    bus.write_byte_data(address, 0x16, 0x18 | lowPassFilter)

##
# Get the value from the sensor, and return an array
#
# @param bus The bus to read from
# @param address The bus address to read from
#
# @returns array(x, y, z) The value of x, y and z
#
def getValue(bus, address):
    #bytes = bus.read_i2c_block_data(address, 0x1D, 6)
    
    valX = int_sw_swap(bus.read_word_data(address, 0x1d))
    valY = int_sw_swap(bus.read_word_data(address, 0x1f))
    valZ = int_sw_swap(bus.read_word_data(address, 0x21))

    valX *= 0.001
    valY *= 0.001
    valZ *= 0.001

    valX = round(valX, 4)
    valY = round(valY, 4)
    valZ = round(valZ, 4)
    
    return [ valX, valY, valZ ]

# Set some globals
bus = smbus.SMBus(1)
address = 0x68

# Initialize
setSampleRate(bus, address, 0, 8)

while True:
    (valX, valY, valZ) = getValue(bus, address);

    print "{0: 3f}".format(valX), "{0: 3f}".format(valY), "{0: 3f}".format(valZ)

    time.sleep(0.03)
