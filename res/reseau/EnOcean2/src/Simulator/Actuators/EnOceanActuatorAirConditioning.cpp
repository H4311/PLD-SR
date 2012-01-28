
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
		for(vector<SensorSimulator*>::iterator it = sensors.begin(); it != sensors.end(); ++it) {
			SensorSimulatorTempHumi* s = (SensorSimulatorTempHumi*)*it;
			float coef = (temperature - s->getTemperature()) / s->getTemperature();
			s->setTemperature(s->getTemperature()*(1+coef*energeticCostPerSecond/100.0));
		}
		pthread_mutex_unlock(&mutex);
		return energeticCostPerSecond;
	}
	else {
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorAirConditioning::EnOceanActuatorAirConditioning(int i, float e, float t): EnOceanActuator(i,e), temperature(t){

} //----- End of EnOceanActuatorAirConditioning

EnOceanActuatorAirConditioning::~EnOceanActuatorAirConditioning() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorAirConditioning


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
