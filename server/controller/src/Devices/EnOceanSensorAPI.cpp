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
extern "C" {
	#include "../Bdd/mysqlinsert.h"
}
//------------------------------------------------------ Personnal Include
#include "EnOceanSensorAPI.h"

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

	bool EnOceanSensorAPI::checkSyncBytes(enocean_data_structure* frame) {
		return ((frame->SYNC_BYTE1 == 0xA5) && (frame->SYNC_BYTE2 == 0x5A));
	}

	void EnOceanSensorAPI::fillSyncBytes(enocean_data_structure * frame) {
		frame->SYNC_BYTE2 = 0x5A;
		frame->SYNC_BYTE1 = 0xA5;
		return;
	}

	void EnOceanSensorAPI::fillHSeqLengthBytes(enocean_data_structure * frame, bool receivedMsg) {
		frame->H_SEQ_LENGTH = receivedMsg?0x0B:0x6B;
		return;
	}

	EnOceanSensorAPI::ORG EnOceanSensorAPI::getORG(enocean_data_structure* frame) {
		return (ORG)frame->ORG;
	}

	void EnOceanSensorAPI::setORG(enocean_data_structure* frame, ORG org) {
		frame->ORG = (BYTE)org;
	}

	int EnOceanSensorAPI::getRepeater(enocean_data_structure* frame) {
		return frame->STATUS & 15;
	}

	void EnOceanSensorAPI::setRepeater(enocean_data_structure* frame, int rep) {
		frame->STATUS &= 240;
		frame->STATUS |= (rep%16);
		return;
	}

	bool EnOceanSensorAPI::checkSum(enocean_data_structure* frame) {
		int sum = 0;
		BYTE* byte = (BYTE*)frame;
		for (unsigned int i = 0; i < 13; i++) {
			sum += *byte;
			byte += sizeof(BYTE);
		}
		sum = sum & 255; // Getting the last byte of the sum.
		return (frame->CHECKSUM == sum);
	}

	void EnOceanSensorAPI::setCheckSum(enocean_data_structure* frame) {
		int sum = 0;
		BYTE* byte = (BYTE*)frame;
		for (unsigned int i = 0; i < 13; i++) {
			sum += *byte;
			byte += sizeof(BYTE);
		}
		sum = sum & 255; // Getting the last byte of the sum.
		frame->CHECKSUM = sum;
		return;
	}

	bool EnOceanSensorAPI::checkValidity(enocean_data_structure* frame, EnOceanSensorAPI::ORG org) {
		return (checkSyncBytes(frame) && checkSum(frame) && (getORG(frame) == org));
	}

	void EnOceanSensorAPI::setHeader(enocean_data_structure* frame, EnOceanSensorAPI::ORG org, bool received) {
		fillSyncBytes(frame);
		fillHSeqLengthBytes(frame, received);
		setORG(frame, org);
		return;
	}


