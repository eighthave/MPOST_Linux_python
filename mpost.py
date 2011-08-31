#!/usr/bin/env python2.6

import time
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


CALLBACK = CFUNCTYPE(None, c_int, c_char_p)

def callbacktest(value, datastr):
    print('received callback: ' + str(value) + ' ' + datastr)

cdll.LoadLibrary('./libpympost.so')
mpost = CDLL('./libpympost.so')

mpost.mpost_setup()
callback = CALLBACK(callbacktest)
mpost.mpost_setcallback(ConnectedEvent, callback)

mpost.mpost_open('/dev/ttyUSB0')
mpost.mpost_acceptbills(1)
print("accept bills true")
time.sleep(10)
mpost.mpost_return()
time.sleep(2)
mpost.mpost_close()
