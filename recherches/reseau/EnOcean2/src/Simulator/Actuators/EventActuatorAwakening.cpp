/*************************************************************************
                           EventActuatorAwakening  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EventActuatorAwakening> (EventActuatorAwakening.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EventActuatorAwakening.h"
#include <iostream>
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EventActuatorAwakening::getPower() {
	pthread_mutex_lock(&mutex);
	float t = power;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EventActuatorAwakening::setPower(float e) {
	pthread_mutex_lock(&mutex);
	power = e;
	pthread_mutex_unlock(&mutex);
}

float EventActuatorAwakening::update() {
	pthread_mutex_lock(&mutex);
	float temp;
	for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
		Patient* patient = dynamic_cast<Patient*>((*it));
		if (patient != 0) {

			temp = patient->getHeartRate();
			patient->setHeartRate(temp + (70 - temp) * power / 10);
			temp = patient->getMovement();
			patient->setMovement(temp + (3 - temp) * power / 10);
		}

	}
	pthread_mutex_unlock(&mutex);
	return 0;

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EventActuatorAwakening::EventActuatorAwakening(int i, float p): Actuator(i), power(p){
	cout << "<Actuator Simu n°" << id << "> Awakening - Created - " << p << "]\n";
} //----- End of EventActuatorAwakening

EventActuatorAwakening::~EventActuatorAwakening() {
	// TODO Auto-generated destructor stub

} //----- End of ~EventActuatorAwakening


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
