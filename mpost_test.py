#!/usr/bin/python

import time
import glob
import mpost

acceptors = []

for f in glob.glob('/dev/loc-bill-ttyUSB*'):
    m = mpost.CAcceptor()
    m.open(f, mpost.powerup.A)
    # sleep after opening since it can take a while to get
    time.sleep(5)
    print 'm.devicestate: ',
    print m.devicestate
    m.autostack = True
    m.acceptbills = True
    acceptors.append(m)
    print "device: "
    print m.deviceportname
    print m.devicemodel
#    print m.devicetype
    print m.devicerevision
    print 'm.bill: ',
    print m.bill
    print 'm.billtypes: ',
    print m.billtypes
    print 'm.billvalues: '
    setbillvalues = []
    for bill in m.billvalues:
        if bill[0] != 'USD' or bill[0] != 'RUB':
            setbillvalues.append(bill)
            print bill[0]
        else:
            print 'NOT: ',
            print bill
    m.autostack = False
    m.acceptbills = False
    time.sleep(6)
    m.close()
