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
#include <stdlib.h>
//------------------------------------------------------ Personnal Include
#include "Sensors.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

	void EnOceanSensorAPI::toFrame(enocean_data_structure* frame, char* buffer) {
		BYTE* byte = (BYTE*)frame;
		BYTE temp;
		char c[3] = {'0', '0', 0};
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE; i += 2) {
			c[0] = buffer[i];
			c[1] = buffer[i+1];
			temp = strtol(c,NULL,16);
			*byte = temp;
			byte += sizeof(BYTE);
		}
	}
	
	char fromHexToChar (BYTE hex) {
		if (hex <= 9) { return ('0'+hex); }
		else { return ('A'+(hex-10)); }
	}

	void EnOceanSensorAPI::toString(enocean_data_structure* frame, char* buffer) {
		BYTE* byte = (BYTE*)frame;
		int temp;
		char c;
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE; i += 2) {
			temp = *byte;
			if (temp < 0) { temp = 255 - temp; }
			temp = *byte & 15;
			c = fromHexToChar(temp);
			buffer[i+1] = c;
			temp = *byte >> 4;
			c = fromHexToChar(temp);
			buffer[i] = c;
			byte += sizeof(BYTE);
		}
	}
	
	
	
	
	
	void EnOceanSensorAPI::setID(enocean_data_structure* frame, SensorId id) {
		frame->ID_BYTE0 = id & 255;
		id = id >> 8;
		frame->ID_BYTE1 = id & 255;
		id = id >> 8;
		frame->ID_BYTE2 = id & 255;
		id = id >> 8;
		frame->ID_BYTE3 = id & 255;
	}

	EnOceanSensorAPI::SensorId EnOceanSensorAPI::getID(enocean_data_structure* frame) {
		SensorId id = frame->ID_BYTE0;
		id += frame->ID_BYTE1 << 8;
		id += frame->ID_BYTE2 << 16;
		id += frame->ID_BYTE3 << 24;
		return id;
	} //----- End of getEnOceanID

	string EnOceanSensorAPI::analyseContactSensor_D5_00_01(enocean_data_structure* frame) {
			ostringstream oss;
			bool isLearning, contact;
			isLearning = (frame->DATA_BYTE0 >> 3) & 0;
			contact = frame->DATA_BYTE0 & 1;
			oss << "Contact : " << (contact?"Yes":"No") << " | Learning : " << (isLearning?"Yes":"No") << " >";
			return oss.str();
		} //----- End of analyseContactSensor_D5_00_01

	string EnOceanSensorAPI::analyseRockerSwitch_F6_02_01(enocean_data_structure* frame) {
			ostringstream oss;
			oss << "< " << getRockerSwitchAction1st(frame) << " | ";
			oss << getRockerSwitchEnergyBow(frame) << " | ";
			oss << getRockerSwitchAction2nd(frame) << " | ";
			oss << isRockerSwitchAction2nd(frame) << " >";
			return oss.str();
		} //----- End of analyseRockerSwitch_F6_02_01

	string EnOceanSensorAPI::analyseTempSensor(enocean_data_structure* frame, int minTemp, int maxTemp) {
		ostringstream oss;
		bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		if (dataFrame) {
			oss << "< " << getTemperatureInverted(frame, minTemp, maxTemp) << "�c >";
		}
		return oss.str();
	} //----- End of analyseTempSensor

	string EnOceanSensorAPI::analyseTempSensor_EEP_07_02_05(enocean_data_structure* frame) {
			return analyseTempSensor(frame,0 , 40);
		} //----- End of analyseTempAndHumidSensor_EEP_07_02_05

	string EnOceanSensorAPI::analyseTempAndHumidSensor(enocean_data_structure* frame, int minTemp, int maxTemp) {
		ostringstream oss;
		bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		if (dataFrame) {
			if ((frame->DATA_BYTE0 >> 1) & 1) { // If temperature sensor is available :
				oss << "< " << getTemperature(frame, minTemp, maxTemp) << "�c | ";
			}
			oss << getHumidity(frame) << "% >/n";
		}
		return oss.str();
	} //----- End of analyseTempAndHumidSensor

	string EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01(enocean_data_structure* frame) {
		return analyseTempAndHumidSensor(frame,0 , 40);
	} //----- End of analyseTempAndHumidSensor_EEP_07_04_01

	string EnOceanSensorAPI::analyseLumAndOcc_EEP_07_08_01(enocean_data_structure* frame) {
		return analyseLumAndOcc(frame, 0, 510, 0.0, 5.1);
	} //----- End of analyseLumAndOcc_EEP_07_08_01

	string EnOceanSensorAPI::analyseLumAndOcc(enocean_data_structure* frame, int minLum, int maxLum, float minV, float maxV) {
		ostringstream oss;
		float lum = getLuminosity(frame, minLum, maxLum);
		float volt = getVoltage(frame, minV, maxV);
		bool pir = getPIRStatus(frame);
		bool occ = getOccupancy(frame);
		oss << "< Lum : " << lum << "lx | Volt : " << volt << "V | PIR : " << (pir?"ON":"OFF") << " | Occ : " << (occ?"Pressed":"Released");
		return oss.str();
	} //----- End of analyseLumAndOcc

	EnOceanSensorAPI::RockerSwitchAction EnOceanSensorAPI::getRockerSwitchAction1st(enocean_data_structure* frame) {
		BYTE info = frame->DATA_BYTE3 >> 5;
		return (EnOceanSensorAPI::RockerSwitchAction)info;
	} //----- End of getRockerSwitchAction1st

	EnOceanSensorAPI::RockerSwitchEnergyBow EnOceanSensorAPI::getRockerSwitchEnergyBow(enocean_data_structure* frame) {
		BYTE info = (frame->DATA_BYTE3 & 16) >> 4;
		return (EnOceanSensorAPI::RockerSwitchEnergyBow)info;
	} //----- End of getRockerSwitchEnergyBow
	EnOceanSensorAPI::RockerSwitchAction EnOceanSensorAPI::getRockerSwitchAction2nd(enocean_data_structure* frame) {
		BYTE info = (frame->DATA_BYTE3 & 14) >> 1;
		return (EnOceanSensorAPI::RockerSwitchAction)info;
	} //----- End of getRockerSwitchAction2nd
	bool EnOceanSensorAPI::isRockerSwitchAction2nd(enocean_data_structure* frame) {
		BYTE info = (frame->DATA_BYTE3 & 1);
		return info;
	} //----- End of isRockerSwitchAction2nd

	float EnOceanSensorAPI::getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		return (float)frame->DATA_BYTE1 * multiplyer + (float)( (multiplyer>=0)? minTemp : maxTemp );
	} //----- End of getTemperature

	float EnOceanSensorAPI::getTemperatureInverted(enocean_data_structure* frame, int minTemp, int maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		BYTE invert = ~frame->DATA_BYTE1;
		return (float)invert * multiplyer + (float)( (multiplyer>=0)? minTemp : maxTemp );
	} //----- End of getTemperature

	void EnOceanSensorAPI::setTemperature(enocean_data_structure* frame, float temp, int minTemp, int maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		frame->DATA_BYTE1 = (BYTE)((temp - (float)( (multiplyer>=0)? minTemp : maxTemp )) / multiplyer);
	} //----- End of setTemperature

	float EnOceanSensorAPI::getHumidity(enocean_data_structure* frame) {
		return (float)frame->DATA_BYTE2 / 2.55;
	} //----- End of getHumidity

	void EnOceanSensorAPI::setHumidity(enocean_data_structure* frame, float humi) {
		frame->DATA_BYTE2 = (BYTE)(humi * 2.55);
	} //----- End of setHumidity

	float EnOceanSensorAPI::getLuminosity(enocean_data_structure* frame, int minLum, int maxLum) {
		float multiplyer = (float)(maxLum-minLum) / 255.0;
		return (float)frame->DATA_BYTE2 * multiplyer + (float)( (multiplyer>=0)? minLum : maxLum );
	}

	float EnOceanSensorAPI::getVoltage(enocean_data_structure* frame, float minV, float maxV) {
		float multiplyer = (float)(maxV-minV) / 255.0;
		return (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? minV : maxV );
	}

	bool EnOceanSensorAPI::getPIRStatus(enocean_data_structure* frame) {
		return (!(frame->DATA_BYTE0 & 2));
	}

	bool EnOceanSensorAPI::getOccupancy(enocean_data_structure* frame) {
		return (frame->DATA_BYTE0 & 0);
	}

