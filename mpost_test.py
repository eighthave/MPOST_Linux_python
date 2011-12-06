#!/usr/bin/python

import time
import mpost

m = mpost.CAcceptor()
m.open("/dev/loc-bill-ttyUSB0", mpost.powerup.A)

m.acceptbills = True

time.sleep(10)

m.close()
