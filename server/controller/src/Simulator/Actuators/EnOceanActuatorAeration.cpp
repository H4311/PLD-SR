/*************************************************************************
                           EnOceanActuatorAeration  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanActuatorAeration> (EnOceanActuatorAeration.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorAeration.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorAeration::getPower() {
	pthread_mutex_lock(&mutex);
	float t = co2ppm;
	pthread_mutex_unlock(&mutex);
	return t;
}

void EnOceanActuatorAeration::setPower(float e) {
	pthread_mutex_lock(&mutex);
	co2ppm = e;
	pthread_mutex_unlock(&mutex);
}

float EnOceanActuatorAeration::update() {
	pthread_mutex_lock(&mutex);
	float coef = co2ppm*energeticCostPerSecond;
	if (on) {
		for(vector<Subject*>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
			Room* room = dynamic_cast<Room*>((*it));
			if (room != 0) {
				float t= room->getCO2Level();
				float coef = (co2ppm - t) / t;
				room->setCO2Level(t*(1+coef*energeticCostPerSecond/100.0));
			}
		}
		pthread_mutex_unlock(&mutex);
		return coef;
	}
	else {
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

void EnOceanActuatorAeration::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	float multiplyer = (float)(ppmMax-ppmMin) / 255.0;
	co2ppm = (float)frame->DATA_BYTE3 * multiplyer + (float)( (multiplyer>=0)? ppmMin : ppmMax);
	pthread_mutex_unlock(&mutex);

}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorAeration::EnOceanActuatorAeration(int i, float e, float t, float tMi, float tMa): EnOceanActuator(i,e), co2ppm(t), ppmMin(tMi), ppmMax(tMa){
	cout << "<Actuator Simu n°" << id << "> Aeration - Created - " << "[" << tMi << "; " << tMa << "]\n";
} //----- End of EnOceanActuatorAeration

EnOceanActuatorAeration::~EnOceanActuatorAeration() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorAeration


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
