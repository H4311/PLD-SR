
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

//------------------------------------------------------ Personnal Include
#include "SensorSimulatorTempHumi.h"
#include "../Sensors.h"
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
	EnOceanSensor::setTemperature(&frame, temperature);
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
	EnOceanSensor::setHumidity(&frame, humidity);
	pthread_mutex_unlock(&mutex);
}

void SensorSimulatorTempHumi::getString(char* buffer) {
	EnOceanSensor::toString(&frame, buffer);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorTempHumi::SensorSimulatorTempHumi(int id, int tMin, int tMax) : SensorSimulator(id), tempMin(tMin), tempMax(tMax) {
	frame.DATA_BYTE0 &= 12; // Data frame + Temp° sensor available.
} //----- End of SensorSimulatorTempHumi

SensorSimulatorTempHumi::~SensorSimulatorTempHumi() {
} //----- End of ~SensorSimulatorTempHumi


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
