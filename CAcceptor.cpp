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
        .def("escrowreturn", &CAcceptor::EscrowReturn)
        .def("escrowstack", &CAcceptor::EscrowStack)
        ;
}
