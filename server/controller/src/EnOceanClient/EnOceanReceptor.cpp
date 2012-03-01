/*************************************************************************
                           EnOceanReceptor  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <EnOceanReceptor> (EnOceanReceptor.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
//------------------------------------------------------ Personnal Include
#include "EnOceanReceptor.h"
#include "../Devices/EnOceanSensorAPI.h"
//-------------------------------------------------------------- Constants



//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void EnOceanReceptor::pushFrame(enocean_data_structure* frame) {
	char buffer[EnOceanSensorAPI::FRAME_SIZE];
	EnOceanSensorAPI::toString(frame, buffer);
	string sBuffer = buffer;
	msgToSend->push(&sBuffer);
}
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m, unsigned int frameS, blocking_queue<string>* msg): Receptor(frameS, msg), messagesQueue(m) {
} //----- End of EnOceanReceptor

EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m, blocking_queue<string>* msg): Receptor(EnOceanSensorAPI::FRAME_SIZE, msg), messagesQueue(m) {
	cout << "<Receptor> Created.\n";
} //----- End of EnOceanReceptor

EnOceanReceptor::~EnOceanReceptor() {
} //----- End of ~EnOceanReceptor


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

/** Is called, if a full frame was received
 */
void EnOceanReceptor::frame_receive(char* buffer) {
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	long long *t = new long long;
	*t = ((long long int)timestamp.tv_sec)*1000 + ((long long int)timestamp.tv_usec)/1000;
	enocean_data_structure* frame = new enocean_data_structure();
	if (((buffer[0] >= '0') && (buffer[0] <= '9')) || ((buffer[0] >= 'A') && (buffer[0] <= 'F')))  {
		cout << "<Receptor> Frame to be sent.\n";
		cout << "<Receptor> " << buffer << endl;
		EnOceanSensorAPI::toFrame(frame, buffer);
		pair<enocean_data_structure*, long long*> * data = new pair<enocean_data_structure*, long long*>(frame, t);
		messagesQueue->push(data, NULL);
	}
} //----- End of frame_receive
