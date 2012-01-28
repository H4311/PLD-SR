/*************************************************************************
                           EnOceanAnalyser  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanAnalyser> (EnOceanAnalyser.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdio.h>
#include <iostream>

//------------------------------------------------------ Personnal Include
#include "EnOceanAnalyser.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanAnalyserThread (void* param) {
	EnOceanAnalyser* analyz = (EnOceanAnalyser*)param;
	analyz->analyse();
	return NULL;
}//----- End of EnOceanAnalyserThread

void EnOceanAnalyser::setMessagesQueue(EnOceanMsgQueue* mQ) {
	messagesQueue = mQ;
} //----- End of setMessagesQueue

void EnOceanAnalyser::analyse() {
	pair<enocean_data_structure*, long*>* data;
	enocean_data_structure* frame;
	long* timestamp;
	EnOceanSensorAPI::SensorId id;
	string dataS;
	EnOceanCallbackFunction translator;
	cout << "<Analyser> Ready.\n";
	while ((flag == true) && (messagesQueue->front(data, NULL)) == 0) {
		cout << "<Analyser> Frame Received.\n";
		frame = data->first;
		timestamp = data->second;
		id = EnOceanSensorAPI::getID(frame);
		cout << "<Analyser> ID : " << id << endl;
		if ((translator = periph->find(id)) != NULL) { // If it is a sensor we use :
			cout << "<Analyser> Sensor identified.\n";
			dataS = translator(frame);
			cout << "<Analyser> Extraction : " << dataS << " | Time : " << *timestamp << "s.\n"; // TO DO : Log
		}
		cout << "<Analyser> Frame processed.\n";
		messagesQueue->pop();
	}
	
} //----- End of analyse


bool EnOceanAnalyser::getFlag() {
	bool f;
	pthread_mutex_lock(&mutex);
	f = flag;
	pthread_mutex_unlock(&mutex);
	return f;
} //----- End of getFlag

void EnOceanAnalyser::run() {
	pthread_mutex_lock(&mutex);
	flag = true;
	pthread_mutex_unlock(&mutex);
	pthread_create(&thread, NULL, EnOceanAnalyserThread, this);
} //----- End of run

void EnOceanAnalyser::stop() {
	pthread_mutex_lock(&mutex);
	flag = false;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread, NULL);
} //----- End of stop

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanAnalyser::EnOceanAnalyser(DeviceTable* per, EnOceanMsgQueue* m): periph(per), messagesQueue(m), flag(false) {
	pthread_mutex_init(&mutex, NULL);
} //----- End of EnOceanAnalyser

EnOceanAnalyser::~EnOceanAnalyser() {
	stop();
	pthread_mutex_destroy(&mutex);
	// TODO Auto-generated destructor stub
} //----- End of ~EnOceanAnalyser


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


