
/*************************************************************************
                           SensorSimulatorLumAndOcc  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorLumAndOcc> (SensorSimulatorLumAndOcc.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorLumAndOcc.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
//float SensorSimulatorLumAndOcc::getIlluminance() {
//	float t;
//	pthread_mutex_lock(&mutex);
//	t = illuminance;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorLumAndOcc::setIlluminance(float t) {
//	pthread_mutex_lock(&mutex);
//	illuminance = t;
//	if (illuminance > maxLum) { t = maxLum; }
//	else if (illuminance < minLum) { t = minLum; }
//
//	EnOceanSensorAPI::setIlluminance(&frame, t, minLum, maxLum);
//	pthread_mutex_unlock(&mutex);
//}
//
//float SensorSimulatorLumAndOcc::getVoltage() {
//	float t;
//	pthread_mutex_lock(&mutex);
//	t = voltage;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorLumAndOcc::setVoltage(float t) {
//	pthread_mutex_lock(&mutex);
//	voltage = t;
//	if (voltage > maxV) { t = maxV; }
//	else if (voltage < minV) { t = minV; }
//
//	EnOceanSensorAPI::setVoltage(&frame, t, minV, maxV);
//	pthread_mutex_unlock(&mutex);
//}
//
//bool SensorSimulatorLumAndOcc::getPIRStatus() {
//	bool t;
//	pthread_mutex_lock(&mutex);
//	t = pirStatus;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorLumAndOcc::setPIRStatus(bool t) {
//	pthread_mutex_lock(&mutex);
//	pirStatus = t;
//	EnOceanSensorAPI::setPIRStatus(&frame, t);
//	pthread_mutex_unlock(&mutex);
//}
//
//bool SensorSimulatorLumAndOcc::getOccupancy() {
//	bool t;
//	pthread_mutex_lock(&mutex);
//	t = occupancy;
//	pthread_mutex_unlock(&mutex);
//	return t;
//}
//
//void SensorSimulatorLumAndOcc::setOccupancy(bool t) {
//	pthread_mutex_lock(&mutex);
//	occupancy = t;
//	EnOceanSensorAPI::setOccupancy(&frame, t);
//	pthread_mutex_unlock(&mutex);
//}

void SensorSimulatorLumAndOcc::update() {
//	float voltage = t;
//	if (voltage > maxV) { t = maxV; }
//	else if (voltage < minV) { t = minV; }
	float illuminance = 0;
	Room* room = dynamic_cast<Room*>(subject);
	if (room != 0) {
		illuminance = room->getLuminosity();
	}
	if (illuminance > maxLum) { illuminance = maxLum; }
	else if (illuminance < minLum) { illuminance = minLum; }
	EnOceanSensorAPI::setIlluminance(&frame, illuminance, minLum, maxLum);
	EnOceanSensorAPI::setVoltage(&frame, maxV, minV, maxV);
	EnOceanSensorAPI::setOccupancy(&frame, room->getOccupancy());
	EnOceanSensorAPI::setPIRStatus(&frame, room->getPIRStatus());
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorLumAndOcc::SensorSimulatorLumAndOcc(int id, Subject* r, float minL, float maxL, float miV, float maV) : SensorSimulator(id, EnOceanSensorAPI::ORG_4BS, r), minLum(minL), maxLum(maxL), minV(miV), maxV(maV) {
//	illuminance = rand()%(int)(maxLum-minLum) - minLum;
//	voltage = rand()%(int)(maxV-minV) - minV;
//	pirStatus = false;
//	occupancy = false;
	float t = 0;
	Room* room = dynamic_cast<Room*>(r);
	if (room != 0) {
		t = room->getLuminosity();
	} else { subject = NULL; }

	EnOceanSensorAPI::setIlluminance(&frame, t, minLum, maxLum);
	EnOceanSensorAPI::setVoltage(&frame, maxV, minV, maxV);
	EnOceanSensorAPI::setOccupancy(&frame, room->getOccupancy());
	EnOceanSensorAPI::setPIRStatus(&frame, room->getPIRStatus());
	cout << "<Sensor Simu n°" << id << "> Créé - " << room->getLuminosity() << "lx [" << minLum << "; " << maxLum << "] - " << maxV << "V [" << minV << "; " << maxV << "]\n";

} //----- End of SensorSimulatorLumAndOcc

SensorSimulatorLumAndOcc::~SensorSimulatorLumAndOcc() {
} //----- End of ~SensorSimulatorLumAndOcc


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
