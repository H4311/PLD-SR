
/*************************************************************************
                           EnOCeanBaseSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOCeanBaseSimulator> (EnOCeanBaseSimulator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include

#include <unistd.h>
#include <iostream>
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EnOCeanBaseSimulator.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanBaseSimulatorThread_Send (void* param) {
	int delayBetween2Sendings;
	char frame[EnOceanSensorAPI::FRAME_SIZE];
	EnOCeanBaseSimulator* simu = (EnOCeanBaseSimulator*)param;

	// Wait for client :
	simu->acceptClient();

	// Sends data from each sensor, sleeping between two sending :
	while(simu->getFlag() == 0) {

		// Updating the sensors :
		simu->updateSensors();

		// Sending their values :
		int nbS = simu->countSensors();
		delayBetween2Sendings = (nbS != 0)?((simu->DELAY*1000000) / nbS):0;
		delayBetween2Sendings = (delayBetween2Sendings < 100)? 100 : delayBetween2Sendings;
		
		for (int i = 0; i < simu->countSensors(); i++) {
			if (simu->getFlag() != 0) { break; }
			simu->getFrame(i, frame);
			cout << "<Simulator> " << frame << " | " << delayBetween2Sendings/1000 << endl;
			simu->writeClient(frame, EnOceanSensorAPI::FRAME_SIZE);
			usleep(delayBetween2Sendings);
		}
	}
	
	simu->closeClient();
	
	return NULL;
}//----- End of EnOceanBaseSimulatorThread_Send

void* EnOceanBaseSimulatorThread_Receive (void* param) {
	int n, id;
	char buffer[EnOceanSensorAPI::FRAME_SIZE];
	EnOCeanBaseSimulator* simu = (EnOCeanBaseSimulator*)param;

	// Wait for client :
	simu->acceptClient();

	// Sends data from each sensor, sleeping between two sending :
	while(simu->getFlag() == 0) {

		// Waiting for data to be read :
		simu->server.waitData();

		if((n = simu->readClient(buffer, EnOceanSensorAPI::FRAME_SIZE)) < 0)
		{
			cout << "<Simu Receptor> Error - Read | " << n << endl;
			break;
		}

		cout << "<Simu Receptor> Frame Received - " << buffer << ".\n";
		enocean_data_structure frame;
		EnOceanSensorAPI::toFrame(&frame, buffer);
		id = EnOceanSensorAPI::getID(&frame);
		pthread_mutex_lock(&(simu->mutex));
		for (vector<Actuator*>::const_iterator it=simu->actuators.begin() ; it < simu->actuators.end(); it++ )
		{
			EnOceanActuator* act = dynamic_cast<EnOceanActuator*>((*it));

			if ((act != 0) && (act->getID() == id)) {
				act->set(&frame);
				cout << "<Simu Receptor> Actuator updated.\n";
				break;
			}
		}
		pthread_mutex_unlock(&(simu->mutex));
	}

	simu->closeClient();

	return NULL;
}//----- End of EnOceanBaseSimulatorThread_Send

void EnOCeanBaseSimulator::addSensor(SensorSimulator* sensor) {
	pthread_mutex_lock(&mutex);
	sensors.push_back(sensor);
	pthread_mutex_unlock(&mutex);
}

bool EnOCeanBaseSimulator::delSensor(EnOceanSensorAPI::SensorId id) {
	pthread_mutex_lock(&mutex);

	for (vector<SensorSimulator*>::iterator it=sensors.begin() ; it < sensors.end(); it++ )
    {
		if ((*it)->getId() == (EnOceanSensorAPI::SensorId)id) {
			sensors.erase(it);
			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	pthread_mutex_unlock(&mutex);
	return false;
}

int EnOCeanBaseSimulator::countSensors() {
	int ret;
	pthread_mutex_lock(&mutex);
	ret = sensors.size();
	pthread_mutex_unlock(&mutex);
	return ret;
}

void EnOCeanBaseSimulator::addActuator(Actuator* a) {
	pthread_mutex_lock(&mutex);
	actuators.push_back(a);
	pthread_mutex_unlock(&mutex);
}

bool EnOCeanBaseSimulator::delActuator(int id) {
	pthread_mutex_lock(&mutex);

	for (vector<Actuator*>::iterator it=actuators.begin() ; it < actuators.end(); it++ )
    {
		if ((*it)->getID() == id) {
			actuators.erase(it);
			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	pthread_mutex_unlock(&mutex);
	return false;
}

int EnOCeanBaseSimulator::countActuators() {
	int ret;
	pthread_mutex_lock(&mutex);
	ret = actuators.size();
	pthread_mutex_unlock(&mutex);
	return ret;
}

void EnOCeanBaseSimulator::addSubject(Subject* r) {
	pthread_mutex_lock(&mutex);
	subjects.push_back(r);
	pthread_mutex_unlock(&mutex);
}

bool EnOCeanBaseSimulator::delSubject(int id) {
	pthread_mutex_lock(&mutex);

	for (vector<Subject*>::iterator it=subjects.begin() ; it < subjects.end(); it++ )
    {
		if ((*it)->getId() == id) {
			subjects.erase(it);
			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	pthread_mutex_unlock(&mutex);
	return false;
}

int EnOCeanBaseSimulator::countSubjects() {
	int ret;
	pthread_mutex_lock(&mutex);
	ret = subjects.size();
	pthread_mutex_unlock(&mutex);
	return ret;
}

Subject* EnOCeanBaseSimulator::findSubject(int id) {
	Subject* r = NULL;
	pthread_mutex_lock(&mutex);
	for (vector<Subject*>::iterator it=subjects.begin() ; it < subjects.end(); it++ )
	{
		if ((*it)->getId() == id) {
			r = (*it);
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
	return r;
}

float EnOCeanBaseSimulator::updateSensors() {
	float conso = 0;
	pthread_mutex_lock(&mutex);
	for (vector<Actuator*>::iterator it=actuators.begin() ; it < actuators.end(); it++ )
	    {
			conso = (*it)->update();
		}
	pthread_mutex_unlock(&mutex);
	return conso;
}


int EnOCeanBaseSimulator::openSocket(int port) {
	return server.openSocket(port);
}

int EnOCeanBaseSimulator::acceptClient() {
	return server.acceptClient();
}

int EnOCeanBaseSimulator::closeClient() {
	return server.closeClient();
	
}
int EnOCeanBaseSimulator::closeSocket() {
	return server.closeSocket();
}

int EnOCeanBaseSimulator::writeClient(char* msg, int length) {
	return server.writeClient(msg, length);
}

int EnOCeanBaseSimulator::readClient(char* msg, int length) {
	return server.readClient(msg, length);
}

 void EnOCeanBaseSimulator::getFrame(int posSensor, char* frame) {
	pthread_mutex_lock(&mutex);
	sensors[posSensor]->getFrame(frame);
	pthread_mutex_unlock(&mutex);	
}

int EnOCeanBaseSimulator::getFlag() {
	int f;
	pthread_mutex_lock(&mutex);
	f = flag;
	pthread_mutex_unlock(&mutex);
	return f;
}

void EnOCeanBaseSimulator::run() {
	pthread_mutex_lock(&mutex);
	flag = 0;
	pthread_mutex_unlock(&mutex);
	pthread_create(&thread_Send, NULL, EnOceanBaseSimulatorThread_Send, this);
	pthread_create(&thread_Receive, NULL, EnOceanBaseSimulatorThread_Receive, this);
}

void EnOCeanBaseSimulator::stop() {
	pthread_mutex_lock(&mutex);
	flag = 1;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread_Send, NULL);
	pthread_join(thread_Receive, NULL);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOCeanBaseSimulator::EnOCeanBaseSimulator(){
	pthread_mutex_init(&mutex, NULL);
	flag = 0;
} //----- End of EnOCeanBaseSimulator

EnOCeanBaseSimulator::~EnOCeanBaseSimulator() {
	// TODO Auto-generated destructor stub
	stop();
	pthread_mutex_destroy(&mutex);
} //----- End of ~EnOCeanBaseSimulator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
