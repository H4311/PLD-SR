
/*************************************************************************
                           EnOCeanBaseSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOCeanBaseSimulator> (EnOCeanBaseSimulator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <unistd.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "EnOCeanBaseSimulator.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanBaseSimulatorThread (void* param) {
	int delayBetween2Sendings;
	char frame[EnOceanSensorAPI::FRAME_SIZE];
	EnOCeanBaseSimulator* simu = (EnOCeanBaseSimulator*)param;

	// Wait for client :
	simu->acceptClient();

	// Sends data from each sensor, sleeping between two sending :
	while(simu->getFlag() == 0) {
		delayBetween2Sendings = (simu->DELAY*1000000) / simu->countSensors();
		delayBetween2Sendings = (delayBetween2Sendings < 100)? 100 : delayBetween2Sendings;
		
		for (int i = 0; i < simu->countSensors(); i++) {
			if (simu->getFlag() != 0) { break; }
			simu->getFrame(i, frame);
			cout << "<Simulator> " << frame << "|\r | " << delayBetween2Sendings << endl;
			simu->writeClient(frame, 28);
			usleep(delayBetween2Sendings);
		}
	}
	
	simu->closeClient();
	
	return NULL;
}//----- End of EnOceanBaseSimulatorThread

void EnOCeanBaseSimulator::addSensor(SensorSimulator* sensor) {
	pthread_mutex_lock(&mutex);
	sensors.push_back(sensor);
	pthread_mutex_unlock(&mutex);
}

void EnOCeanBaseSimulator::delSensor(EnOceanSensorAPI::SensorId id) {
	pthread_mutex_lock(&mutex);

	for (vector<SensorSimulator*>::iterator it=sensors.begin() ; it < sensors.end(); it++ )
    {
		if ((*it)->getId() == (EnOceanSensorAPI::SensorId)id) {
			sensors.erase(it);
			return;
		}
	}
	pthread_mutex_unlock(&mutex);
}

int EnOCeanBaseSimulator::countSensors() {
	int ret;
	pthread_mutex_lock(&mutex);
	ret = sensors.size();
	pthread_mutex_unlock(&mutex);
	return ret;
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
	pthread_create(&thread, NULL, EnOceanBaseSimulatorThread, this);
}

void EnOCeanBaseSimulator::stop() {
	pthread_mutex_lock(&mutex);
	flag = 1;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread, NULL);
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
