
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
float SensorSimulatorTempHumi::getTemperature() {
	float t;
	pthread_mutex_lock(&mutex);
	t = temperature;
	pthread_mutex_unlock(&mutex);
	return t;
}

void SensorSimulatorTempHumi::setTemperature(float t) {
	pthread_mutex_lock(&mutex);
	temperature = t;
	if (temperature > tempMax) { t = tempMax; }
	else if (temperature < tempMin) { t = tempMin; }

	EnOceanSensorAPI::setTemperature(&frame, t, tempMin, tempMax);
	pthread_mutex_unlock(&mutex);
}

float SensorSimulatorTempHumi::getHumidity() {
	float h;
	pthread_mutex_lock(&mutex);
	h = humidity;
	pthread_mutex_unlock(&mutex);
	return h;
}

void SensorSimulatorTempHumi::setHumidity(float h) {
	pthread_mutex_lock(&mutex);
	humidity = h;
	EnOceanSensorAPI::setHumidity(&frame, humidity);
	pthread_mutex_unlock(&mutex);
}

void SensorSimulatorTempHumi::getFrame(char* buffer) {
	EnOceanSensorAPI::toString(&frame, buffer);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorTempHumi::SensorSimulatorTempHumi(int id, int tMin, int tMax) : SensorSimulator(id), tempMin(tMin), tempMax(tMax) {
	temperature = rand()%(tMax-tMin) - tMin;
	humidity = rand()%100;
	frame.DATA_BYTE0 = 0xA; // Data frame + Temp� sensor available.
	EnOceanSensorAPI::setHumidity(&frame, humidity);
	EnOceanSensorAPI::setTemperature(&frame, temperature, tempMin, tempMax);

	cout << "<Sensor Simu n°" << id << "> Créé - " << temperature << "°c [" << tempMin << "; " << tempMax << "] - " << humidity << "%\n";

} //----- End of SensorSimulatorTempHumi

SensorSimulatorTempHumi::~SensorSimulatorTempHumi() {
} //----- End of ~SensorSimulatorTempHumi


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
