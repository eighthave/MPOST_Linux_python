#!/usr/bin/env python2.6

import time
import sys
from ctypes import *

class MPOST():
    '''
    class for receiving info from an MEI Bill Acceptor following the MEI Point
    of Service Toolkit (MPOST)
    '''

    instances = 0 # count of instances for referencing C++ CAcceptor struct

    # all available event types
    (Events_Begin,
     ConnectedEvent,
     EscrowEvent,
     PUPEscrowEvent,
     StackedEvent,
     ReturnedEvent,
     RejectedEvent,
     CheatedEvent,
     StackerFullEvent,
     CalibrateStartEvent,
     CalibrateProgressEvent,
     CalibrateFinishEvent,
     DownloadStartEvent,
     DownloadRestartEvent,
     DownloadProgressEvent,
     DownloadFinishEvent,
     PauseDetectedEvent,
     PauseClearedEvent,
     StallDetectedEvent,
     StallClearedEvent,
     JamDetectedEvent,
     JamClearedEvent,
     PowerUpEvent,
     InvalidCommandEvent,
     CashBoxAttachedEvent,
     CashBoxRemovedEvent,
     DisconnectedEvent,
     Events_End) = map(c_int, xrange(28))

    CALLBACK = CFUNCTYPE(None, c_int, c_char_p)
    
    MAX_INSTANCES = 16
    
    cdll.LoadLibrary('./libpympost.so')
    clib = CDLL('./libpympost.so')

    def __init__(self):
        if MPOST.instances < MPOST.MAX_INSTANCES:
            self.instance = MPOST.instances
            MPOST.clib.mpost_setup(self.instance)
            MPOST.instances += 1
        else:
            raise Exception('No more instances, max: ', str(MPOST.MAX_INSTANCES))

    def open(self, tty='/dev/ttyUSB0'):
        '''open the connection to the device'''
        MPOST.clib.mpost_open(self.instance, tty)

    def close(self):
        '''close the connection to the device'''
        MPOST.clib.mpost_close(self.instance)

    def returnbill(self):
        '''return the bill currently sitting in escrow'''
        MPOST.clib.mpost_return(self.instance)

    def acceptbills(self, boolean):
        '''set whether the acceptor will take bills or not'''
        MPOST.clib.mpost_acceptbills(self.instance, boolean)

    def autostack(self, boolean):
        '''set whether the acceptor should automatically stack the bills and
        skip the escrow'''
        MPOST.clib.mpost_autostack(self.instance, boolean)

    def setcallback(self, event, callback):
        '''attach a callback function to an event type.  The callback function
        should have two parameters: a int value and a string for data'''
        MPOST.clib.mpost_setcallback(self.instance, event, callback)


#------------------------------------------------------------------------------#
# for testing from the command line:
def main(argv):

    connectedcallback = MPOST.CALLBACK(connected)
    disconnectedcallback = MPOST.CALLBACK(disconnected)
    escrowcallback = MPOST.CALLBACK(escrow)
    stackedcallback = MPOST.CALLBACK(stacked)
    returnedcallback = MPOST.CALLBACK(returned)
    stackerfullcallback = MPOST.CALLBACK(stackerfull)

    mpost0 = MPOST()
    mpost0.open('/dev/loc-bill-ttyUSB0')
    mpost0.setcallback(MPOST.ConnectedEvent, connectedcallback)
    mpost0.setcallback(MPOST.DisconnectedEvent, disconnectedcallback)
    mpost0.setcallback(MPOST.EscrowEvent, escrowcallback)
    mpost0.setcallback(MPOST.StackedEvent, stackedcallback)
    mpost0.setcallback(MPOST.ReturnedEvent, returnedcallback)
    mpost0.setcallback(MPOST.StackerFullEvent, stackerfullcallback)

    mpost1 = MPOST()
    mpost1.open('/dev/loc-bill-ttyUSB1')
    mpost1.setcallback(MPOST.ConnectedEvent, connectedcallback)
    mpost1.setcallback(MPOST.DisconnectedEvent, disconnectedcallback)
    mpost1.setcallback(MPOST.EscrowEvent, escrowcallback)
    mpost1.setcallback(MPOST.StackedEvent, stackedcallback)
    mpost1.setcallback(MPOST.ReturnedEvent, returnedcallback)
    mpost1.setcallback(MPOST.StackerFullEvent, stackerfullcallback)

    mpost0.acceptbills(True)
    mpost1.acceptbills(True)
    time.sleep(20)
    mpost0.returnbill()
    mpost1.returnbill()
    time.sleep(2)
    mpost0.close()
    mpost1.close()
    
if __name__ == "__main__":

    # event callbacks, not all events are implemented...
    def connected(value, datastr):
        print('connected: ' + datastr)

    def disconnected(value, datastr):
        print('disconnected: ' + datastr)

    def escrow(value, datastr):
        print('escrow: ' + datastr)

    def stacked(value, datastr):
        print('stacked: ' + datastr)

    def returned(value, datastr):
        print('returned: ' + datastr)

    def stackerfull(value, datastr):
        print('stackerfull: ' + datastr)

    main(sys.argv[1:])
