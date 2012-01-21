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
//----------------------------------------------------- Personnal Includes
#include "EnOceanProtocol.h"
#include "Receptor.h"
#include "Sensors.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef string (*EnOceanCallbackFunction)(enocean_data_structure* frame);

//------------------------------------------------------------------------
// Description :
//		Receipts and stocks the frames sent by the EnOcean server.
//
//------------------------------------------------------------------------

class PeriphTable
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants
	static const int FRAME_SIZE = 8;
	static const int QUEUE_SIZE = 0;
//--------------------------------------------------------- Public Methods
	int add(SensorId id, EnOceanCallbackFunction funct);
	EnOceanCallbackFunction find(SensorId id);

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	PeriphTable();
	virtual ~PeriphTable();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes
	map<SensorId, EnOceanCallbackFunction> periph;
	pthread_mutex_t mutex;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* PERIPHTABLE_H_ */

