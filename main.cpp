
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "../MPOST_Linux/Acceptor.h"

#include "mpost_int.h"

using namespace std;
using namespace MPOST;


/* -------------------------------------------------------------------------- */

#define MAX_INSTANCES 16

class WrappedAcceptor
{
public:
    eventcallback eventcallbacks[28];
    CAcceptor* cAcceptor;

	WrappedAcceptor()
	{
        cAcceptor = new CAcceptor;
	}

private:
};

WrappedAcceptor* acceptors[MAX_INSTANCES];

WrappedAcceptor* findWA(CAcceptor* g_acceptor)
{
    for (int i = 0; i < MAX_INSTANCES; i++)
        if(acceptors[i]->cAcceptor == g_acceptor)
            return acceptors[i];
    return NULL;
}

/* -------------------------------------------------------------------------- */

void ConnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Connected" << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[ConnectedEvent])
        wa->eventcallbacks[ConnectedEvent](value, "");
}

void DisconnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Disconnected" << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[DisconnectedEvent])
        wa->eventcallbacks[DisconnectedEvent](value, "");
}

void EscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Escrow: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[EscrowEvent])
        wa->eventcallbacks[EscrowEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void PUPEscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: PUPEscrow: " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[PUPEscrowEvent])
        wa->eventcallbacks[PUPEscrowEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void StackedEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Stacked: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[StackedEvent])
        wa->eventcallbacks[StackedEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void ReturnedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Returned." << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[ReturnedEvent])
        wa->eventcallbacks[ReturnedEvent](value, "");
}

void RejectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Rejected." << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[RejectedEvent])
        wa->eventcallbacks[RejectedEvent](value, "");
}

void CheatedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Cheated." << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[CheatedEvent])
        wa->eventcallbacks[CheatedEvent](value, "");
}

void StackerFullEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Stacker Full." << endl;
    WrappedAcceptor* wa = findWA(g_acceptor);
    if (wa && wa->eventcallbacks[StackerFullEvent])
        wa->eventcallbacks[StackerFullEvent](value, "");
}

void CalibrateStartEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Start." << endl;
}

void CalibrateProgressEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Progress." << endl;
}

void CalibrateFinishEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Calibrate Finish." << endl;
}

int g_TotalSectors = 0;
int g_SectorsDownloaded = 0;

void DownloadStartEventHandler(CAcceptor* g_acceptor, int value)
{
	g_TotalSectors = value;
    cout << "EVENT: Download Start." << endl;
}

void DownloadRestartEventHandler(CAcceptor* g_acceptor, int value)
{
    cout << "EVENT: Download Restart." << endl;
}

void DownloadProgressEventHandler(CAcceptor* g_acceptor, int value)
{
	g_SectorsDownloaded = value;
	
	cout << "EVENT: Download Progress." << endl;
}

void DownloadFinishEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Download Finish." << endl;
}

/* C API ---------------------------------------------------------------- */


extern "C" {
        
    void mpost_open(int instance, char *portname) {
        acceptors[instance]->cAcceptor->Open(portname, A);
    }

    void mpost_close(int instance) {
        acceptors[instance]->cAcceptor->Close();
    }    

/* return the bill that is currently sitting in escrow */
    void mpost_return(int instance) {
        acceptors[instance]->cAcceptor->EscrowReturn();
    }

/* stack the bill that is currently sitting in escrow */
    void mpost_stack(int instance) {
        acceptors[instance]->cAcceptor->EscrowStack();
    }

    void mpost_acceptbills(int instance, int enable) {
        acceptors[instance]->cAcceptor->SetEnableAcceptance(enable);
    }

    void mpost_autostack(int instance, int enable) {
        acceptors[instance]->cAcceptor->SetAutoStack(enable);
    }

    void mpost_highsecurity(int instance, int enable) {
        acceptors[instance]->cAcceptor->SetHighSecurity(enable);
    }

    void mpost_softreset(int instance) {
        acceptors[instance]->cAcceptor->SoftReset();
    }

    void mpost_debug(int instance, int enable) {
        acceptors[instance]->cAcceptor->SetDebugLog(enable);
    }
    
    void mpost_setcallback(int instance, Event event, eventcallback callback) {
        acceptors[instance]->eventcallbacks[event] = callback;
    }
    
    /* setup C++ callbacks */
	void mpost_setup(int instance)
	{
        cout << "mpost_setup" << endl;
        WrappedAcceptor* wa = new WrappedAcceptor;
        CAcceptor* ca = wa->cAcceptor;
        for (int i = Events_Begin; i < Events_End; i++)
            wa->eventcallbacks[i] = 0;
        ca->SetEventHandler(ConnectedEvent, ConnectedEventHandler);
        ca->SetEventHandler(DisconnectedEvent, DisconnectedEventHandler);
        ca->SetEventHandler(EscrowEvent, EscrowEventHandler);
        ca->SetEventHandler(PUPEscrowEvent, PUPEscrowEventHandler);
        ca->SetEventHandler(StackedEvent, StackedEventHandler);
        ca->SetEventHandler(ReturnedEvent, ReturnedEventHandler);
        ca->SetEventHandler(RejectedEvent, RejectedEventHandler);
        ca->SetEventHandler(CheatedEvent, CheatedEventHandler);
        ca->SetEventHandler(StackerFullEvent, StackerFullEventHandler);
        ca->SetEventHandler(CalibrateStartEvent, CalibrateStartEventHandler);
        ca->SetEventHandler(CalibrateProgressEvent, CalibrateProgressEventHandler);
        ca->SetEventHandler(CalibrateFinishEvent, CalibrateFinishEventHandler);
        ca->SetEventHandler(DownloadStartEvent, DownloadStartEventHandler);
        ca->SetEventHandler(DownloadRestartEvent, DownloadRestartEventHandler);
        ca->SetEventHandler(DownloadProgressEvent, DownloadProgressEventHandler);
        ca->SetEventHandler(DownloadFinishEvent, DownloadFinishEventHandler);
        acceptors[instance] = wa;
        cout << "mpost_setup END" << endl;
    }

}

