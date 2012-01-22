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
#include <string>
#include <sstream>


//------------------------------------------------------ Personnal Include
#include "Sensors.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

SensorId getEnOceanID(enocean_data_structure* frame) {
	SensorId id = /*frame->ID_BYTE0 + 255*frame->ID_BYTE1 + 65025*frame->ID_BYTE2 + 16581375*frame->ID_BYTE3*/ 0;
	return id;
} //----- End of getEnOceanID

string analyseRockerSwitch(enocean_data_structure* frame) {
	ostringstream oss;
	oss << "< " << getRockerSwitchAction1st(frame) << " | ";
	oss << getRockerSwitchEnergyBow(frame) << " | ";
	oss << getRockerSwitchAction2nd(frame) << " | ";
	oss << isRockerSwitchAction2nd(frame) << " >/n";
	return oss.str();
} //----- End of analyseRockerSwitch

string analyseTempAndHumidSensor(enocean_data_structure* frame, int minTemp, int maxTemp) {
	ostringstream oss;
	oss << "< " << getTemperature(frame, minTemp, maxTemp) << "�c | ";
	oss << getHumidity(frame) << "% >/n";
	return oss.str();
} //----- End of analyseTempAndHumidSensor



RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame) {
	BYTE info = frame->DATA_BYTE3 >> 5;
	return (RockerSwitchAction)info;
} //----- End of getRockerSwitchAction1st
RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 16) >> 4;
	return (RockerSwitchEnergyBow)info;
} //----- End of getRockerSwitchEnergyBow
RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 14) >> 1;
	return (RockerSwitchAction)info;
} //----- End of getRockerSwitchAction2nd
bool isRockerSwitchAction2nd(enocean_data_structure* frame) {
	BYTE info = (frame->DATA_BYTE3 & 1);
	return info;
} //----- End of isRockerSwitchAction2nd

float getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp) {
	return (float)frame->DATA_BYTE1 * (float)(maxTemp-minTemp) / 250.0 + minTemp;
} //----- End of getTemperature

float getHumidity(enocean_data_structure* frame) {
	return (float)frame->DATA_BYTE2 / 2.5;
} //----- End of getHumidity



