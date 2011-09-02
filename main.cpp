
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "../MPOST_Linux/Acceptor.h"

#include "mpost_int.h"

using namespace std;
using namespace MPOST;


eventcallback eventcallbacks[28];

CAcceptor* g_acceptor = new CAcceptor;


void ConnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Connected" << endl;
    if (eventcallbacks[ConnectedEvent])
        eventcallbacks[ConnectedEvent](value, "");
}

void DisconnectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Disconnected" << endl;
    if (eventcallbacks[DisconnectedEvent])
        eventcallbacks[DisconnectedEvent](value, "");
}

void EscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Escrow: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    if (eventcallbacks[EscrowEvent])
        eventcallbacks[EscrowEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void PUPEscrowEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: PUPEscrow: " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    if (eventcallbacks[PUPEscrowEvent])
        eventcallbacks[PUPEscrowEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void StackedEventHandler(CAcceptor* g_acceptor, int value)
{
	stringstream ss;
	
	ss << "EVENT: Stacked: Doc Type: " <<  CAcceptor::DocumentTypeToString(g_acceptor->GetDocType()) << " " << g_acceptor->GetBill().ToString() << endl;
	
	cout << ss.str().c_str();
    if (eventcallbacks[StackedEvent])
        eventcallbacks[StackedEvent](value, g_acceptor->GetBill().ToString().c_str());
}

void ReturnedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Returned." << endl;
    if (eventcallbacks[ReturnedEvent])
        eventcallbacks[ReturnedEvent](value, "");
}

void RejectedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Rejected." << endl;
    if (eventcallbacks[RejectedEvent])
        eventcallbacks[RejectedEvent](value, "");
}

void CheatedEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Cheated." << endl;
    if (eventcallbacks[CheatedEvent])
        eventcallbacks[CheatedEvent](value, "");
}

void StackerFullEventHandler(CAcceptor* g_acceptor, int value)
{
	cout << "EVENT: Stacker Full." << endl;
    if (eventcallbacks[StackerFullEvent])
        eventcallbacks[StackerFullEvent](value, "");
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
        
    void mpost_open(char *portname) {
        g_acceptor->Open(portname, A);
    }

    void mpost_close() {
        g_acceptor->Close();
    }    

/* return the bill that is currently sitting in escrow */
    void mpost_return() {
        g_acceptor->EscrowReturn();
    }

/* stack the bill that is currently sitting in escrow */
    void mpost_stack() {
        g_acceptor->EscrowStack();
    }

    void mpost_acceptbills(int enable) {
        g_acceptor->SetEnableAcceptance(enable);
    }

    void mpost_autostack(int enable) {
        g_acceptor->SetAutoStack(enable);
    }

    void mpost_highsecurity(int enable) {
        g_acceptor->SetHighSecurity(enable);
    }

    void mpost_softreset() {
        g_acceptor->SoftReset();
    }

    void mpost_debug(int enable) {
        g_acceptor->SetDebugLog(enable);
    }

    void mpost_setcallback(Event event, eventcallback callback) {
        eventcallbacks[event] = callback;
    }

    /* setup C++ callbacks */
	void mpost_setup()
	{

        for (int i = Events_Begin; i < Events_End; i++)
            eventcallbacks[i] = 0;
        g_acceptor->SetEventHandler(ConnectedEvent, ConnectedEventHandler);
        g_acceptor->SetEventHandler(DisconnectedEvent, DisconnectedEventHandler);
        g_acceptor->SetEventHandler(EscrowEvent, EscrowEventHandler);
        g_acceptor->SetEventHandler(PUPEscrowEvent, PUPEscrowEventHandler);
        g_acceptor->SetEventHandler(StackedEvent, StackedEventHandler);
        g_acceptor->SetEventHandler(ReturnedEvent, ReturnedEventHandler);
        g_acceptor->SetEventHandler(RejectedEvent, RejectedEventHandler);
        g_acceptor->SetEventHandler(CheatedEvent, CheatedEventHandler);
        g_acceptor->SetEventHandler(StackerFullEvent, StackerFullEventHandler);
        g_acceptor->SetEventHandler(CalibrateStartEvent, CalibrateStartEventHandler);
        g_acceptor->SetEventHandler(CalibrateProgressEvent, CalibrateProgressEventHandler);
        g_acceptor->SetEventHandler(CalibrateFinishEvent, CalibrateFinishEventHandler);
        g_acceptor->SetEventHandler(DownloadStartEvent, DownloadStartEventHandler);
        g_acceptor->SetEventHandler(DownloadRestartEvent, DownloadRestartEventHandler);
        g_acceptor->SetEventHandler(DownloadProgressEvent, DownloadProgressEventHandler);
        g_acceptor->SetEventHandler(DownloadFinishEvent, DownloadFinishEventHandler);
    }

}

