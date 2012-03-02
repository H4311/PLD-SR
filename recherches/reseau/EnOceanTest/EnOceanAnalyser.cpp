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

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void EnOceanAnalyser::addSensor(SensorId id, EnOceanCallbackFunction cf) {
	return sensors.insert(pair<SensorId,EnOceanCallbackFunction>(id, cf);
} //----- End of addSensor

void EnOceanAnalyser::setMessagesQueue(blocking_queue<enocean_data_structure>* mQ) {
	messagesQueue = mq;
} //----- End of setMessagesQueue

void EnOceanAnalyser::run() {
	enocean_data_structure frame;
	while (messagesQueue.front(&frame, NULL) {
		
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

/** Is called, if a full frame was received
 */
void EnOceanAnalyser::frame_receive() {
	if(callback != NULL)
		//callback(receivebuffer[frames_read]);
		messagesQueue.push(receivebuffer[frames_read], NULL);
	frames_read++;
	frames_read%=BUFSIZE;
} //----- End of frame_receive

/** Is called, when some byte was received (only for internal use!)
 */
void EnOceanAnalyser::raw_receive(int id, uint8_t *buf, int length) {
    int i;
    for(i=0;i<length;i++) {
    	// write received byte into buffer
    	BYTE* actual_frame = (BYTE*) &(receivebuffer[frames_received]);
    	*(actual_frame + bytes_received*sizeof(BYTE)) = buf[i];
    	bytes_received++;
    	if (bytes_received >= (sizeof(struct enocean_data_structure)/sizeof(BYTE))) {
    		// data-frame full -> begin next one and call appropriate function
    		bytes_received = 0;
    		frames_received++;
    		frames_received%=BUFSIZE;
    		frame_receive();
    	}
    }
} //----- End of raw_receive

