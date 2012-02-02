
/*************************************************************************
                           SensorSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulator> (SensorSimulator.h file) --------

#ifndef SENSORSIMULATOR_H_
#define SENSORSIMULATOR_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <pthread.h>
//------------------------------------------------------ Personnal Include
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Room.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Analyses the frame provided by the server, and extracts the informations from them, for the chosen sensors.
//
//------------------------------------------------------------------------

class SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	EnOceanSensorAPI::SensorId getId();

	void getFrame(char* frame);

	virtual void update();

	Room* getRoom();


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulator(int id, Room* room);
	virtual ~SensorSimulator();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	EnOceanSensorAPI::SensorId id;					// ID
	pthread_mutex_t mutex; 			// Mutex to protect this value
	enocean_data_structure frame; 	// Frame to ben sent
	Room *room;						// Room where is the sensor

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* SENSORSIMULATOR_H_ */