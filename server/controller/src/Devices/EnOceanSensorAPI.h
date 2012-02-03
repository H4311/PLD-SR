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
//------------------------------------------------------ Personnal Include
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
	typedef enum {ACT_A1 = 0, ACT_A0 = 1, ACT_B1 = 2, ACT_B0 = 3} RockerSwitchAction;
	typedef enum { PRESSED = 0, RELEASED = 1} RockerSwitchEnergyBow;
	
	static const unsigned int FRAME_SIZE = 28;

//--------------------------------------------------------- Public Methods

	static void toFrame(enocean_data_structure* frame, char* buffer);
	static void toString(enocean_data_structure* frame, char* buffer);
	
	static SensorId getID(enocean_data_structure* frame);
	static void setID(enocean_data_structure* frame, SensorId id);

// ---- CONTACT SENSOR ----
	static string analyseContactSensor_D5_00_01(enocean_data_structure* frame);

// ---- ROCKER SWITCH ----
	static string analyseRockerSwitch_F6_02_01(enocean_data_structure* frame);

// ---- TEMP SENSOR ----
	static string analyseTempSensor(enocean_data_structure* frame, float minTemp, float maxTemp);
	static string analyseTempSensor_EEP_07_02_05(enocean_data_structure* frame);

// ---- TEMP & HUMID SENSOR ----
	static string analyseTempAndHumidSensor(enocean_data_structure* frame, float minTemp, float maxTemp);
	static string analyseTempAndHumidSensor_EEP_07_04_01(enocean_data_structure* frame);
	
// ---- LUM & OCC SENSOR ----
	static string analyseLumAndOcc_EEP_07_08_01(enocean_data_structure* frame);
	static string analyseLumAndOcc(enocean_data_structure* frame, float minLum, float maxLum, float minV, float maxV);

// ---- CO2 GAS SENSOR ----
	static string analyseCO2_EEP_07_09_01(enocean_data_structure* frame);
	static string analyseC02(enocean_data_structure* frame, float minPPM, float maxPPM);

// ---- BASIC FUNCTIONS ----
	static RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame);
	static RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame);
	static RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame);
	static bool isRockerSwitchAction2nd(enocean_data_structure* frame);

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
};

//------------------------------ Other definition, depending on this class

#endif /* SENSORS_H_ */
