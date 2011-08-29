#!/usr/bin/env python2.6

from ctypes import *

cdll.LoadLibrary('./libMPOST_Linux.so')
mpost = CDLL('./libMPOST_Linux.so')


