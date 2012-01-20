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

//------------------------------------------------------ Personnal Include
#include "EnOceanReceptor.h"

//-------------------------------------------------------------- Constants



//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanReceptor::EnOceanReceptor(unsigned int frameS): Receptor(frameS) {
	messagesQueue = blocking_queue<enocean_data_structure>(QUEUE_SIZE);
} //----- End of EnOceanReceptor

EnOceanReceptor::EnOceanReceptor(): Receptor(FRAME_SIZE) {
	messagesQueue = blocking_queue<enocean_data_structure>(QUEUE_SIZE);
} //----- End of EnOceanReceptor

EnOceanReceptor::~EnOceanReceptor() {
} //----- End of ~EnOceanReceptor


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

/** Is called, if a full frame was received
 */
void EnOceanReceptor::frame_receive(char* buffer) {
	enocean_data_structure* frame = (enocean_data_structure*)malloc(sizeof(enocean_data_structure));
	BYTE* byte = (BYTE*)frame;
	for (unsigned int i = 0; i < frameSize; i++) {
		*(byte + i*sizeof(BYTE)) = buffer[i];
	}
	messagesQueue.push(frame, NULL);
} //----- End of frame_receive
