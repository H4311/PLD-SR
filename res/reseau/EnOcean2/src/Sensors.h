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

// ---- ROCKER SWITCH ----
	static string analyseRockerSwitch(enocean_data_structure* frame);
	
	static RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame);
	static RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame);
	static RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame);
	static bool isRockerSwitchAction2nd(enocean_data_structure* frame);

// ---- TEMP & HUMID SENSOR ----
	static string analyseTempAndHumidSensor(enocean_data_structure* frame, int minTemp, int maxTemp);
	
	static float getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp);
	static float getHumidity(enocean_data_structure* frame);
	static void setTemperature(enocean_data_structure* frame, float temp, int minTemp, int maxTemp);
	static void setHumidity(enocean_data_structure* frame, float humi);
};

//------------------------------ Other definition, depending on this class

#endif /* SENSORS_H_ */
