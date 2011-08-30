
/* this is the header for C programs (not C++) */

#include "mpost_int.h"

enum State
{
    Disconnected,
    Connecting,
    PupEscrow,
    Idling,
    Accepting,
    Escrow,
    Stacking,
    Stacked,
    Returning,
    Returned,
    Rejected,
    Stalled,
    Failed,
    CalibrateStart,
    Calibrating,
    DownloadStart,
    DownloadRestart,
    Downloading,
};

enum Event
{
	Events_Begin,
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
	Events_End
};

void mpost_open(char *portname);
void mpost_close();
/* return the bill that is currently sitting in escrow */
void mpost_return();
/* stack the bill that is currently sitting in escrow */
void mpost_stack();
void mpost_softreset();
void mpost_acceptbills(int enable);
void mpost_debug(int enable);
void mpost_setcallback(enum Event event, eventcallback callback);
