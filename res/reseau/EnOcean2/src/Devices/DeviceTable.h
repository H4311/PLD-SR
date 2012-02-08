/*************************************************************************
                           PeriphTable  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <PeriphTable> (PeriphTable.h file) --------

#ifndef PERIPHTABLE_H_
#define PERIPHTABLE_H_

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System Includes
using namespace std;
#include <map>
#include <string>
#include <pthread.h>
//----------------------------------------------------- Personnal Includes
#include "EnOceanProtocol.h"
#include "../EnOceanClient/Receptor.h"
#include "EnOceanSensorAPI.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Map containing the "drivers", ie the id of the knownn devices, and the functions to process the data they send.
//
//------------------------------------------------------------------------

class DeviceTable
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants
	static const int FRAME_SIZE = 8;
	static const int QUEUE_SIZE = 0;
//--------------------------------------------------------- Public Methods
	int add(EnOceanSensorAPI::SensorId id, EnOceanSensorAPI::EnOceanCallbackFunction funct);
	// Manual :
    //		Add a driver to the list.
    // Contract :
    //		/

	bool del(EnOceanSensorAPI::SensorId id);
	// Manual :
	//		Delete a driver from the list. Return true if deleted.
	// Contract :
	//		/


	EnOceanSensorAPI::EnOceanCallbackFunction find(EnOceanSensorAPI::SensorId id);
	// Manual :
    //		Returns the Process-function corresponding to the device's id (or NULL if not found).
    // Contract :
    //		/

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	DeviceTable();
	virtual ~DeviceTable();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes
	map<EnOceanSensorAPI::SensorId, EnOceanSensorAPI::EnOceanCallbackFunction> drivers;
	pthread_mutex_t mutex;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* PERIPHTABLE_H_ */

