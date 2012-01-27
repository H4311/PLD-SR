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


//------------------------------------------------------ Personnal Include
#include "PeriphTable.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int PeriphTable::add(EnOceanSensorAPI::SensorId id, EnOceanCallbackFunction cf) {
	int n;
	pthread_mutex_lock(&mutex);
	n = (periph.insert(pair<EnOceanSensorAPI::SensorId,EnOceanCallbackFunction>(id, cf))).second;
	pthread_mutex_unlock(&mutex);
	return n;
} //----- End of add

EnOceanCallbackFunction PeriphTable::find(EnOceanSensorAPI::SensorId id) {
	pthread_mutex_lock(&mutex);
	map<EnOceanSensorAPI::SensorId, EnOceanCallbackFunction>::const_iterator hop = periph.find(id);
	EnOceanCallbackFunction ret = (hop != periph.end())? hop->second : NULL;
	pthread_mutex_unlock(&mutex);
	return ret;

} //----- End of read



//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
PeriphTable::PeriphTable() {
	pthread_mutex_init(&mutex, NULL);
} //----- End of PeriphTable

PeriphTable::~PeriphTable() {
	pthread_mutex_destroy(&mutex);
} //----- End of ~PeriphTable


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

