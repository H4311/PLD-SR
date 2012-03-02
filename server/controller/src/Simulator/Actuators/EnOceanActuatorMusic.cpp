/*************************************************************************
                           EnOceanActuatorMusic  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Thibaut PATEL (TPL)
*************************************************************************/

//---- Implementation - <EnOceanActuatorMusic> (EnOceanActuatorMusic.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorMusic.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorMusic::getPower() {
	return 0;
}

void EnOceanActuatorMusic::setPower(float e) {
}

float EnOceanActuatorMusic::update() {
	pthread_mutex_lock(&mutex);
	if (on) {
		system("");
		pthread_mutex_unlock(&mutex);
		return coef;
	}
	else {
		system("");
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

void EnOceanActuatorMusic::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	pthread_mutex_unlock(&mutex);

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorMusic::EnOceanActuatorMusic(int i, float e): EnOceanActuator(i,e){
	cout << "<Actuator Simu n°" << id << "> Music - Created\n";
} //----- End of EnOceanActuatorMusic

EnOceanActuatorMusic::~EnOceanActuatorMusic() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorMusic


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
