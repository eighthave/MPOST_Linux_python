#!/usr/bin/env python2.6

import time
import sys
from ctypes import *

class MPOST():
    '''
    class for receiving info from an MEI Bill Acceptor following the MEI Point
    of Service Toolkit (MPOST)
    '''

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

    def __init__(self):
        cdll.LoadLibrary('./libpympost.so')
        self.clib = CDLL('./libpympost.so')
        self.clib.mpost_setup()

    def open(self, tty='/dev/ttyUSB0'):
        '''open the connection to the device'''
        self.clib.mpost_open(tty)

    def close(self):
        '''close the connection to the device'''
        self.clib.mpost_close()

    def returnbill(self):
        '''return the bill currently sitting in escrow'''
        self.clib.mpost_return()

    def acceptbills(self, boolean):
        '''set whether the acceptor will take bills or not'''
        self.clib.mpost_acceptbills(boolean)

    def autostack(self, boolean):
        '''set whether the acceptor should automatically stack the bills and
        skip the escrow'''
        self.clib.mpost_autostack(boolean)

    def setcallback(self, event, callback):
        '''attach a callback function to an event type.  The callback function
        should have two parameters: a int value and a string for data'''
        self.clib.mpost_setcallback(event, callback)


#------------------------------------------------------------------------------#
# for testing from the command line:
def main(argv):
    mpost = MPOST()
    mpost.open('/dev/ttyUSB0')

    connectedcallback = MPOST.CALLBACK(connected)
    disconnectedcallback = MPOST.CALLBACK(disconnected)
    escrowcallback = MPOST.CALLBACK(escrow)
    stackedcallback = MPOST.CALLBACK(stacked)
    returnedcallback = MPOST.CALLBACK(returned)
    stackerfullcallback = MPOST.CALLBACK(stackerfull)

    mpost.setcallback(MPOST.ConnectedEvent, connectedcallback)
    mpost.setcallback(MPOST.DisconnectedEvent, disconnectedcallback)
    mpost.setcallback(MPOST.EscrowEvent, escrowcallback)
    mpost.setcallback(MPOST.StackedEvent, stackedcallback)
    mpost.setcallback(MPOST.ReturnedEvent, returnedcallback)
    mpost.setcallback(MPOST.StackerFullEvent, stackerfullcallback)

    mpost.acceptbills(True)
    time.sleep(10)
    mpost.returnbill()
    time.sleep(2)
    mpost.close()
    
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
