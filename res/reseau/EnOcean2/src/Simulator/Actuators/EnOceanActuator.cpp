
/*************************************************************************
                           EnOceanActuator  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanActuator> (EnOceanActuator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

bool EnOceanActuator::getStatus() {
	pthread_mutex_lock(&mutex);
	bool s = on;
	pthread_mutex_unlock(&mutex);
	return s;
}

void EnOceanActuator::setStatus(bool s) {
	pthread_mutex_lock(&mutex);
	on = s;
	pthread_mutex_unlock(&mutex);
}

float EnOceanActuator::getEnergeticCostPerSecond() {
	pthread_mutex_lock(&mutex);
	float s = energeticCostPerSecond;
	pthread_mutex_unlock(&mutex);
	return s;
}

void EnOceanActuator::setEnergeticCostPerSecond(float e) {
	pthread_mutex_lock(&mutex);
	energeticCostPerSecond = e;
	pthread_mutex_unlock(&mutex);
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuator::EnOceanActuator(int i, float e): Actuator(i), energeticCostPerSecond(e), on(false){

} //----- End of EnOceanActuator

EnOceanActuator::~EnOceanActuator() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
