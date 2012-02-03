
/*************************************************************************
                           SensorSimulatorTempHumi  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorTempHumi> (SensorSimulatorTempHumi.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorTempHumi.h"
#include "../../Devices/EnOceanSensorAPI.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
//float SensorSimulatorTempHumi::getTemperature() {
//	float t;
//	pthread_mutex_lock(&mutex);
//	t = temperature;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorTempHumi::setTemperature(float t) {
//	pthread_mutex_lock(&mutex);
//	temperature = t;
//	if (temperature > tempMax) { t = tempMax; }
//	else if (temperature < tempMin) { t = tempMin; }
//
//	EnOceanSensorAPI::setTemperature(&frame, t, tempMin, tempMax);
//	pthread_mutex_unlock(&mutex);
//}
//
//float SensorSimulatorTempHumi::getHumidity() {
//	float h;
//	pthread_mutex_lock(&mutex);
//	h = humidity;
//	pthread_mutex_unlock(&mutex);
//	return h;
//}
//
//void SensorSimulatorTempHumi::setHumidity(float h) {
//	pthread_mutex_lock(&mutex);
//	humidity = h;
//	EnOceanSensorAPI::setHumidity(&frame, humidity);
//	pthread_mutex_unlock(&mutex);
//}

void SensorSimulatorTempHumi::update() {
	float temperature = room->getTemperature();
	if (temperature > tempMax) { temperature = tempMax; }
	else if (temperature < tempMin) { temperature = tempMin; }
	EnOceanSensorAPI::setHumidity(&frame, room->getHumidity());
	EnOceanSensorAPI::setTemperature(&frame, temperature, tempMin, tempMax);
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorTempHumi::SensorSimulatorTempHumi(int id, Room* r, float tMin, float tMax) : SensorSimulator(id,r), tempMin(tMin), tempMax(tMax) {
	frame.DATA_BYTE0 = 0xA; // Data frame + Temp� sensor available.
	EnOceanSensorAPI::setHumidity(&frame, room->getHumidity());
	EnOceanSensorAPI::setTemperature(&frame, room->getTemperature(), tempMin, tempMax);

	cout << "<Sensor Simu n°" << id << "> Créé - " << room->getTemperature() << "°c [" << tempMin << "; " << tempMax << "] - " << room->getHumidity() << "%\n";

} //----- End of SensorSimulatorTempHumi

SensorSimulatorTempHumi::~SensorSimulatorTempHumi() {
} //----- End of ~SensorSimulatorTempHumi


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
