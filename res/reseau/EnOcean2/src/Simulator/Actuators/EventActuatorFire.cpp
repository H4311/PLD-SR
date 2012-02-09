/*************************************************************************
                           EventActuatorFire  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EventActuatorFire> (EventActuatorFire.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EventActuatorFire.h"
#include <iostream>
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EventActuatorFire::getPower() {
	pthread_mutex_lock(&mutex);
	float t = power;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EventActuatorFire::setPower(float e) {
	pthread_mutex_lock(&mutex);
	power = e;
	pthread_mutex_unlock(&mutex);
}

float EventActuatorFire::update() {
	pthread_mutex_lock(&mutex);
	float temp, temp2;
	vector<Room*> neigthborsTakingFire;
	for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
		temp = (*it)->getTemperature();
		temp2 = temp*power;

		Room* room = dynamic_cast<Room*>((*it));
		if (room != 0) {
			room->setHumidity(room->getHumidity()/power);
			if (temp2>5000) {
				room->setTemperature(5000);
				room->setCO2Level(4000);
			}
			else if ((temp2 < 25) && (room->getHumidity() < 10)) {
				room->setTemperature(25);
				cout << "<Actuator Simu n°" << id << "> Fire - Room n°" << room->getId() << " stabilized !\n";
				subjects.erase(it);
			}
			else {
				room->setTemperature(temp2);
				room->setCO2Level(room->getCO2Level()*power);
			}

			if ((temp<400) && (temp2>470)) { // Neightbors take fire
				vector<Room*> neigthbors = room->getNeigthborRooms();
				neigthborsTakingFire.insert( neigthborsTakingFire.end(), neigthbors.begin(), neigthbors.end() );
				cout << "<Actuator Simu n°" << id << "> Fire - " << neigthbors.size() << " other rooms took fire !\n";
			}
		}

	}
	subjects.insert( subjects.end(), neigthborsTakingFire.begin(), neigthborsTakingFire.end() );
	power *= 1.2;
	pthread_mutex_unlock(&mutex);
	return 0;

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EventActuatorFire::EventActuatorFire(int i, float p): Actuator(i), power(p){
	cout << "<Actuator Simu n°" << id << "> Fire - Created - " << p << "]\n";
} //----- End of EventActuatorFire

EventActuatorFire::~EventActuatorFire() {
	// TODO Auto-generated destructor stub

} //----- End of ~EventActuatorFire


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
