
/*************************************************************************
                           Actuator  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <Actuator> (Actuator.h file) --------

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <vector>
#include <pthread.h>
//------------------------------------------------------ Personnal Include
#include "../Sensors/SensorSimulator.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element which can edit the value of some sensors.
//
//------------------------------------------------------------------------

class Actuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	int getID();

	void addSensor(SensorSimulator* sensor);
	void delSensor(EnOceanSensorAPI::SensorId id);
	int countSensors();

	virtual float update() = 0;
	virtual void set(enocean_data_structure *frame) = 0;


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	Actuator(int id);
	virtual ~Actuator();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	vector<SensorSimulator*> sensors;
	int id;
	pthread_mutex_t mutex; 			// Mutex to protect this value

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ACTUATOR_H_ */
