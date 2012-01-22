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

//------------------------------------------------------ Personnal Include
#include "EnOceanReceptor.h"
#include "Sensor.h"
//-------------------------------------------------------------- Constants



//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m, unsigned int frameS): Receptor(frameS), messagesQueue(m) {
} //----- End of EnOceanReceptor

EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m): Receptor(EnOceanSensor::FRAME_SIZE), messagesQueue(m) {
	cout << "<Receptor> Created.\n";
} //----- End of EnOceanReceptor

EnOceanReceptor::~EnOceanReceptor() {
} //----- End of ~EnOceanReceptor


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

/** Is called, if a full frame was received
 */
void EnOceanReceptor::frame_receive(char* buffer) {
	enocean_data_structure frame;
	cout << "<Receptor> Frame to be sent.\n";
	cout << "<Receptor> " << buffer << endl;
	EnOceanSensor::toFrame(&frame, buffer);
	if (frame.ID_BYTE3 == 0xE3) {
	messagesQueue->push(&frame, NULL);
	}
} //----- End of frame_receive
