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

//------------------------------------------------------ Personnal Include
#include "EnOceanProtocol.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 
typedef int32_t SensorId;
typedef enum {ACT_A1 = 0, ACT_A0 = 1, ACT_B1 = 2, ACT_B0 = 3} RockerSwitchAction;
typedef enum { PRESSED = 0, RELEASED = 1} RockerSwitchEnergyBow;

//------------------------------------------------------------------------ 
// Description : 
//
//
//------------------------------------------------------------------------ 


//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

	SensorId getEnOceanID(enocean_data_structure* frame);

// ---- ROCKER SWITCH ----
	string analyseRockerSwitch(enocean_data_structure* frame);
	
	RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame);
	RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame);
	RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame);
	bool isRockerSwitchAction2nd(enocean_data_structure* frame);

// ---- TEMP & HUMID SENSOR ----
	string analyseTempAndHumidSensor(enocean_data_structure* frame, int minTemp, int maxTemp);
	
	float getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp);
	float getHumidity(enocean_data_structure* frame);



//------------------------------ Other definition, depending on this class

#endif /* SENSORS_H_ */
