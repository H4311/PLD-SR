/*************************************************************************
                           PeriphTable  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <PeriphTable> (PeriphTable.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <pthread.h>


//------------------------------------------------------ Personnal Include
#include "PeriphTable.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int PeriphTable::add(SensorId id, EnOceanCallbackFunction cf) {
	int n;
	pthread_mutex_lock(&mutex);
	n = (periph.insert(pair<SensorId,EnOceanCallbackFunction>(id, cf))).second;
	pthread_mutex_unlock(&mutex);
	return n;
} //----- End of add

EnOceanCallbackFunction PeriphTable::find(SensorId id) {
	pthread_mutex_lock(&mutex);
	map<SensorId, EnOceanCallbackFunction>::const_iterator hop = periph.find(id);
	EnOceanCallbackFunction ret = (hop != periph.end())? hop->second : NULL;
	pthread_mutex_unlock(&mutex);
	return ret;

} //----- End of read



//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
PeriphTable::PeriphTable() {

} //----- End of PeriphTable

PeriphTable::~PeriphTable() {
} //----- End of ~PeriphTable


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

