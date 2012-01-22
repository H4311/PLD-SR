
/*************************************************************************
                           EnOCeanBaseSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOCeanBaseSimulator> (EnOCeanBaseSimulator.h file) --------

#ifndef ENOCEANBASESIMULATOR_H_
#define ENOCEANBASESIMULATOR_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <pthread.h>
#include <vector>
//------------------------------------------------------ Personnal Include
#include "../EnOceanProtocol.h"
#include "SensorSimulator.h"
#include "ServerSimulator.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Analyses the frame provided by the server, and extracts the informations from them, for the chosen sensors.
//
//------------------------------------------------------------------------

class EnOCeanBaseSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants
	const int DELAY = 100;
//--------------------------------------------------------- Public Methods

	int addSensor(SensorSimulator* sensor);
	void delSensor(SensorId id);
	int countSensors();

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
	
	int writeClient(char* msg, int length);
	
	getFrame(int posSensor, char* frame);
	
	int getFlag();
	
	void run();
	void stop();


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOCeanBaseSimulator();
	virtual ~EnOCeanBaseSimulator();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes
	vector<SensorSimulator*> sensors;
	pthread_mutex_t mutex;
	ServerSimulator server;
	pthread_t thread;
	int flag;
private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class
	void* EnOceanBaseSimulatorThread (void* param);

#endif /* ENOCEANBASESIMULATOR_H_ */
