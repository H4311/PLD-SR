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
#include <iostream>

//------------------------------------------------------ Personnal Include
#include "DeviceTable.h"
extern "C" {
	#include "../Bdd/mysqlinsert.h"
}
#ifdef SIMULATION
#include "../Simulator/Model/Subject.h"
#endif
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int DeviceTable::add(EnOceanSensorAPI::SensorId id, EnOceanSensorAPI::EnOceanCallbackFunction cf) {
	int n;
	pthread_mutex_lock(&mutex);
	n = (drivers.insert(pair<EnOceanSensorAPI::SensorId,EnOceanSensorAPI::EnOceanCallbackFunction>(id, cf))).second;
	pthread_mutex_unlock(&mutex);
	return n;
} //----- End of add

void DeviceTable::fillFromDB(
#ifdef SIMULATION
		EnOCeanBaseSimulator* simulator, vector<int>* simulatedSensorsID
#endif

) {
	MYSQL* mysql = connectToMysql();
	result* sensors = getCapteurs(mysql);
	closeMysql(mysql);
	for (int i = 0; i < sensors->nbRows; i++) {
		this->add((EnOceanSensorAPI::SensorId)sensors->tab[i][1], (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::getFunctionPerType(sensors->tab[i][0]));
#ifdef SIMULATION
		bool simulated = false;
		for (unsigned int j = 0; j < simulatedSensorsID->size(); j++) {
			if (simulatedSensorsID->at(j) == sensors->tab[i][1]) {
				simulated = true;
				break;
			}
		}
		if (simulated)	{
			Subject* subject = simulator->findSubject(sensors->tab[i][3]);
			simulator->addSensor(SensorSimulator::createSensorSimulator(sensors->tab[i][1], sensors->tab[i][0], subject));
			cout << "<Simulator> Simulated Sensor n°" << sensors->tab[i][1] << " - Created !\n";

		}
#endif
	}
}

bool DeviceTable::del(EnOceanSensorAPI::SensorId id) {
	bool ret;
	pthread_mutex_lock(&mutex);
	map<EnOceanSensorAPI::SensorId, EnOceanSensorAPI::EnOceanCallbackFunction>::iterator it = drivers.find(id);
	ret = (it != drivers.end());
	drivers.erase(it);
	pthread_mutex_unlock(&mutex);
	return ret;
} //----- End of del

EnOceanSensorAPI::EnOceanCallbackFunction DeviceTable::find(EnOceanSensorAPI::SensorId id) {
	pthread_mutex_lock(&mutex);
	map<EnOceanSensorAPI::SensorId, EnOceanSensorAPI::EnOceanCallbackFunction>::const_iterator hop = drivers.find(id);
	EnOceanSensorAPI::EnOceanCallbackFunction ret = (hop != drivers.end())? hop->second : NULL;
	pthread_mutex_unlock(&mutex);
	return ret;

} //----- End of find



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

