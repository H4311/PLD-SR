/*************************************************************************
                           Sensors  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/


#ifndef SENSORS_H_
#define SENSORS_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <map>
#include <string>
#include <mysql/mysql.h>
//------------------------------------------------------ Personnal Include
#include "../Config.h"
#include "EnOceanProtocol.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Description : 
//
//
//------------------------------------------------------------------------ 


//----------------------------------------------------------------- PUBLIC

class EnOceanSensorAPI 
{
public :
	typedef int32_t SensorId;
	typedef string (*EnOceanCallbackFunction)(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);

	typedef enum { ACT_A1 = 0, ACT_A0 = 1, ACT_B1 = 2, ACT_B0 = 3} RockerSwitchAction;
	typedef enum { PRESSED = 0, RELEASED = 1} RockerSwitchEnergyBow;
	typedef enum { ORG_RPS = 5, ORG_1BS = 6, ORG_4BS = 7} ORG;
	
typedef enum { CONTACT = 1, SWITCH, TEMPERATURE, HUMIDITY, LUMINOSITY, OCCUPANCY, MOVEMENT, CO2, HEARTRATE} MeasureType;

	static const unsigned int FRAME_SIZE = 28;

//--------------------------------------------------------- Public Methods

	static void toFrame(enocean_data_structure* frame, char* buffer);
	static void toString(enocean_data_structure* frame, char* buffer);
	
	static SensorId getID(enocean_data_structure* frame);
	static void setID(enocean_data_structure* frame, SensorId id);

	static bool checkSyncBytes(enocean_data_structure* frame);
	static void fillSyncBytes(enocean_data_structure* frame);

	static void fillHSeqLengthBytes(enocean_data_structure * frame, bool receivedMsg);

	static ORG getORG(enocean_data_structure* frame);
	static void setORG(enocean_data_structure* frame, ORG org);

	static int getRepeater(enocean_data_structure* frame);
	static void setRepeater(enocean_data_structure* frame, int rep);

	static bool checkSum(enocean_data_structure* frame);
	static void setCheckSum(enocean_data_structure* frame);

	static bool checkValidity(enocean_data_structure* frame, ORG org);
	static void setHeader(enocean_data_structure* frame, ORG org, bool received);

// ---- ACTUATOR ----
	static void toFrame_Actuator(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, int type, bool switchOn, float value);

	static void toFrame_Switch(enocean_data_structure* frame, SensorId id, bool switchOn);
	static void toFrame_AirConditioning(enocean_data_structure* frame, SensorId id, bool on, float temp, float tempMin, float tempMax);
	static void toFrame_Light(enocean_data_structure* frame, SensorId id, bool on, float val, float minL, float maxL);
	static void toFrame_Aeration(enocean_data_structure* frame, SensorId id, bool on, float val, float valMin, float valMax);
	static void toFrame_Sprinkler(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax);
	static void toFrame_PainKiller(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax);
	static void toFrame_Defibrillator(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on, float val, float valMin, float valMax);
	static void toFrame_Music(enocean_data_structure* frame, EnOceanSensorAPI::SensorId id, bool on);

// ---- SENSOR ----
static EnOceanCallbackFunction getFunctionPerType(int type);


// ---- CONTACT SENSOR ----
	static string analyseContactSensor_EEP_06_00_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);

// ---- ROCKER SWITCH ----
	static string analyseRockerSwitch_EEP_05_02_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);

// ---- TEMP SENSOR ----
	static string analyseTempSensor(enocean_data_structure* frame, float minTemp, float maxTemp, MYSQL* mysql, long long int timestamp);
	static string analyseTempSensor_EEP_07_02_05(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);

// ---- TEMP & HUMID SENSOR ----
	static string analyseTempAndHumidSensor(enocean_data_structure* frame, float minTemp, float maxTemp, MYSQL* mysql, long long int timestamp);
	static string analyseTempAndHumidSensor_EEP_07_04_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);

// ---- LUM & OCC SENSOR ----
	static string analyseLumAndOcc_EEP_07_08_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);
	static string analyseLumAndOcc(enocean_data_structure* frame, float minLum, float maxLum, float minV, float maxV, MYSQL* mysql, long long int timestamp);

// ---- CO2 GAS SENSOR ----
	static string analyseCO2_EEP_07_09_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);
	static string analyseC02(enocean_data_structure* frame, float minPPM, float maxPPM, MYSQL* mysql, long long int timestamp);

// ---- HEART RATE SENSOR ----
	static string analyseHeartRate_EEP_07_0A_01(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);
	static string analyseHeartRate(enocean_data_structure* frame, float minBPM, float maxBPM, MYSQL* mysql, long long int timestamp);

// ---- SUNSPOT SENSOR ----
	static string analyseSunSpot(enocean_data_structure* frame, MYSQL* mysql, long long int timestamp);


// ---- BASIC FUNCTIONS ----
	static RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame);
	static RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame);
	static RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame);
	static bool isRockerSwitchAction2nd(enocean_data_structure* frame);
	static void setRockerSwitch(enocean_data_structure* frame, int val);

	static float getTemperature(enocean_data_structure* frame, float minTemp, float maxTemp);
	static float getTemperatureInverted(enocean_data_structure* frame, float minTemp, float maxTemp);
	static float getHumidity(enocean_data_structure* frame);
	static void setTemperature(enocean_data_structure* frame, float temp, float minTemp, float maxTemp);
	static void setHumidity(enocean_data_structure* frame, float humi);

	static float getIlluminance(enocean_data_structure* frame, float minLum, float maxLum);
	static void setIlluminance(enocean_data_structure* frame, float val, float minLum, float maxLum);
	static float getVoltage(enocean_data_structure* frame, float minV, float maxV);
	static void setVoltage(enocean_data_structure* frame, float val, float minV, float maxV);
	static bool getPIRStatus(enocean_data_structure* frame);
	static void setPIRStatus(enocean_data_structure* frame, bool val);
	static bool getOccupancy(enocean_data_structure* frame);
	static void setOccupancy(enocean_data_structure* frame, bool val);

	static float getCO2Level(enocean_data_structure* frame, float minPPM, float maxPPM);
	static void setCO2Level(enocean_data_structure* frame, float val, float minPPM, float maxPPM);

	static float getHeartRate(enocean_data_structure* frame, float minBPM, float maxBPM);
	static void setHeartRate(enocean_data_structure* frame, float val, float minBPM, float maxBPM);

	static float getMovement(enocean_data_structure* frame, float minBPM, float maxBPM);
	static void setMovement(enocean_data_structure* frame, float val, float minBPM, float maxBPM);

	static void setContact(enocean_data_structure* frame, bool val);
};

//------------------------------ Other definition, depending on this class

#endif /* SENSORS_H_ */
