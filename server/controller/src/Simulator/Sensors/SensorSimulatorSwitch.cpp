/*************************************************************************
                           SensorSimulatorSwitch  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorSwitch> (SensorSimulatorSwitch.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorSwitch.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Subject.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
void SensorSimulatorSwitch::update() {
	int v = subject->getClick();
	if (v != 0) { subject->setClick(0); }
	EnOceanSensorAPI::setContact(&frame, v);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorSwitch::SensorSimulatorSwitch(int id, Subject* r) : SensorSimulator(id, EnOceanSensorAPI::ORG_1BS, r) {
	int t = false;
	t = r->getClick();
	EnOceanSensorAPI::setRockerSwitch(&frame, t);
	cout << "<Sensor Simu n°" << id << "> Créé - Switch :" << t << "\n";

} //----- End of SensorSimulatorSwitch

SensorSimulatorSwitch::~SensorSimulatorSwitch() {
} //----- End of ~SensorSimulatorSwitch


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
