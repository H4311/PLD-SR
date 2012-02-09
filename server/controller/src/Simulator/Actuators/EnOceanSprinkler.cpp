/*************************************************************************
                           EnOceanSprinkler  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanSprinkler> (EnOceanSprinkler.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanSprinkler.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

EventActuatorFire* EnOceanSprinkler::getFire() {
	pthread_mutex_lock(&mutex);
	EventActuatorFire* t = fire;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanSprinkler::setFire(EventActuatorFire* e) {
	pthread_mutex_lock(&mutex);
	fire = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanSprinkler::getDebit() {
	pthread_mutex_lock(&mutex);
	float t = debit;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanSprinkler::setDebit(float e) {
	pthread_mutex_lock(&mutex);
	debit = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanSprinkler::update() {
	pthread_mutex_lock(&mutex);
	float coef = 0;
	if (on && (fire != NULL)) {

		// Fighting the fire :
		fire->setPower(fire->getPower() / debit);
		coef = debit;

		// Increasing the humidity :
		for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
			Room* room = dynamic_cast<Room*>((*it));
			if (room != 0) {
				room->setCO2Level(room->getHumidity()*(1+debit));
			}
		}
	}
	pthread_mutex_unlock(&mutex);
	return coef;
}

void EnOceanSprinkler::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	float multiplyer = (float)(debitMax-debitMin) / 255.0;
	debit = (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? debitMin : debitMax);
	pthread_mutex_unlock(&mutex);

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanSprinkler::EnOceanSprinkler(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), debit(t), debitMin(tMi), debitMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Sprinkler - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanSprinkler

EnOceanSprinkler::~EnOceanSprinkler() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanSprinkler


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
