
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
# include "SensorSimulatorContact.h"
# include "SensorSimulatorSwitch.h"
# include "SensorSimulatorSunSpot.h"
# include "SensorSimulatorHeartRate.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
SensorSimulator* SensorSimulator::createSensorSimulator(int id, int type, Subject* subject) {
	switch(type) {
	case 0x0060001 : { return new SensorSimulatorContact(id, subject); }
	case 0x0050201 : { return new SensorSimulatorSwitch(id, subject); }
	case 0x0070205 : { return NULL; }
	case 0x0070A01 : {  return new SensorSimulatorHeartRate(id, subject, 0, 400); }
	case 0x0070401 : { return new SensorSimulatorTempHumi(id, subject, 0, 40); }
	case 0x0070801 : { return new SensorSimulatorLumAndOcc(id, subject, 0, 510, 0.0, 5.1); }
	case 0x0070901 : { return new SensorSimulatorCO2(id, subject, 0, 2000); }
	case 0x00A0001 : { return new SensorSimulatorSunSpot(id, subject, 0.0, 750.0, -40.0, 60.0, 0.0, 10.0); }
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

Subject* SensorSimulator::getSubject() {
	return subject;
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulator::SensorSimulator(int i, EnOceanSensorAPI::ORG org, Subject* r): id(i), subject(r){
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
