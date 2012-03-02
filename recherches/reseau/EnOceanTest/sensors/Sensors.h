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
#include "EnOceanProtocol.h'

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 
typedef SensorId int32_t;
enum RockerSwitchAction { A1, A0, B1, B0 };
enum RockerSwitchEnergyBow { pressed, released };
};

//------------------------------------------------------------------------ 
// Description : 
//
//
//------------------------------------------------------------------------ 


//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

	SensorId getEnOceanID(enocean_data_structure* frame);

// ---- ROCKER SWITCH ----
	RockerSwitchAction getRockerSwitchAction1st(enocean_data_structure* frame);
	RockerSwitchEnergyBow getRockerSwitchEnergyBow(enocean_data_structure* frame);
	RockerSwitchAction getRockerSwitchAction2nd(enocean_data_structure* frame);
	bool isRockerSwitchAction2nd(enocean_data_structure* frame);

// ---- TEMP & HUMID SENSOR ----
	float getTemperature(enocean_data_structure* frame, int minTemp, int maxTemp);
	float getHumidity(enocean_data_structure* frame);



//------------------------------ Other definition, depending on this class

#endif /* SENSORS_H_ */