/*
  int main(int argc, char *argv[])
  {
  g_acceptor->SetEventHandler(ConnectedEvent, ConnectedEventHandler);
  g_acceptor->SetEventHandler(DisconnectedEvent, DisconnectedEventHandler);
  g_acceptor->SetEventHandler(EscrowEvent, EscrowEventHandler);
  g_acceptor->SetEventHandler(PUPEscrowEvent, PUPEscrowEventHandler);
  g_acceptor->SetEventHandler(StackedEvent, StackedEventHandler);
  g_acceptor->SetEventHandler(ReturnedEvent, ReturnedEventHandler);
  g_acceptor->SetEventHandler(RejectedEvent, RejectedEventHandler);
  g_acceptor->SetEventHandler(CheatedEvent, CheatedEventHandler);
  g_acceptor->SetEventHandler(StackerFullEvent, StackerFullEventHandler);
  g_acceptor->SetEventHandler(CalibrateStartEvent, CalibrateStartEventHandler);
  g_acceptor->SetEventHandler(CalibrateProgressEvent, CalibrateProgressEventHandler);
  g_acceptor->SetEventHandler(CalibrateFinishEvent, CalibrateFinishEventHandler);
  g_acceptor->SetEventHandler(DownloadStartEvent, DownloadStartEventHandler);
  g_acceptor->SetEventHandler(DownloadRestartEvent, DownloadRestartEventHandler);
  g_acceptor->SetEventHandler(DownloadProgressEvent, DownloadProgressEventHandler);
  g_acceptor->SetEventHandler(DownloadFinishEvent, DownloadFinishEventHandler);

  string s;
    
  while(true)
  {
  cin >> s;
        
  if (s == "o")
  g_acceptor->Open("/dev/ttyUSB0", A);
        
  if (s == "c")
  g_acceptor->Close();
        
  // Exit
  if (s == "x")
  break;
        
  if (s == "r")
  g_acceptor->EscrowReturn();
        
  if (s == "s")
  g_acceptor->EscrowStack();    
        
  if (s == "res")
  g_acceptor->SoftReset();    
        
  // Hard-code the appropriate filename here (or add code to read a filename).
  if (s == "f")
  g_acceptor->FlashDownload("/root/workspace/MPOST/284us281.bds");//490021211_SC83_JPY_FLASH.BIN");
        
  // Device Information
  if (s == "i")
  {
  cout << "     Device Type: " <<(g_acceptor->GetCapDeviceType() ? g_acceptor->GetDeviceType() : "Not supported") << endl;
  cout << "       Device CRC: " << g_acceptor->GetDeviceCRC() << endl;
  cout << "        Serial #: " <<(g_acceptor->GetCapDeviceSerialNumber() ? g_acceptor->GetDeviceSerialNumber() : "Not supported") << endl;
  cout << "     Boot Part #: " <<(g_acceptor->GetCapBootPN() ? g_acceptor->GetBootPN() : "Not supported") << endl;
  cout << "  Application PN: " <<(g_acceptor->GetCapApplicationPN() ? g_acceptor->GetApplicationPN() : "Not supported") << endl;
  if (g_acceptor->GetCapVariantPN())
  {
  cout << "       Variant PN: " << g_acceptor->GetVariantPN() << endl;
  cout << "    Variant Name: " << endl;
	        	
  vector<string> names = g_acceptor->GetVariantNames();
	        	
  for(vector<string>::iterator i = names.begin(); i != names.end(); i++)
  cout << *i << " ";
	        	
  cout << endl;
  }
  else
  {
  cout << "       Variant PN: Not supported";
  cout << "    Variant Name: Not supported" << endl;
  }
        	
  cout << "        Cassette: " <<(g_acceptor->GetCashBoxAttached() ? "Installed" : "Not installed") << endl;
  cout << "Cash in Cassette: ";
  if (g_acceptor->GetCapCashBoxTotal())
  cout << g_acceptor->GetCashBoxTotal() << endl;
  else
  cout << "Not supported" << endl;
        	
  cout << "           Resets: " << g_acceptor->GetDeviceResets() << endl;
  cout << "        Bill Path: " <<(g_acceptor->GetDeviceJammed() ? "Jammed" : "Clear") << endl;
  cout << "            Model: " << g_acceptor->GetDeviceModel();
        	
  if (g_acceptor->GetDeviceModel() >= 32)
  cout << "(" <<(char)g_acceptor->GetDeviceModel() << ")" << endl;
  else
  cout << endl;
        
  cout << "        BNFStatus: ";
  if (g_acceptor->GetCapBNFStatus())
  cout << g_acceptor->GetBNFStatus() << endl;
  else
  cout << "Not supported" << endl;
        	
  if (g_acceptor->GetCapAudit())
  {
  vector<int> values = g_acceptor->GetAuditLifeTimeTotals();
  cout << "             Data Map: " << values[0] << endl;
  cout << "       Total Op Hours: " << values[1] << endl;
  cout << "    Total Mot Starts: " << values[2] << endl;
  cout << "        Total Escrow: " << values[3] << endl;
  cout << "    Total Recognized: " << values[4] << endl;
  cout << "     Total Validated: " << values[5] << endl;

  values = g_acceptor->GetAuditQP();
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

  values = g_acceptor->GetAuditPerformance();
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
