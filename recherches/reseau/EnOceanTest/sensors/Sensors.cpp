/*************************************************************************
                           Sensors  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/


//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdio.h>

//------------------------------------------------------ Personnal Include
#include "EnOceanAnalyser.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

SensorId getEnOceanID(enocean_data_structure* frame) {
	SensorId id = frame->ID_BYTE0 + 255*frame->ID_BYTE1 + 65025*frame->ID_BYTE2 + 16581375*frame->ID_BYTE3;
	return id;
}


RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame) {
	BYTE info = frame->DATA_BYTE3 >> 5;
	return info;
}
RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 16) >> 4;
	return info;
}
RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 14) >> 1;
	return info;
}
bool isRockerSwitchAction2nd(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 1);
	return info;
}

float getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp) {
	return (float)frame->DATA_BYTE1 * (float)(maxTemp-minTemp) / 250.0 + minTemp;
}

float getHumidity(enocean_data_structure* frame) {
	return (float)frame->DATA_BYTE2 / 2.5;
}



