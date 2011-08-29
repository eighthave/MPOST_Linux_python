
void(*eventcallbacks[28])(int);

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