// ---- ACTUATOR ----

	void EnOceanSensorAPI::toFrame_Actuator(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, int type, bool switchOn, float value) {
			switch (type) {
			// Switch :
			case 0x1050201 : { toFrame_Switch(frame, id, !switchOn); break; }

			// Air Cond :
			case 0x1070201 : { toFrame_AirConditioning(frame, id, switchOn, value, -40.0, 0.0); break; }
			case 0x1070202 : { toFrame_AirConditioning(frame, id, switchOn, value, -30.0, 10.0); break; }
			case 0x1070203 : { toFrame_AirConditioning(frame, id, switchOn, value, -20.0, 20.0); break; }
			case 0x1070204 : { toFrame_AirConditioning(frame, id, switchOn, value, -10.0, 30.0); break; }
			case 0x1070205 : { toFrame_AirConditioning(frame, id, switchOn, value, 0.0, 40.0); break; }
			case 0x1070206 : { toFrame_AirConditioning(frame, id, switchOn, value, 10.0, 50.0); break; }
			case 0x1070207 : { toFrame_AirConditioning(frame, id, switchOn, value, 20.0, 60.0); break; }
			case 0x1070208 : { toFrame_AirConditioning(frame, id, switchOn, value, 30.0, 70.0); break; }
			case 0x1070209 : { toFrame_AirConditioning(frame, id, switchOn, value, 40.0, 80.0); break; }
			case 0x107020A : { toFrame_AirConditioning(frame, id, switchOn, value, 50.0, 90.0); break; }
			case 0x107020B : { toFrame_AirConditioning(frame, id, switchOn, value, 60.0, 100.0); break; }
			case 0x1070210 : { toFrame_AirConditioning(frame, id, switchOn, value, -60.0, 20.0); break; }
			case 0x1070211 : { toFrame_AirConditioning(frame, id, switchOn, value, -50.0, 30.0); break; }
			case 0x1070212 : { toFrame_AirConditioning(frame, id, switchOn, value, -40.0, 40.0); break; }
			case 0x1070213 : { toFrame_AirConditioning(frame, id, switchOn, value, -30.0, 50.0); break; }
			case 0x1070214 : { toFrame_AirConditioning(frame, id, switchOn, value, -20.0, 60.0); break; }
			case 0x1070215 : { toFrame_AirConditioning(frame, id, switchOn, value, -10.0, 70.0); break; }
			case 0x1070216 : { toFrame_AirConditioning(frame, id, switchOn, value, 0.0, 80.0); break; }
			case 0x1070217 : { toFrame_AirConditioning(frame, id, switchOn, value, 10.0, 90.0); break; }
			case 0x1070218 : { toFrame_AirConditioning(frame, id, switchOn, value, 20.0, 100.0); break; }
			case 0x1070219 : { toFrame_AirConditioning(frame, id, switchOn, value, 30.0, 110.0); break; }
			case 0x107021A : { toFrame_AirConditioning(frame, id, switchOn, value, 40.0, 120.0); break; }
			case 0x107021B : { toFrame_AirConditioning(frame, id, switchOn, value, 50.0, 130.0); break; }

			// Light :
			case 0x1070601 : { toFrame_Light(frame, id, switchOn, value, 300.0, 60000.0); break; }
			case 0x1070602 : { toFrame_Light(frame, id, switchOn, value, 0.0, 1024.0); break; }

			// Aeration :
			case 0x1070901 : { toFrame_Aeration(frame, id, switchOn, value, 200.0, 1000.0); break; }

			// Sprinkler :
			case 0x1070A01 : { toFrame_Sprinkler(frame, id, switchOn, value, 0.0, 10.0); break; }

			// Pain-killer :
			case 0x1070B01 : { toFrame_PainKiller(frame, id, switchOn, value, 0.0, 10.0); break; }

			// Defibrillator :
			case 0x1070C01 : { toFrame_Defibrillator(frame, id, switchOn, value, 0.0, 10.0); break; }
			}
		}

	void EnOceanSensorAPI::toFrame_Switch(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool switchOn) {
		EnOceanSensorAPI::setID(frame, id);
		frame->SYNC_BYTE1 = 0;
		frame->SYNC_BYTE2 = 0;
		frame->H_SEQ_LENGTH = 0; ///< Header identification and number of octets following the header octet
		frame->DATA_BYTE3 = (switchOn)? 0x70 : 0x50;
		frame->DATA_BYTE2 = 0;
		frame->DATA_BYTE1 = 0; ///< Data Byte 1
		frame->DATA_BYTE0 = 0; ///< Data Byte 0
		frame->STATUS = 0x30; ///< Status field
		frame->CHECKSUM = 0;
		setHeader(frame, ORG_RPS, false);
		setCheckSum(frame);
		return;
	}

	void  EnOceanSensorAPI::toFrame_AirConditioning(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float temp, float tempMin, float tempMax) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		EnOceanSensorAPI::setTemperature(frame, temp, tempMin, tempMax);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);

		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

	void  EnOceanSensorAPI::toFrame_Light(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float minL, float maxL) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		EnOceanSensorAPI::setIlluminance(frame, val, minL, maxL);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);
		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

	void  EnOceanSensorAPI::toFrame_Aeration(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		float multiplyer = (float)(valMax-valMin) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? valMin : valMax )) / multiplyer);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);
		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

	void  EnOceanSensorAPI::toFrame_Sprinkler(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		float multiplyer = (float)(valMax-valMin) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? valMin : valMax )) / multiplyer);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);
		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

	void  EnOceanSensorAPI::toFrame_PainKiller(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		float multiplyer = (float)(valMax-valMin) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? valMin : valMax )) / multiplyer);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);
		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

	void  EnOceanSensorAPI::toFrame_Defibrillator(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax) {
		BYTE* byte = (BYTE*)(frame);
		for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
			*byte = 0;
			byte += sizeof(BYTE);
		}
		EnOceanSensorAPI::setID(frame, (EnOceanSensorAPI::SensorId)id);
		float multiplyer = (float)(valMax-valMin) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? valMin : valMax )) / multiplyer);
		frame->DATA_BYTE0 = on?(1<<3):(0<<3);
		EnOceanSensorAPI::setHeader(frame, EnOceanSensorAPI::ORG_4BS, false);
		EnOceanSensorAPI::setCheckSum(frame);

		return;
	}

