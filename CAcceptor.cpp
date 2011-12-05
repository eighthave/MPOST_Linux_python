#include <boost/python.hpp>
#include "Acceptor.h"

using namespace boost::python;
using namespace MPOST;


BOOST_PYTHON_MODULE(mpost)
{
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
