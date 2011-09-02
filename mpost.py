#!/usr/bin/env python2.6

import time
import sys
from ctypes import *

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

# ------------------------------------------------------------------------
# event callbacks

CALLBACK = CFUNCTYPE(None, c_int, c_char_p)

def callbacktest(value, datastr):
    print('received callback: ' + str(value) + ' ' + datastr)

def connected(value, datastr):
    print('connected: ' + datastr)
    callbacktest(value, datastr)
connectedcallback = CALLBACK(connected)

def disconnected(value, datastr):
    print('disconnected: ' + datastr)
    callbacktest(value, datastr)
disconnectedcallback = CALLBACK(disconnected)

def escrow(value, datastr):
    print('escrow: ' + datastr)
    callbacktest(value, datastr)
escrowcallback = CALLBACK(escrow)

def stacked(value, datastr):
    print('stacked: ' + datastr)
    callbacktest(value, datastr)
stackedcallback = CALLBACK(stacked)

def returned(value, datastr):
    print('returned: ' + datastr)
    callbacktest(value, datastr)
returnedcallback = CALLBACK(returned)

def stackerfull(value, datastr):
    print('stackerfull: ' + datastr)
    callbacktest(value, datastr)
stackerfullcallback = CALLBACK(stackerfull)

# not all events are implemented...

#------------------------------------------------------------------------------#
# for testing from the command line:
def main(argv):
    cdll.LoadLibrary('./libpympost.so')
    mpost = CDLL('./libpympost.so')

    mpost.mpost_setup()
    mpost.mpost_autostack(1)
    mpost.mpost_setcallback(ConnectedEvent, connectedcallback)
    mpost.mpost_setcallback(DisconnectedEvent, disconnectedcallback)
    mpost.mpost_setcallback(EscrowEvent, escrowcallback)
    mpost.mpost_setcallback(StackedEvent, stackedcallback)
    mpost.mpost_setcallback(ReturnedEvent, returnedcallback)
    mpost.mpost_setcallback(StackerFullEvent, stackerfullcallback)

    mpost.mpost_open('/dev/ttyUSB0')
    mpost.mpost_acceptbills(1)
    print("accept bills true")
    time.sleep(10)
    mpost.mpost_return()
    time.sleep(2)
    mpost.mpost_close()
    
if __name__ == "__main__":
    main(sys.argv[1:])


