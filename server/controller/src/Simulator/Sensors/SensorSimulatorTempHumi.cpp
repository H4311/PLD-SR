
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
#include "../Model/Room.h"
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
	float temperature, humidity;
	Room* room = dynamic_cast<Room*>(subject);
	if (room != 0) {
		temperature = room->getTemperature();
		humidity = room->getHumidity();
	}
	if (temperature > tempMax) { temperature = tempMax; }
	else if (temperature < tempMin) { temperature = tempMin; }
	EnOceanSensorAPI::setHumidity(&frame, humidity);
	EnOceanSensorAPI::setTemperature(&frame, temperature, tempMin, tempMax);
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorTempHumi::SensorSimulatorTempHumi(int id, Subject* r, float tMin, float tMax) : SensorSimulator(id, EnOceanSensorAPI::ORG_4BS, r), tempMin(tMin), tempMax(tMax) {
	frame.DATA_BYTE0 = 0xA; // Data frame + Temp� sensor available.
	float t = 0;
	float t2 = r->getTemperature();
	Room* room = dynamic_cast<Room*>(r);
	if (room != 0) {
		t = room->getHumidity();
	} else { subject = NULL; }
	EnOceanSensorAPI::setHumidity(&frame, t);
	EnOceanSensorAPI::setTemperature(&frame, t2, tempMin, tempMax);

	cout << "<Sensor Simu n°" << id << "> Créé - " << t2 << "°c [" << tempMin << "; " << tempMax << "] - " << t << "%\n";

} //----- End of SensorSimulatorTempHumi

SensorSimulatorTempHumi::~SensorSimulatorTempHumi() {
} //----- End of ~SensorSimulatorTempHumi


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
