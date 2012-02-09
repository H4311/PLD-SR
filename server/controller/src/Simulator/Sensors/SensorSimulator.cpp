
/*************************************************************************
                           SensorSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulator> (SensorSimulator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;

//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"
#include "../../Devices/EnOceanSensorAPI.h"

# include "SensorSimulatorCO2.h"
# include "SensorSimulatorLumAndOcc.h"
# include "SensorSimulatorTempHumi.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
SensorSimulator* SensorSimulator::createSensorSimulator(int id, int type, Room* room) {
	switch(type) {
	case 0x0060001 : { return NULL; }
	case 0x0050201 : { return NULL; }
	case 0x0070205 : { return NULL; }
	case 0x0070401 : { return new SensorSimulatorTempHumi(id, room, 0, 40); }
	case 0x0070801 : { return new SensorSimulatorLumAndOcc(id, room, 0, 510, 0.0, 5.1); }
	case 0x0070901 : { return new SensorSimulatorCO2(id, room, 0, 2000); }
	}
	return NULL;
}


EnOceanSensorAPI::SensorId SensorSimulator::getId() {
	return id;
}

void SensorSimulator::update() {
	return;
}

void SensorSimulator::getFrame(char* buffer) {
	update();
	EnOceanSensorAPI::setCheckSum(&frame);
	EnOceanSensorAPI::toString(&frame, buffer);
}

Room* SensorSimulator::getRoom() {
	return room;
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulator::SensorSimulator(int i, EnOceanSensorAPI::ORG org, Room* r): id(i), room(r){
	EnOceanSensorAPI::setID(&frame, id);
	frame.SYNC_BYTE1 = 0;
	frame.SYNC_BYTE2 = 0;
	frame.H_SEQ_LENGTH = 0; ///< Header identification and number of octets following the header octet
	frame.ORG = 0; ///< Type of telegram
	frame.DATA_BYTE3 = 0; ///< Data Byte 3
	frame.DATA_BYTE2 = 0; ///< Data Byte 2
	frame.DATA_BYTE1 = 0; ///< Data Byte 1
	frame.DATA_BYTE0 = 0; ///< Data Byte 0
	frame.STATUS = 0; ///< Status field
	frame.CHECKSUM = 0;
	EnOceanSensorAPI::setHeader(&frame, org, true);
	pthread_mutex_init(&mutex, NULL);
} //----- End of SensorSimulator

SensorSimulator::~SensorSimulator() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
} //----- End of ~SensorSimulator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
