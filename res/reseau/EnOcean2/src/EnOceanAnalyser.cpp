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

void* EnOceanAnalyserThread(void* periphTable) {
	EnOceanAnalyser analyz = EnOceanAnalyser((PeriphTable*)periphTable);
	
	// Run it :
	analyz.run();
	return NULL;
}//----- End of EnOceanAnalyserThread

void EnOceanAnalyser::setMessagesQueue(blocking_queue<enocean_data_structure>* mQ) {
	messagesQueue = mQ;
} //----- End of setMessagesQueue

void EnOceanAnalyser::run() {
	enocean_data_structure* frame;
	SensorId id;
	string data;
	EnOceanCallbackFunction translator;
	while (messagesQueue->front(frame, NULL) == 0) {
		id = getEnOceanID(frame);
		if ((translator = periph->find(id)) != NULL) { // If it is a sensor we use :
			data = translator(frame);
			cout << data; // TO DO : Log
		}
		free(frame);
	}
	
} //----- End of run


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanAnalyser::EnOceanAnalyser(PeriphTable* per): periph(per) {

} //----- End of EnOceanAnalyser

EnOceanAnalyser::~EnOceanAnalyser() {
	// TODO Auto-generated destructor stub
} //----- End of ~EnOceanAnalyser


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


