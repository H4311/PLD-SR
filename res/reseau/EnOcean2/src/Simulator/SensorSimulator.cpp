
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
#include "../Sensors.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
EnOceanSensorAPI::SensorId SensorSimulator::getId() {
	return id;
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulator::SensorSimulator(int i){
	id = i;
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
	pthread_mutex_init(&mutex, NULL);
} //----- End of SensorSimulator

SensorSimulator::~SensorSimulator() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
} //----- End of ~SensorSimulator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
