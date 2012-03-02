/*************************************************************************
                           EnOceanDefibrillator  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanDefibrillator> (EnOceanDefibrillator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanDefibrillator.h"
#include "../Model/Patient.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanDefibrillator::getPower() {
	pthread_mutex_lock(&mutex);
	float t = power;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanDefibrillator::setPower(float e) {
	pthread_mutex_lock(&mutex);
	power = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanDefibrillator::update() {
	pthread_mutex_lock(&mutex);
	float coef = 0;
	if (on) {

		for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
			Patient* patient = dynamic_cast<Patient*>((*it));
			if (patient != 0) {
				patient->setMovement(10);
				patient->setHeartRate(patient->getHeartRate() * (1+power));
			}
		}

		coef = power*20;
	}
	pthread_mutex_unlock(&mutex);
	return coef;
}

void EnOceanDefibrillator::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	float multiplyer = (float)(powerMax-powerMin) / 255.0;
	power = (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? powerMin : powerMax);
	pthread_mutex_unlock(&mutex);

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanDefibrillator::EnOceanDefibrillator(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), power(t), powerMin(tMi), powerMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Defibrillator - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanDefibrillator

EnOceanDefibrillator::~EnOceanDefibrillator() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanDefibrillator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
