
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

#include "EnOceanActuatorAeration.h"
#include "EnOceanActuatorAirConditioning.h"
#include "EnOceanActuatorLight.h"
#include "EventActuatorFire.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

Actuator* Actuator::createActuator(int id, int type) {
	switch (type) {
	// Switch :
	case 0x1050201 : { return NULL;}

	// Air Cond :
	case 0x1070201 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -40.0, 0.0);}
	case 0x1070202 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -30.0, 10.0);}
	case 0x1070203 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -20.0, 20.0);}
	case 0x1070204 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -10.0, 30.0);}
	case 0x1070205 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 0.0, 40.0);}
	case 0x1070206 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 10.0, 50.0);}
	case 0x1070207 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 20.0, 60.0);}
	case 0x1070208 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 30.0, 70.0);}
	case 0x1070209 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 40.0, 80.0);}
	case 0x107020A : { return new EnOceanActuatorAirConditioning(id, 0, 0, 50.0, 90.0);}
	case 0x107020B : { return new EnOceanActuatorAirConditioning(id, 0, 0, 60.0, 100.0);}
	case 0x1070210 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -60.0, 20.0);}
	case 0x1070211 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -50.0, 30.0);}
	case 0x1070212 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -40.0, 40.0);}
	case 0x1070213 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -30.0, 50.0);}
	case 0x1070214 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -20.0, 60.0);}
	case 0x1070215 : { return new EnOceanActuatorAirConditioning(id, 0, 0, -10.0, 70.0);}
	case 0x1070216 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 0.0, 80.0);}
	case 0x1070217 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 10.0, 90.0);}
	case 0x1070218 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 20.0, 100.0);}
	case 0x1070219 : { return new EnOceanActuatorAirConditioning(id, 0, 0, 30.0, 110.0);}
	case 0x107021A : { return new EnOceanActuatorAirConditioning(id, 0, 0, 40.0, 120.0);}
	case 0x107021B : { return new EnOceanActuatorAirConditioning(id, 0, 0, 50.0, 130.0);}

	// Light :
	case 0x1070601 : { return new EnOceanActuatorLight(id, 0, 0, 300.0, 60000.0);}
	case 0x1070602 : { return new EnOceanActuatorLight(id, 0, 0, 0.0, 1024.0);}

	// Aeration :
	case 0x1070901 : { return new EnOceanActuatorAeration(id, 0, 0, 200.0, 1000.0);}

	// Fire :
	case 0x2000001 : { return new EventActuatorFire(id, 1.5);}
	}

	return NULL;
}

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
