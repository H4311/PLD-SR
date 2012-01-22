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
#include "Sensors.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanAnalyserThread(void* param) {

	Analyser_thread_param* p = (Analyser_thread_param*)param;

	EnOceanAnalyser analyz = EnOceanAnalyser(p->periph, p->messagesQueue);
	cout << "<Analyser> Created.\n";
	// Run it :
	analyz.run();
	return NULL;
}//----- End of EnOceanAnalyserThread

int runAnalyser (pthread_t *thread, void* param)
{
	cout << "<Analyser> Creating.\n";
	return pthread_create(thread, NULL, EnOceanAnalyserThread, param);

}


void EnOceanAnalyser::setMessagesQueue(EnOceanMsgQueue* mQ) {
	messagesQueue = mQ;
} //----- End of setMessagesQueue

void EnOceanAnalyser::run() {
	enocean_data_structure* frame;
	SensorId id;
	string data;
	EnOceanCallbackFunction translator;
	cout << "<Analyser> Ready.\n";
	while (messagesQueue->front(frame, NULL) == 0) {
		cout << "<Analyser> Frame Received.\n";
		id = getEnOceanID(frame);
		cout << "<Analyser> ID :" << id << endl;
		if ((translator = periph->find(id)) != NULL) { // If it is a sensor we use :
			cout << "<Analyser> Sensor identified.\n";
			data = translator(frame);
			cout << data; // TO DO : Log
		}
		cout << "<Analyser> Frame processed.\n";
		messagesQueue->pop();
	}
	
} //----- End of run


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanAnalyser::EnOceanAnalyser(PeriphTable* per, EnOceanMsgQueue* m): periph(per), messagesQueue(m) {

} //----- End of EnOceanAnalyser

EnOceanAnalyser::~EnOceanAnalyser() {
	// TODO Auto-generated destructor stub
} //----- End of ~EnOceanAnalyser


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


