/*************************************************************************
                           SensorSimulatorContact  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorContact> (SensorSimulatorContact.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorContact.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
void SensorSimulatorContact::update() {
	bool v = false;
	Room* room = dynamic_cast<Room*>(subject);
	if (room != 0) {
		v = room->getDoorState();
	}
	EnOceanSensorAPI::setContact(&frame, v);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorContact::SensorSimulatorContact(int id, Subject* r) : SensorSimulator(id, EnOceanSensorAPI::ORG_1BS, r) {
	bool t = false;
	Room* room = dynamic_cast<Room*>(r);
	if (room != 0) {
		t = room->getDoorState();
	} else { subject = NULL; }
	EnOceanSensorAPI::setContact(&frame, t);
	cout << "<Sensor Simu n°" << id << "> Créé - Contact :" << (t? "yes":"no") << "\n";

} //----- End of SensorSimulatorContact

SensorSimulatorContact::~SensorSimulatorContact() {
} //----- End of ~SensorSimulatorContact


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
