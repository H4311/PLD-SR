
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
#include "../Devices/EnOceanSensorAPI.h"
#include "Sensors/SensorSimulator.h"
#include "ServerSimulator.h"
#include "Actuators/EnOceanActuator.h"
#include "Model/Subject.h"
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
	static const int DELAY = 30;
//--------------------------------------------------------- Public Methods

	void addSensor(SensorSimulator* sensor);
	bool delSensor(EnOceanSensorAPI::SensorId id);
	int countSensors();

	void addActuator(Actuator* sensor);
	bool delActuator(int id);
	int countActuators();

	void addSubject(Subject* sensor);
	bool delSubject(int id);
	int countSubjects();
	Subject* findSubject(int id);

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
	
	int writeClient(char* msg, int length);
	int readClient(char* msg, int length);
	
	void getFrame(int posSensor, char* frame);
	
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
	vector<Actuator*> actuators;
	vector<Subject*> subjects;
	pthread_mutex_t mutex;
	ServerSimulator server;
	pthread_t thread_Send;
	pthread_t thread_Receive;
	int flag;
private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes
	friend void* EnOceanBaseSimulatorThread_Send(void* param);
	friend void* EnOceanBaseSimulatorThread_Receive(void* param);
//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class
void* EnOceanBaseSimulatorThread_Send(void* param);
void* EnOceanBaseSimulatorThread_Receive(void* param);

#endif /* ENOCEANBASESIMULATOR_H_ */
