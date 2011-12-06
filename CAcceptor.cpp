#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Acceptor.h"

using namespace boost::python;
using namespace MPOST;


struct CBill_to_python_tuple
{
    static PyObject* convert(CBill s)
        {
            boost::python::list* l = new boost::python::list();
            (*l).append(s.GetCountry());
            (*l).append((int)s.GetValue());
            (*l).append(s.GetSeries());
            (*l).append(s.GetType());
            (*l).append(s.GetCompatibility());
            (*l).append(s.GetVersion());
            return l->ptr();
        }
};

template<class T>
struct VecToList
{
    static PyObject* convert(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};

BOOST_PYTHON_MODULE(mpost)
{
    enum_<BNFStatus>("bnfstatus")
        .value("unknown", Unknown)
        .value("ok", OK)
        .value("notattached", NotAttached)
        .value("error", Error)
        ;

    enum_<PowerUp>("powerup")
        .value("A", A)
        .value("B", B)
        .value("C", C)
        .value("E", E)
        ;

    enum_<PupExt>("pupext")
        .value("return", Return)
        .value("outofservice", OutOfService)
        .value("stacknocredit", StackNoCredit)
        .value("stack", Stack)
        .value("waitnocredit", WaitNoCredit)
        .value("wait", Wait)
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

    enum_<Bezel>("bezel")
        .value("standard", Standard)
        .value("platform", Platform)
        .value("diagnostic", Diagnostic)
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

    class_<CBill,boost::noncopyable>("CBill", "Represents a bill type")
        .def("__repr__", &CBill::ToString)
        .add_property("country", &CBill::GetCountry)
        .add_property("value", &CBill::GetValue)
        .add_property("type", &CBill::GetType)
        .add_property("series", &CBill::GetSeries)
        .add_property("compatibility", &CBill::GetCompatibility)
        .add_property("version", &CBill::GetVersion)
        ;

    boost::python::to_python_converter<CBill, CBill_to_python_tuple>();
    to_python_converter<std::vector<CBill, std::allocator<CBill> >, 
                        VecToList<CBill> >();

    class_<CAcceptor,boost::noncopyable>("CAcceptor")
        .def("open", &CAcceptor::Open)
        .def("close", &CAcceptor::Close)
        .def("calibrate", &CAcceptor::Calibrate)
        .def("escrowreturn", &CAcceptor::EscrowReturn)
        .def("escrowstack", &CAcceptor::EscrowStack)
        .def("flashdownload", &CAcceptor::FlashDownload)
        .def("softreset", &CAcceptor::SoftReset)
        .def("clearcashboxtotal", &CAcceptor::ClearCashBoxTotal)
        .add_property("bill", &CAcceptor::GetBill)
        .add_property("billtypes", &CAcceptor::GetBillTypes)
        .add_property("billvalues", &CAcceptor::GetBillValues)
        .add_property("bnfstatus", &CAcceptor::GetBNFStatus)
        .add_property("cashboxattached", &CAcceptor::GetCashBoxAttached)
        .add_property("cashboxfull", &CAcceptor::GetCashBoxFull)
        .add_property("cashboxtotal", &CAcceptor::GetCashBoxTotal)
        .add_property("connected", &CAcceptor::GetConnected)
        .add_property("devicebusy", &CAcceptor::GetDeviceBusy)
        .add_property("devicecrc", &CAcceptor::GetDeviceCRC)
        .add_property("devicefailure", &CAcceptor::GetDeviceFailure)
        .add_property("devicejammed", &CAcceptor::GetDeviceJammed)
        .add_property("devicemodel", &CAcceptor::GetDeviceModel)
        .add_property("devicepaused", &CAcceptor::GetDevicePaused)
        .add_property("deviceportname", &CAcceptor::GetDevicePortName)
        .add_property("devicepowerup", &CAcceptor::GetDevicePowerUp)
        .add_property("deviceresets", &CAcceptor::GetDeviceResets)
        .add_property("devicerevision", &CAcceptor::GetDeviceRevision)
        .add_property("deviceserialnumber", &CAcceptor::GetDeviceSerialNumber)
        .add_property("devicestalled", &CAcceptor::GetDeviceStalled)
        .add_property("devicestate", &CAcceptor::GetDeviceState)
        .add_property("devicetype", &CAcceptor::GetDeviceType)
/*
        .add_property("", &CAcceptor::Get)
        .add_property("", &CAcceptor::Get)
        .add_property("", &CAcceptor::Get)
        .add_property("", &CAcceptor::Get)
*/
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