// ---- SENSOR ----
	EnOceanSensorAPI::EnOceanCallbackFunction EnOceanSensorAPI::getFunctionPerType(int type) {
		switch(type) {
		case 0x0060001 : { return analyseContactSensor_EEP_06_00_01; }
		case 0x0050201 : { return analyseRockerSwitch_EEP_05_02_01; }
		case 0x0070205 : { return analyseTempSensor_EEP_07_02_05; }
		case 0x0070401 : { return analyseTempAndHumidSensor_EEP_07_04_01; }
		case 0x0070801 : { return analyseLumAndOcc_EEP_07_08_01; }
		case 0x0070901 : { return analyseCO2_EEP_07_09_01; }
		case 0x0070A01 : { return analyseHeartRate_EEP_07_0A_01; }
		case 0x00A0001 : { return analyseSunSpot; }
		}
		return NULL;
	}

// ---- CONTACT SENSOR ----

	string EnOceanSensorAPI::analyseContactSensor_EEP_06_00_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		bool isLearning, contact;
		isLearning = (frame->DATA_BYTE0 >> 3) & 0;
		contact = frame->DATA_BYTE0 & 1;
		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, CONTACT, (contact?1:0));
		//insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 1, (isLearning?1:0));
		oss << "Contact : " << (contact?"Yes":"No") << " | Learning : " << (isLearning?"Yes":"No") << " >";
		return oss.str();
	} //----- End of analyseContactSensor_D5_00_01


// ---- ROCKER SWITCH ----

	string EnOceanSensorAPI::analyseRockerSwitch_EEP_05_02_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		oss << "< " << getRockerSwitchAction1st(frame) << " | ";
		oss << getRockerSwitchEnergyBow(frame) << " | ";
		oss << getRockerSwitchAction2nd(frame) << " | ";
		oss << isRockerSwitchAction2nd(frame) << " >";

		int action = (getRockerSwitchAction1st(frame)+getRockerSwitchEnergyBow(frame))*16+(getRockerSwitchAction2nd(frame)*(isRockerSwitchAction2nd(frame)?1:0));
		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, SWITCH, action);
//		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 1, getRockerSwitchEnergyBow(frame));
//		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 2, getRockerSwitchAction2nd(frame));
//		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 3, isRockerSwitchAction2nd(frame));
		return oss.str();
	} //----- End of analyseRockerSwitch_F6_02_01


// ---- TEMP & HUMID SENSOR ----

	string EnOceanSensorAPI::analyseTempSensor(enocean_data_structure* frame, float minTemp, float maxTemp, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		if (dataFrame) {
			oss << "< " << getTemperatureInverted(frame, minTemp, maxTemp) << "�c >";
			insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, TEMPERATURE, getTemperatureInverted(frame, minTemp, maxTemp));
		}
		return oss.str();
	} //----- End of analyseTempSensor

	string EnOceanSensorAPI::analyseTempSensor_EEP_07_02_05(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
			return analyseTempSensor(frame,0 , 40, mysql, timestamp);
		} //----- End of analyseTempAndHumidSensor_EEP_07_02_05

	string EnOceanSensorAPI::analyseTempAndHumidSensor(enocean_data_structure* frame, float minTemp, float maxTemp, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		if (dataFrame) {
			if ((frame->DATA_BYTE0 >> 1) & 1) { // If temperature sensor is available :
				insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, TEMPERATURE, getTemperature(frame, minTemp, maxTemp));
				oss << "< " << getTemperature(frame, minTemp, maxTemp) << "�c | ";
			}
			insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, HUMIDITY, getHumidity(frame));
			oss << getHumidity(frame) << "% >/n";
		}
		return oss.str();
	} //----- End of analyseTempAndHumidSensor

	string EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		return analyseTempAndHumidSensor(frame,0 , 40, mysql, timestamp);
	} //----- End of analyseTempAndHumidSensor_EEP_07_04_01


