/*************************************************************************
                           EnOceanActuatorLight  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanActuatorLight> (EnOceanActuatorLight.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorLight.h"
#include "../Sensors/SensorSimulatorLumAndOcc.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorLight::getIlluminance() {
	pthread_mutex_lock(&mutex);
	float t = illuminance;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanActuatorLight::setIlluminance(float e) {
	pthread_mutex_lock(&mutex);
	illuminance = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanActuatorLight::update() {
	time_t rawtime;
	time ( &rawtime );
	struct tm *tm_struct = localtime(&rawtime);
	int hour = tm_struct->tm_hour%24;
	float naturalLight;
	if ((hour >= 22) && (hour <= 5)) {
		naturalLight = 3; // Night in a city
	}
	else if (hour < 13) {
		naturalLight = 4000*(hour-5); // ~35000lx for midday
	}
	else {
		naturalLight = 3800*(22-hour);
	}

	pthread_mutex_lock(&mutex);
	for(vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
		(*it)->setLuminosity(naturalLight+(on?illuminance:0));
	}
	pthread_mutex_unlock(&mutex);
	return energeticCostPerSecond*illuminance*(luxMax-luxMin);
}

void EnOceanActuatorLight::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	illuminance = EnOceanSensorAPI::getIlluminance(frame, luxMin, luxMax);
	pthread_mutex_unlock(&mutex);

}

enocean_data_structure EnOceanActuatorLight::toFrame(int id, bool on, float val, float minL, float maxL) {
	enocean_data_structure frame;
	BYTE* byte = (BYTE*)(&frame);
	for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
		*byte = 0;
		byte += sizeof(BYTE);
	}
	EnOceanSensorAPI::setID(&frame, (EnOceanSensorAPI::SensorId)id);
	EnOceanSensorAPI::setIlluminance(&frame, val, minL, maxL);
	frame.DATA_BYTE0 = on?(1<<3):(0<<3);

	return frame;
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorLight::EnOceanActuatorLight(int i, float e, float v, float lMi, float lMa): EnOceanActuator(i,e), illuminance(v), luxMin(lMi), luxMax(lMa){
	cout << "<Actuator Simu n°" << id << "> Light - Created - " << "[" << lMi << "; " << lMa << "]\n";
} //----- End of EnOceanActuatorLight

EnOceanActuatorLight::~EnOceanActuatorLight() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorLight


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
