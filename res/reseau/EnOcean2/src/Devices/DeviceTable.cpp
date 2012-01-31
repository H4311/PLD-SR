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
#include "DeviceTable.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int DeviceTable::add(EnOceanSensorAPI::SensorId id, EnOceanCallbackFunction cf) {
	int n;
	pthread_mutex_lock(&mutex);
	n = (drivers.insert(pair<EnOceanSensorAPI::SensorId,EnOceanCallbackFunction>(id, cf))).second;
	pthread_mutex_unlock(&mutex);
	return n;
} //----- End of add

EnOceanCallbackFunction DeviceTable::find(EnOceanSensorAPI::SensorId id) {
	pthread_mutex_lock(&mutex);
	map<EnOceanSensorAPI::SensorId, EnOceanCallbackFunction>::const_iterator hop = drivers.find(id);
	EnOceanCallbackFunction ret = (hop != drivers.end())? hop->second : NULL;
	pthread_mutex_unlock(&mutex);
	return ret;

} //----- End of read



//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
DeviceTable::DeviceTable() {
	pthread_mutex_init(&mutex, NULL);
} //----- End of PeriphTable

DeviceTable::~DeviceTable() {
	pthread_mutex_destroy(&mutex);
} //----- End of ~PeriphTable


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