// ---- LUM & OCC SENSOR ----

	string EnOceanSensorAPI::analyseLumAndOcc_EEP_07_08_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		return analyseLumAndOcc(frame, 0, 510, 0.0, 5.1, mysql, timestamp);
	} //----- End of analyseLumAndOcc_EEP_07_08_01

	string EnOceanSensorAPI::analyseLumAndOcc(enocean_data_structure* frame, float minLum, float maxLum, float minV, float maxV, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		float lum = getIlluminance(frame, minLum, maxLum);
		float volt = getVoltage(frame, minV, maxV);
		bool pir = getPIRStatus(frame);
		bool occ = getOccupancy(frame);
		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, LUMINOSITY, getIlluminance(frame, minLum, maxLum)*100);
//		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 1, getVoltage(frame, minV, maxV));
//		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, 2, getPIRStatus(frame));
		insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, OCCUPANCY, getOccupancy(frame));
		oss << "< Lum : " << lum << "lx | Volt : " << volt << "V | PIR : " << (pir?"ON":"OFF") << " | Occ : " << (occ?"Pressed":"Released");
		return oss.str();
	} //----- End of analyseLumAndOcc


// ---- CO2 GAS SENSOR ----
	string EnOceanSensorAPI::analyseCO2_EEP_07_09_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		return analyseC02(frame, 0, 2000, mysql, timestamp);
	} //----- End of analyseCO2_EEP_07_09_01

	string EnOceanSensorAPI::analyseC02(enocean_data_structure* frame, float minPPM, float maxPPM, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		//bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		//if (dataFrame) {
			oss << "< CO2 : " << getCO2Level(frame, minPPM, maxPPM) << "ppm. >";
			insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, CO2, getCO2Level(frame, minPPM, maxPPM));
		//}
		return oss.str();
	} //----- End of analyseC02


// ---- HEART RATE SENSOR ----
	string EnOceanSensorAPI::analyseHeartRate_EEP_07_0A_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		return analyseHeartRate(frame, 0, 400, mysql, timestamp);
	} //----- End of analyseHeartRate_EEP_07_0A_01
	string EnOceanSensorAPI::analyseHeartRate(enocean_data_structure* frame, float minBPM, float maxBPM, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		bool dataFrame = (frame->DATA_BYTE0 >> 3) & 1;
		if (dataFrame) {
			oss << "< Heart-Rate : " << getHeartRate(frame, minBPM, maxBPM) << "bpm. >";
			insertMesure(mysql, CAPTEUR_ENOCEAN, (int)getID(frame), timestamp, HEARTRATE, getHeartRate(frame, minBPM, maxBPM));
		}
		return oss.str();
	} //----- End of analyseHeartRate

// ---- SUNSPOT SENSOR ----
	string EnOceanSensorAPI::analyseSunSpot(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp) {
		ostringstream oss;
		float lum = getIlluminance(frame, 0.0, 750.0);
		float temp = getTemperature(frame, -40.0, 60.0);
		float mov = getMovement(frame, 0.0, 10.0);
		insertMesure(mysql, CAPTEUR_SUNSPOT, (int)getID(frame), timestamp, LUMINOSITY, lum);
		insertMesure(mysql, CAPTEUR_SUNSPOT, (int)getID(frame), timestamp, TEMPERATURE, temp);
		insertMesure(mysql, CAPTEUR_SUNSPOT, (int)getID(frame), timestamp, MOVEMENT, mov);
		oss << "< Lum : " << lum << "lx | Temp : " << temp << "°c | Mov : " << mov << " >";
		return oss.str();
	} //----- End of analyseSunSpot


