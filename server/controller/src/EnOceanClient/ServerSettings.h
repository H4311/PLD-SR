/*************************************************************************
                           ServerSettings  -  description
                             -------------------
    Creation             : 05 Febr. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <ServerSettings> (ServerSettings.h file) --------

#ifndef SERVERSETTINGS_H_
#define SERVERSETTINGS_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <pthread.h>
#include <vector>
//------------------------------------------------------ Personnal Include
#include "../Config.h"
#include "../Devices/EnOceanSensorAPI.h"
#include "../Devices/DeviceTable.h"
#include "../Simulator/EnOCeanBaseSimulator.h"
#include "TCPServer.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Server receiving order from the Web server, to add/delete/edit the sensors actuators.
//
//------------------------------------------------------------------------

class ServerSettings
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	float updateSensors();

	int openSocket(int port);
		// Manual :
	    //		Open the socket.

	int acceptClient();
	// Manual :
	//		Accept a client connection.
	// Contract :
	//		open()

	int closeClient();
	int closeSocket();

	int readClient(char* msg, int length);

	int getFlag();

	void run();
	void stop();


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	ServerSettings(DeviceTable* sensors, blocking_queue<string>* msgToSend
#ifdef SIMULATION
			, blocking_queue<string>* msgToSendSimu
			,EnOCeanBaseSimulator* simu
#endif
	);
	virtual ~ServerSettings();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes
	DeviceTable* sensors;
	blocking_queue<string>* msgToSend;
#ifdef SIMULATION
	blocking_queue<string>* msgToSendSimu;
	EnOCeanBaseSimulator* simu;
#endif
	pthread_mutex_t mutex;
	TCPServer server;
	pthread_t thread_Receive;
	int flag;
private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes
	friend void* ServerSettingsThread_Receive(void* param);
//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class
void* ServerSettingsThread_Receive(void* param);

#endif /* SERVERSETTINGS_H_ */
