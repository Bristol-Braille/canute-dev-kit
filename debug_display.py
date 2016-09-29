#!/usr/bin/env python
from __future__ import print_function
from __future__ import unicode_literals
import serial
import sys

#./debug_display.py sep means seperate the output with a pipe character
if sys.argv[-1][:3] == 'sep':
    seperator = '|'
else:
    seperator = ''


def pin_num_to_unicode(pin_num):
    return unichr(pin_num+10240)

with serial.Serial('/dev/ttyUSB0', 115200) as ser:
    while 1:
        line = ser.readline()
        evens = line[0:-1:2]
        odds = line[1:-1:2]
        output = ''
        for i,c in enumerate(evens):
            if c != '\r':
                pin_num = int(c) | (int(odds[i]) << 3)
                output += seperator + pin_num_to_unicode(pin_num)
        print(output)
