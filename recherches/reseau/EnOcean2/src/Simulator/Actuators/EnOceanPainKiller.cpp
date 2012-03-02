/*************************************************************************
                           EnOceanPainKiller  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanPainKiller> (EnOceanPainKiller.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanPainKiller.h"
#include "../Model/Patient.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanPainKiller::getDebit() {
	pthread_mutex_lock(&mutex);
	float t = debit;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanPainKiller::setDebit(float e) {
	pthread_mutex_lock(&mutex);
	debit = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanPainKiller::update() {
	pthread_mutex_lock(&mutex);
	float coef = 0;
	if (on) {

		for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
			Patient* patient = dynamic_cast<Patient*>((*it));
			if (patient != 0) {
				patient->setMovement(patient->getMovement() / (1+debit));
				patient->setHeartRate(patient->getHeartRate() * (1-debit/10));
			}
		}

		coef = debit;
	}
	pthread_mutex_unlock(&mutex);
	return coef;
}

void EnOceanPainKiller::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	float multiplyer = (float)(debitMax-debitMin) / 255.0;
	debit = (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? debitMin : debitMax);
	pthread_mutex_unlock(&mutex);

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanPainKiller::EnOceanPainKiller(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), debit(t), debitMin(tMi), debitMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Pain Killer - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanPainKiller

EnOceanPainKiller::~EnOceanPainKiller() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanPainKiller


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
