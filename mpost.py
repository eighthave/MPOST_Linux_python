#!/usr/bin/env python2.6

import time
from ctypes import *

cdll.LoadLibrary('./libpympost.so')
mpost = CDLL('./libpympost.so')

mpost.mpost_open('/dev/ttyUSB0')
print("accept bills true")
mpost.mpost_acceptbills(1)
time.sleep(10)
mpost.mpost_return()
time.sleep(2)
mpost.mpost_close()
