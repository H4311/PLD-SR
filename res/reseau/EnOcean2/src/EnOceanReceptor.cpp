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

//-------------------------------------------------------------- Constants



//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m, unsigned int frameS): Receptor(frameS), messagesQueue(m) {
} //----- End of EnOceanReceptor

EnOceanReceptor::EnOceanReceptor(EnOceanMsgQueue* m): Receptor(FRAME_SIZE), messagesQueue(m) {
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
	BYTE* byte = (BYTE*)&frame;
	BYTE temp;
	char c[3] = {'0', '0', 0};
	cout << "<Receptor> Frame to be sent.\n";
	cout << "<Receptor> ";
	for (unsigned int i = 0; i < frameSize; i += 2) {
		c[0] = buffer[i];
		c[1] = buffer[i+1];
		temp = strtol (c,NULL,16);
		*byte = temp;
		byte += sizeof(BYTE);
		cout << temp << "(" << i << ")" << "|";
	}
	cout << endl;
	if (frame.ID_BYTE3 == 0xE3) {
	messagesQueue->push(&frame);
	}
} //----- End of frame_receive
