
/*************************************************************************
                           Actuator  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <Actuator> (Actuator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "Actuator.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int Actuator::getID() {
	return id;
}

void Actuator::addRoom(Room* sensor) {
	pthread_mutex_lock(&mutex);
	rooms.push_back(sensor);
	pthread_mutex_unlock(&mutex);
}

void Actuator::delRoom(int id) {
	pthread_mutex_lock(&mutex);
	for (vector<Room*>::iterator it=rooms.begin() ; it < rooms.end(); it++ )
    {
		if ((*it)->getId() == id) {
			rooms.erase(it);
			return;
		}
	}
	pthread_mutex_unlock(&mutex);
}

int Actuator::countRooms() {
	return rooms.size();
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
Actuator::Actuator(int i): id(i){
	pthread_mutex_init(&mutex, NULL);
} //----- End of Actuator

Actuator::~Actuator() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
} //----- End of ~Actuator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
