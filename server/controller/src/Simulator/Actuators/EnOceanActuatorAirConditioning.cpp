
/*************************************************************************
                           EnOceanActuatorAirConditioning  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanActuatorAirConditioning> (EnOceanActuatorAirConditioning.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorAirConditioning.h"
#include "../Sensors/SensorSimulatorTempHumi.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorAirConditioning::getTemperature() {
	pthread_mutex_lock(&mutex);
	float t = temperature;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanActuatorAirConditioning::setTemperature(float e) {
	pthread_mutex_lock(&mutex);
	temperature = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanActuatorAirConditioning::update() {
	pthread_mutex_lock(&mutex);
	if (on) {
		for(vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
			float t= (*it)->getTemperature();
			float coef = (temperature - t) / t;
			(*it)->setTemperature(t*(1+coef*energeticCostPerSecond/100.0));
		}
		pthread_mutex_unlock(&mutex);
		return energeticCostPerSecond;
	}
	else {
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

void EnOceanActuatorAirConditioning::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	temperature = EnOceanSensorAPI::getTemperature(frame, tempMin, tempMax);
	pthread_mutex_unlock(&mutex);

}

enocean_data_structure EnOceanActuatorAirConditioning::toFrame(int id, bool on, float temp, float tempMin, float tempMax) {
	enocean_data_structure frame;
	BYTE* byte = (BYTE*)(&frame);
	for (unsigned int i = 0; i < EnOceanSensorAPI::FRAME_SIZE/2; i++) {
		*byte = 0;
		byte += sizeof(BYTE);
	}
	EnOceanSensorAPI::setID(&frame, (EnOceanSensorAPI::SensorId)id);
	EnOceanSensorAPI::setTemperature(&frame, temp, tempMin, tempMax);
	frame.DATA_BYTE0 = on?(1<<3):(0<<3);

	return frame;
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorAirConditioning::EnOceanActuatorAirConditioning(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), temperature(t), tempMin(tMi), tempMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Air Conditioning - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanActuatorAirConditioning

EnOceanActuatorAirConditioning::~EnOceanActuatorAirConditioning() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorAirConditioning


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
