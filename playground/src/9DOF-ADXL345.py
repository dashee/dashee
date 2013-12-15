#!/usr/bin/python

'''
This python program sets the ADXL345 and reads the Acceleration values from it.
Full documentation of the ADXL345 acellerometer can be found on:
    https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
'''

import smbus
import time
import math

while True:

    xval = 1.0000000
    yval = 2.0000000
    zval = 3.0000000

    print "{0:-3f}".format(xval), "{0:-3f}".format(yval), "{0:-3f}".format(xval)

    time.sleep(0.2)
