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

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m, unsigned int frameS): Receptor(frameS), messagesQueue(m) {
} //----- End of EnOceanReceptor

EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m): Receptor(EnOceanSensorAPI::FRAME_SIZE), messagesQueue(m) {
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
	long *t = new long;
	*t = timestamp.tv_sec;
	enocean_data_structure* frame = new enocean_data_structure();
	cout << "<Receptor> Frame to be sent.\n";
	cout << "<Receptor> " << buffer << endl;
	EnOceanSensorAPI::toFrame(frame, buffer);
	pair<enocean_data_structure*, long*> * data = new pair<enocean_data_structure*, long*>(frame, t);
	messagesQueue->push(data, NULL);
} //----- End of frame_receive
