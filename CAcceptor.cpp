#include <boost/python.hpp>
#include "Acceptor.h"

using namespace boost::python;
using namespace MPOST;


BOOST_PYTHON_MODULE(mpost)
{
    enum_<PowerUp>("powerup")
        .value("A", A)
        .value("B", B)
        .value("C", C)
        .value("E", E)
        ;

    enum_<State>("state")
        .value("disconnected", Disconnected)
        .value("connecting", Connecting)
        .value("pupescrow", PupEscrow)
        .value("idling", Idling)
        .value("accepting", Accepting)
        .value("escrow", Escrow)
        .value("stacking", Stacking)
        .value("stacked", Stacked)
        .value("returning", Returning)
        .value("returned", Returned)
        .value("rejected", Rejected)
        .value("stalled", Stalled)
        .value("failed", Failed)
        .value("calibratestart", CalibrateStart)
        .value("calibrating", Calibrating)
        .value("downloadstart", DownloadStart)
        .value("downloadrestart", DownloadRestart)
        .value("downloading", Downloading)
        ;

    enum_<Event>("event")
        .value("Events_Begin", Events_Begin)
        .value("ConnectedEvent", ConnectedEvent)
        .value("EscrowEvent", EscrowEvent)
        .value("PUPEscrowEvent", PUPEscrowEvent)
        .value("StackedEvent", StackedEvent)
        .value("ReturnedEvent", ReturnedEvent)
        .value("RejectedEvent", RejectedEvent)
        .value("CheatedEvent", CheatedEvent)
        .value("StackerFullEvent", StackerFullEvent)
        .value("CalibrateStartEvent", CalibrateStartEvent)
        .value("CalibrateProgressEvent", CalibrateProgressEvent)
        .value("CalibrateFinishEvent", CalibrateFinishEvent)
        .value("DownloadStartEvent", DownloadStartEvent)
        .value("DownloadRestartEvent", DownloadRestartEvent)
        .value("DownloadProgressEvent", DownloadProgressEvent)
        .value("DownloadFinishEvent", DownloadFinishEvent)
        .value("PauseDetectedEvent", PauseDetectedEvent)
        .value("PauseClearedEvent", PauseClearedEvent)
        .value("StallDetectedEvent", StallDetectedEvent)
        .value("StallClearedEvent", StallClearedEvent)
        .value("JamDetectedEvent", JamDetectedEvent)
        .value("JamClearedEvent", JamClearedEvent)
        .value("PowerUpEvent", PowerUpEvent)
        .value("InvalidCommandEvent", InvalidCommandEvent)
        .value("CashBoxAttachedEvent", CashBoxAttachedEvent)
        .value("CashBoxRemovedEvent", CashBoxRemovedEvent)
        .value("DisconnectedEvent", DisconnectedEvent)
        .value("Events_End", Events_End)
        ;

    class_<CAcceptor,boost::noncopyable>("CAcceptor")
        .def("open", &CAcceptor::Open)
        .def("close", &CAcceptor::Close)
        .def("calibrate", &CAcceptor::Calibrate)
        .def("softreset", &CAcceptor::SoftReset)
        .def("clearcashboxtotal", &CAcceptor::ClearCashBoxTotal)
        .def("escrowreturn", &CAcceptor::EscrowReturn)
        .def("escrowstack", &CAcceptor::EscrowStack)
        .def("getbill", &CAcceptor::GetBill)
        .add_property("autostack",
                      &CAcceptor::GetAutoStack, &CAcceptor::SetAutoStack)
        .add_property("acceptbills",
                      &CAcceptor::GetEnableAcceptance, &CAcceptor::SetEnableAcceptance)
        .add_property("highsecurity",
                      &CAcceptor::GetHighSecurity, &CAcceptor::SetHighSecurity)
        .add_property("debuglog",
                      &CAcceptor::GetDebugLog, &CAcceptor::SetDebugLog)
        .add_property("debuglogpath",
                      &CAcceptor::GetDebugLogPath, &CAcceptor::SetDebugLogPath)
        .add_property("billtypeenables",
                      &CAcceptor::GetBillTypeEnables, &CAcceptor::SetBillTypeEnables)
        .add_property("billvalueenables",
                      &CAcceptor::GetBillValueEnables, &CAcceptor::SetBillValueEnables)
/*
        .add_property("",
                      &CAcceptor::Get, &CAcceptor::Set)
*/
        ;
}
