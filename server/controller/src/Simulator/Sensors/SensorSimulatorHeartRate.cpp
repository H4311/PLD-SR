/*************************************************************************
                           SensorSimulatorHeartRate  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorHeartRate> (SensorSimulatorHeartRate.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorHeartRate.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Patient.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
void SensorSimulatorHeartRate::update() {
	float hRate = 0;
	Patient* patient = dynamic_cast<Patient*>(subject);
	if (patient != 0) {
		hRate = patient->getHeartRate();
	}
	if (hRate > rateMax) { hRate = rateMax; }
	else if (hRate < rateMin) { hRate = rateMin; }
	EnOceanSensorAPI::setHeartRate(&frame, hRate, rateMin, rateMax);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorHeartRate::SensorSimulatorHeartRate(int id, Subject* r, float minp, float maxp) : SensorSimulator(id, EnOceanSensorAPI::ORG_4BS, r), rateMin(minp), rateMax(maxp) {
	float t = 0;
	Patient* patient = dynamic_cast<Patient*>(r);
	if (patient != 0) {
		t = patient->getHeartRate();
	} else { subject = NULL; }
	EnOceanSensorAPI::setHeartRate(&frame, t, rateMin, rateMax);
	cout << "<Sensor Simu n°" << id << "> Créé - " << t << "bpm [" << rateMin << "; " << rateMax << "]\n";

} //----- End of SensorSimulatorHeartRate

SensorSimulatorHeartRate::~SensorSimulatorHeartRate() {
} //----- End of ~SensorSimulatorHeartRate


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
