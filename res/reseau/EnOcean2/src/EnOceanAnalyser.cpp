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

//------------------------------------------------------ Personnal Include
#include "EnOceanAnalyser.h"
#include "Sensors.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* EnOceanAnalyserThread(void* sensorsInfo) {
	EnOceanAnalyser analyz = EnOceanAnalyser();
	
	// Sets the analyst :
	map<SensorId, EnOceanCallbackFunction>* sensors = (map<SensorId, EnOceanCallbackFunction>*)sensorsInfo;
	for ( map<SensorId, EnOceanCallbackFunction>::iterator iter = sensors->begin(); iter != sensors->end(); ++iter ) {
		analyz.addSensor(iter->first, iter->second);
	}
	
	// Run it :
	analyz.run();
}//----- End of EnOceanAnalyserThread

bool EnOceanAnalyser::addSensor(SensorId id, EnOceanCallbackFunction cf) {
	return (sensors.insert(pair<SensorId,EnOceanCallbackFunction>(id, cf))).second;
} //----- End of addSensor

void EnOceanAnalyser::setMessagesQueue(blocking_queue<enocean_data_structure>* mQ) {
	messagesQueue = mQ;
} //----- End of setMessagesQueue

void EnOceanAnalyser::run() {
	enocean_data_structure* frame;
	SensorId id;
	string data;
	map<SensorId, EnOceanCallbackFunction>::const_iterator translator;
	while (messagesQueue->front(frame, NULL) == 0) {
		id = getEnOceanID(frame);
		if ((translator = sensors.find(id)) != sensors.end()) { // If it is a sensor we use :
			data = (translator->second)(frame);
			printf(data.c_str()); // TO DO : Log
		}
		free(frame);
	}
	
} //----- End of run


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanAnalyser::EnOceanAnalyser() {

} //----- End of EnOceanAnalyser

EnOceanAnalyser::~EnOceanAnalyser() {
	// TODO Auto-generated destructor stub
} //----- End of ~EnOceanAnalyser


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


