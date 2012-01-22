
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
//------------------------------------------------------ Personnal Include
#include "EnOCeanBaseSimulator.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanBaseSimulatorThread (void* param) {
	int delayBetween2Sendings;
	char[28] frame;
	EnOceanBaseSimulator* simu = (EnOceanBaseSimulator*)simu;
	// Sends data from each sensor, sleeping between two sending :
	while(simu->getFlag() == 0) {
		delayBetween2Sendings = (simu.DELAY*1000) / simu->countSensors();
		delayBetween2Sendings (delayBetween2Sendings > 100)? 100 : delayBetween2Sendings;
		
		for (int i = 0; i < simu->countSensors(); i++) {
			simu->getFrame(i, frame);
			simu->writeClient(frame, 28);
			usleep(delayBetween2Sendings);
		}
	}
	
	
	return NULL;
}//----- End of EnOceanBaseSimulatorThread

int EnOCeanBaseSimulator::addSensor(SensorSimulator* sensor) {
	int ret;
	pthread_mutex_lock(&mutex);
	ret = sensors.push_back(sensor);
	pthread_mutex_unlock(&mutex);
	return ret;
}

void EnOCeanBaseSimulator::delSensor(SensorId id) {
	pthread_mutex_lock(&mutex);
	vector<SensorSimulator*>::iterator it;
	for ( it=sensors.begin() ; it < sensors.end(); it++ )
    {
		if (it->getId() == id) {
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
	server.openSocket(port);
}

int EnOCeanBaseSimulator::acceptClient() {
	server.acceptClient();
}

int EnOCeanBaseSimulator::closeClient() {
	server.closeClient();
	
}
int EnOCeanBaseSimulator::closeSocket() {
	server.closeSocket();
}

int EnOCeanBaseSimulator::writeClient(char* msg, int length) {
	return server.writeClient(msg, length);
}

 void EnOCeanBaseSimulator::getFrame(int posSensor, char* frame) {
	pthread_mutex_lock(&mutex);
	sensors[posSensor].getString(frame);
	pthread_mutex_unlock(&mutex);	
}

int getFlag() {
	int f;
	pthread_mutex_lock(&mutex);
	f = flag;
	pthread_mutex_unlock(&mutex);
	return f;
}

void run() {
	pthread_mutex_lock(&mutex);
	flag = 0;
	pthread_mutex_unlock(&mutex);
	pthread_create(&thread, NULL, EnOceanBaseSimulatorThread, &this);
}

void stop() {
	pthread_mutex_lock(&mutex);
	flag = 1;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread, NULL);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOCeanBaseSimulator::EnOCeanBaseSimulator(){
	pthread_mutex_init(&mutex);
	flag = 0;
} //----- End of EnOCeanBaseSimulator

EnOCeanBaseSimulator::~EnOCeanBaseSimulator() {
	// TODO Auto-generated destructor stub
	stop();
	pthread_mutex_destroy(&mutex);
} //----- End of ~EnOCeanBaseSimulator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
