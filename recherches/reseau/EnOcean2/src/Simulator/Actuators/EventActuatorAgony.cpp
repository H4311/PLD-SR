/*************************************************************************
                           EventActuatorAgony  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EventActuatorAgony> (EventActuatorAgony.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EventActuatorAgony.h"
#include <iostream>
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EventActuatorAgony::getPower() {
	pthread_mutex_lock(&mutex);
	float t = power;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EventActuatorAgony::setPower(float e) {
	pthread_mutex_lock(&mutex);
	power = e;
	pthread_mutex_unlock(&mutex);
}

float EventActuatorAgony::update() {
	pthread_mutex_lock(&mutex);
	float temp;
	for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
		Patient* patient = dynamic_cast<Patient*>((*it));
		if (patient != 0) {

			temp = patient->getHeartRate();
			temp = temp + (0 - temp) * power / 10;

			if (temp <= 5) { // Dead
				patient->setHeartRate(0);
				patient->setMovement(0);
				patient->setStatus(false);
				subjects.erase(it);
			}
			else {
				patient->setHeartRate(temp);
				temp = patient->getMovement();
				patient->setMovement(temp + (0 - temp) * power / 10);
			}

		}

	}
	pthread_mutex_unlock(&mutex);
	return 0;

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EventActuatorAgony::EventActuatorAgony(int i, float p): Actuator(i), power(p){
	cout << "<Actuator Simu n°" << id << "> Awakening - Created - " << p << "]\n";
} //----- End of EventActuatorAgony

EventActuatorAgony::~EventActuatorAgony() {
	// TODO Auto-generated destructor stub

} //----- End of ~EventActuatorAgony


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
