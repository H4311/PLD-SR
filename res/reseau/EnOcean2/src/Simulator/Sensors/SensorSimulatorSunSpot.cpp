/*************************************************************************
                           SensorSimulatorSunSpot  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorSunSpot> (SensorSimulatorSunSpot.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorSunSpot.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Patient.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
//float SensorSimulatorSunSpot::getIlluminance() {
//	float t;
//	pthread_mutex_lock(&mutex);
//	t = illuminance;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorSunSpot::setIlluminance(float t) {
//	pthread_mutex_lock(&mutex);
//	illuminance = t;
//	if (illuminance > maxLum) { t = maxLum; }
//	else if (illuminance < minLum) { t = minLum; }
//
//	EnOceanSensorAPI::setIlluminance(&frame, t, minLum, maxLum);
//	pthread_mutex_unlock(&mutex);
//}
//
//float SensorSimulatorSunSpot::getVoltage() {
//	float t;
//	pthread_mutex_lock(&mutex);
//	t = voltage;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorSunSpot::setVoltage(float t) {
//	pthread_mutex_lock(&mutex);
//	voltage = t;
//	if (voltage > maxV) { t = maxV; }
//	else if (voltage < minV) { t = minV; }
//
//	EnOceanSensorAPI::setVoltage(&frame, t, minV, maxV);
//	pthread_mutex_unlock(&mutex);
//}
//
//bool SensorSimulatorSunSpot::getPIRStatus() {
//	bool t;
//	pthread_mutex_lock(&mutex);
//	t = pirStatus;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorSunSpot::setPIRStatus(bool t) {
//	pthread_mutex_lock(&mutex);
//	pirStatus = t;
//	EnOceanSensorAPI::setPIRStatus(&frame, t);
//	pthread_mutex_unlock(&mutex);
//}
//
//bool SensorSimulatorSunSpot::getOccupancy() {
//	bool t;
//	pthread_mutex_lock(&mutex);
//	t = occupancy;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorSunSpot::setOccupancy(bool t) {
//	pthread_mutex_lock(&mutex);
//	occupancy = t;
//	EnOceanSensorAPI::setOccupancy(&frame, t);
//	pthread_mutex_unlock(&mutex);
//}

void SensorSimulatorSunSpot::update() {
//	float voltage = t;
//	if (voltage > maxV) { t = maxV; }
//	else if (voltage < minV) { t = minV; }
	Patient* patient = dynamic_cast<Patient*>(subject);
	if (patient != 0) {
		float t, i, m;
		t = patient->getTemperature();
		if (t > maxTemp) { t = maxTemp; }
		else if (t < minTemp) { t = minTemp; }
		i = patient->getRoom()->getLuminosity();
		if (i > maxLum) { i = maxLum; }
		else if (i < minLum) { i = minLum; }
		m = patient->getMovement();
		if (m > maxMov) { m = maxMov; }
		else if (m < minMov) { m = minMov; }
		EnOceanSensorAPI::setIlluminance(&frame, i, minLum, maxLum);
		EnOceanSensorAPI::setTemperature(&frame, t, minTemp, maxTemp);
		EnOceanSensorAPI::setMovement(&frame,  m, minMov, maxMov);
	}
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorSunSpot::SensorSimulatorSunSpot(int id, Subject* r, float minL, float maxL, float minT, float maxT, float minM, float maxM) : SensorSimulator(id, EnOceanSensorAPI::ORG_4BS, r), minLum(minL), maxLum(maxL), minTemp(minT), maxTemp(maxT), minMov(minM), maxMov(maxM) {
//	illuminance = rand()%(int)(maxLum-minLum) - minLum;
//	voltage = rand()%(int)(maxV-minV) - minV;
//	pirStatus = false;
//	occupancy = false;
	Patient* patient = dynamic_cast<Patient*>(r);
	if (patient != 0) {
		float t, i, m;
		t = patient->getTemperature();
		i = patient->getRoom()->getLuminosity();
		m = patient->getMovement();
		EnOceanSensorAPI::setIlluminance(&frame, i, minLum, maxLum);
		EnOceanSensorAPI::setTemperature(&frame, t, minT, maxT);
		EnOceanSensorAPI::setMovement(&frame,  m, minM, maxM);
		cout << "<Sensor Simu n°" << id << "> Créé - Sunspot\n";

	} else { subject = NULL; }


} //----- End of SensorSimulatorSunSpot

SensorSimulatorSunSpot::~SensorSimulatorSunSpot() {
} //----- End of ~SensorSimulatorSunSpot


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