// ---- BASIC FUNCTIONS ----

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

	void EnOceanSensorAPI::setRockerSwitch(enocean_data_structure* frame, int val) {
		int fstAction = val / 16;
		int scdAction = val % 16;
		frame->DATA_BYTE3 = fstAction >> 5;
		frame->DATA_BYTE3 += scdAction >> 1;
		if (scdAction != 0) {
			frame->DATA_BYTE3 += 1;
		}
	} //----- End of setTemperature


	float EnOceanSensorAPI::getTemperature(enocean_data_structure* frame, float minTemp, float maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		return (float)frame->DATA_BYTE1 * multiplyer + (float)( (multiplyer>=0)? minTemp : maxTemp );
	} //----- End of getTemperature

	float EnOceanSensorAPI::getTemperatureInverted(enocean_data_structure* frame, float minTemp, float maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		BYTE invert = ~frame->DATA_BYTE1;
		return (float)invert * multiplyer + (float)( (multiplyer>=0)? minTemp : maxTemp );
	} //----- End of getTemperature

	void EnOceanSensorAPI::setTemperature(enocean_data_structure* frame, float temp, float minTemp, float maxTemp) {
		float multiplyer = (float)(maxTemp-minTemp) / 255.0;
		frame->DATA_BYTE1 = (BYTE)((temp - (float)( (multiplyer>=0)? minTemp : maxTemp )) / multiplyer);
	} //----- End of setTemperature

	float EnOceanSensorAPI::getHumidity(enocean_data_structure* frame) {
		return (float)frame->DATA_BYTE2 / 2.55;
	} //----- End of getHumidity

	void EnOceanSensorAPI::setHumidity(enocean_data_structure* frame, float humi) {
		frame->DATA_BYTE2 = (BYTE)(humi * 2.55);
	} //----- End of setHumidity

	float EnOceanSensorAPI::getIlluminance(enocean_data_structure* frame, float minLum, float maxLum) {
		float multiplyer = (float)(maxLum-minLum) / 255.0;
		return (float)frame->DATA_BYTE2 * multiplyer + (float)( (multiplyer>=0)? minLum : maxLum );
	}

	void EnOceanSensorAPI::setIlluminance(enocean_data_structure* frame, float val, float minL, float maxL) {
		float multiplyer = (float)(maxL-minL) / 255.0;
		frame->DATA_BYTE2 = (BYTE)((val - (float)( (multiplyer>=0)? minL : maxL )) / multiplyer);
	} //----- End of setIlluminance

	float EnOceanSensorAPI::getVoltage(enocean_data_structure* frame, float minV, float maxV) {
		float multiplyer = (float)(maxV-minV) / 255.0;
		return (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? minV : maxV );
	}

	void EnOceanSensorAPI::setVoltage(enocean_data_structure* frame, float val, float minV, float maxV) {
			float multiplyer = (float)(maxV-minV) / 255.0;
			frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? minV : maxV )) / multiplyer);
		} //----- End of setVoltage

	bool EnOceanSensorAPI::getPIRStatus(enocean_data_structure* frame) {
		return (!(frame->DATA_BYTE0 & 2));
	}

	void EnOceanSensorAPI::setPIRStatus(enocean_data_structure* frame, bool val) {
		if (val) {
			frame->DATA_BYTE0 &= ~(1 << 1);
		}
		else {
			frame->DATA_BYTE0 |= 1 << 1;
		}
	}

	bool EnOceanSensorAPI::getOccupancy(enocean_data_structure* frame) {
		return (frame->DATA_BYTE0 & 0);
	}

	void EnOceanSensorAPI::setOccupancy(enocean_data_structure* frame, bool val) {
			if (val) {
				frame->DATA_BYTE0 &= ~(1 << 0);
			}
			else {
				frame->DATA_BYTE0 |= 1 << 0;
			}
		}


	float EnOceanSensorAPI::getCO2Level(enocean_data_structure* frame, float minPPM, float maxPPM) {
		float multiplyer = (float)(maxPPM-minPPM) / 255.0;
		return (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? minPPM : maxPPM );
	}

	void EnOceanSensorAPI::setCO2Level(enocean_data_structure* frame, float val, float minPPM, float maxPPM) {
		float multiplyer = (float)(maxPPM-minPPM) / 255.0;
		frame->DATA_BYTE0 = 1 >> 3;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? minPPM : maxPPM )) / multiplyer);
	}


	float EnOceanSensorAPI::getHeartRate(enocean_data_structure* frame, float minBPM, float maxBPM) {
		float multiplyer = (float)(maxBPM-minBPM) / 255.0;
		return (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? minBPM : maxBPM );
	}
	void EnOceanSensorAPI::setHeartRate(enocean_data_structure* frame, float val, float minBPM, float maxBPM) {
		float multiplyer = (float)(maxBPM-minBPM) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? minBPM : maxBPM )) / multiplyer);
	}

	float EnOceanSensorAPI::getMovement(enocean_data_structure* frame, float minBPM, float maxBPM) {
		float multiplyer = (float)(maxBPM-minBPM) / 255.0;
		return (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? minBPM : maxBPM );
	}
	void EnOceanSensorAPI::setMovement(enocean_data_structure* frame, float val, float minBPM, float maxBPM) {
		float multiplyer = (float)(maxBPM-minBPM) / 255.0;
		frame->DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? minBPM : maxBPM )) / multiplyer);
	}

	void EnOceanSensorAPI::setContact(enocean_data_structure* frame, bool val) {
		frame->DATA_BYTE0 = val? 1 : 0;
	}