/*
  int main(int argc, char *argv[])
  {
  WrappedAcceptor* wa = acceptors[instance];
  CAcceptor* ca = wa->cAcceptor;
  ca->SetEventHandler(ConnectedEvent, ConnectedEventHandler);
  ca->SetEventHandler(DisconnectedEvent, DisconnectedEventHandler);
  ca->SetEventHandler(EscrowEvent, EscrowEventHandler);
  ca->SetEventHandler(PUPEscrowEvent, PUPEscrowEventHandler);
  ca->SetEventHandler(StackedEvent, StackedEventHandler);
  ca->SetEventHandler(ReturnedEvent, ReturnedEventHandler);
  ca->SetEventHandler(RejectedEvent, RejectedEventHandler);
  ca->SetEventHandler(CheatedEvent, CheatedEventHandler);
  ca->SetEventHandler(StackerFullEvent, StackerFullEventHandler);
  ca->SetEventHandler(CalibrateStartEvent, CalibrateStartEventHandler);
  ca->SetEventHandler(CalibrateProgressEvent, CalibrateProgressEventHandler);
  ca->SetEventHandler(CalibrateFinishEvent, CalibrateFinishEventHandler);
  ca->SetEventHandler(DownloadStartEvent, DownloadStartEventHandler);
  ca->SetEventHandler(DownloadRestartEvent, DownloadRestartEventHandler);
  ca->SetEventHandler(DownloadProgressEvent, DownloadProgressEventHandler);
  ca->SetEventHandler(DownloadFinishEvent, DownloadFinishEventHandler);

  string s;
    
  while(true)
  {
  cin >> s;
        
  if (s == "o")
  acceptors[instance]->cAcceptor->Open("/dev/ttyUSB0", A);
        
  if (s == "c")
  acceptors[instance]->cAcceptor->Close();
        
  // Exit
  if (s == "x")
  break;
        
  if (s == "r")
  acceptors[instance]->cAcceptor->EscrowReturn();
        
  if (s == "s")
  acceptors[instance]->cAcceptor->EscrowStack();    
        
  if (s == "res")
  acceptors[instance]->cAcceptor->SoftReset();    
        
  // Hard-code the appropriate filename here (or add code to read a filename).
  if (s == "f")
  acceptors[instance]->cAcceptor->FlashDownload("/root/workspace/MPOST/284us281.bds");//490021211_SC83_JPY_FLASH.BIN");
        
  // Device Information
  if (s == "i")
  {
  cout << "     Device Type: " <<(acceptors[instance]->cAcceptor->GetCapDeviceType() ? acceptors[instance]->cAcceptor->GetDeviceType() : "Not supported") << endl;
  cout << "       Device CRC: " << acceptors[instance]->cAcceptor->GetDeviceCRC() << endl;
  cout << "        Serial #: " <<(acceptors[instance]->cAcceptor->GetCapDeviceSerialNumber() ? acceptors[instance]->cAcceptor->GetDeviceSerialNumber() : "Not supported") << endl;
  cout << "     Boot Part #: " <<(acceptors[instance]->cAcceptor->GetCapBootPN() ? acceptors[instance]->cAcceptor->GetBootPN() : "Not supported") << endl;
  cout << "  Application PN: " <<(acceptors[instance]->cAcceptor->GetCapApplicationPN() ? acceptors[instance]->cAcceptor->GetApplicationPN() : "Not supported") << endl;
  if (acceptors[instance]->cAcceptor->GetCapVariantPN())
  {
  cout << "       Variant PN: " << acceptors[instance]->cAcceptor->GetVariantPN() << endl;
  cout << "    Variant Name: " << endl;
	        	
  vector<string> names = acceptors[instance]->cAcceptor->GetVariantNames();
	        	
  for(vector<string>::iterator i = names.begin(); i != names.end(); i++)
  cout << *i << " ";
	        	
  cout << endl;
  }
  else
  {
  cout << "       Variant PN: Not supported";
  cout << "    Variant Name: Not supported" << endl;
  }
        	
  cout << "        Cassette: " <<(acceptors[instance]->cAcceptor->GetCashBoxAttached() ? "Installed" : "Not installed") << endl;
  cout << "Cash in Cassette: ";
  if (acceptors[instance]->cAcceptor->GetCapCashBoxTotal())
  cout << acceptors[instance]->cAcceptor->GetCashBoxTotal() << endl;
  else
  cout << "Not supported" << endl;
        	
  cout << "           Resets: " << acceptors[instance]->cAcceptor->GetDeviceResets() << endl;
  cout << "        Bill Path: " <<(acceptors[instance]->cAcceptor->GetDeviceJammed() ? "Jammed" : "Clear") << endl;
  cout << "            Model: " << acceptors[instance]->cAcceptor->GetDeviceModel();
        	
  if (acceptors[instance]->cAcceptor->GetDeviceModel() >= 32)
  cout << "(" <<(char)acceptors[instance]->cAcceptor->GetDeviceModel() << ")" << endl;
  else
  cout << endl;
        
  cout << "        BNFStatus: ";
  if (acceptors[instance]->cAcceptor->GetCapBNFStatus())
  cout << acceptors[instance]->cAcceptor->GetBNFStatus() << endl;
  else
  cout << "Not supported" << endl;
        	
  if (acceptors[instance]->cAcceptor->GetCapAudit())
  {
  vector<int> values = acceptors[instance]->cAcceptor->GetAuditLifeTimeTotals();
  cout << "             Data Map: " << values[0] << endl;
  cout << "       Total Op Hours: " << values[1] << endl;
  cout << "    Total Mot Starts: " << values[2] << endl;
  cout << "        Total Escrow: " << values[3] << endl;
  cout << "    Total Recognized: " << values[4] << endl;
  cout << "     Total Validated: " << values[5] << endl;

  values = acceptors[instance]->cAcceptor->GetAuditQP();
  cout << "             Last 100: " << values[0] << endl;
  cout << "        Motor Starts: " << values[1] << endl;
  cout << "        Docs Stacked: " << values[2] << endl;
  cout << "          Docs Escrow: " << values[3] << endl;
  cout << "    Docs Recognition: " << values[4] << endl;
  cout << "       Docs Validated: " << values[5] << endl;
  cout << "     Docs Rec Reject: " << values[6] << endl;
  cout << "     Docs Sec Reject: " << values[7] << endl;
  cout << "  Docs Orient Reject: " << values[8] << endl;
  cout << "Docs Disabled Reject: " << values[9] << endl;
  cout << "       Docs FF Reject: " << values[10] << endl;
  cout << " Docs While Disabled: " << values[11] << endl;
  cout << "    Docs Host Reject: " << values[12] << endl;
  cout << "        Docs Barcode: " << values[13] << endl;

  values = acceptors[instance]->cAcceptor->GetAuditPerformance();
  cout << "           CC0 Reject: " << values[0] << endl;
  cout << "           CC1 Reject: " << values[1] << endl;
  cout << "            All James: " << values[2] << endl;
  cout << "        Jam Recovery: " << values[3] << endl;
  cout << "           Jam Reject: " << values[4] << endl;
  cout << "          Jam Stacker: " << values[5] << endl;
  cout << "     Jam No Recovery: " << values[6] << endl;
  cout << "       Out of Service: " << values[7] << endl;
  cout << "        Out of Order: " << values[8] << endl;
  cout << "     Operating Hours: " << values[9] << endl;
  cout << "        Doc Too Long: " << values[10] << endl;
  cout << "            Doc Tease: " << values[11] << endl;
  cout << "        Calibrations: " << values[12] << endl;
  cout << "               Resets: " << values[13] << endl;
  cout << "            Downloads: " << values[14] << endl;
  cout << "        Cassette Full: " << values[15] << endl;
  cout << "    Cassette Removed: " << values[16] << endl;
  }
  else
  {
  cout << "          Performance: Not supported" << endl;
  }
  }
  }
  return 1;
  }

*/
