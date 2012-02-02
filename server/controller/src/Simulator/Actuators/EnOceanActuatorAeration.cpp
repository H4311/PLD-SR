/*************************************************************************
                           EnOceanActuatorAeration  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanActuatorAeration> (EnOceanActuatorAeration.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorAeration.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorAeration::getPower() {
	pthread_mutex_lock(&mutex);
	float t = power;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanActuatorAeration::setPower(float e) {
	pthread_mutex_lock(&mutex);
	power = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanActuatorAeration::update() {
	pthread_mutex_lock(&mutex);
	float coef = power*energeticCostPerSecond;
	if (on) {
		for(vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
			(*it)->setCO2Level((*it)->getCO2Level()*(1-coef/100.0));
		}
		pthread_mutex_unlock(&mutex);
		return coef;
	}
	else {
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

void EnOceanActuatorAeration::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	float multiplyer = (float)(powerMax-powerMin) / 255.0;
	power = (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? powerMin : powerMax);
	pthread_mutex_unlock(&mutex);

}

enocean_data_structure EnOceanActuatorAeration::toFrame(int id, bool on, float val, float valMin, float valMax) {
	enocean_data_structure frame;
	BYTE* byte = (BYTE*)(&frame);
	for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
		*byte = 0;
		byte += sizeof(BYTE);
	}
	EnOceanSensorAPI::setID(&frame, (EnOceanSensorAPI::SensorId)id);
	float multiplyer = (float)(valMax-valMin) / 255.0;
	frame.DATA_BYTE3 = (BYTE)((val - (float)( (multiplyer>=0)? valMin : valMax )) / multiplyer);
	frame.DATA_BYTE0 = on?(1<<3):(0<<3);

	return frame;
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorAeration::EnOceanActuatorAeration(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), power(t), powerMin(tMi), powerMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Aeration - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanActuatorAeration

EnOceanActuatorAeration::~EnOceanActuatorAeration() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorAeration


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
