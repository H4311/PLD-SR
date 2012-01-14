/*
 * EnOceanReceptor.cpp
 *
 *  Created on: 8 janv. 2012
 *      Author: bill
 */
#include <stdio.h>
#include "EnOceanReceptor.h"
#include "cssl.h"


void EnOceanReceptor::connect(char* address, int portno, EnOceanCallbackFunction cb) {
	cssl_start();
	// 9600 bps, 8 data, 0 parity, 1 stop)
	serial=cssl_openSock(address, portno,(cssl_callback_t*)raw_receive,0,9600,8,0,1);
	if (!serial) {
		throw ERR_DEVICE_OPEN_FAILURE;
	}
	callback = cb;
	return;
}

void EnOceanReceptor::close() {
	cssl_close(serial);
	cssl_stop();
}










/** Is called, if a full frame was received
 */
void EnOceanReceptor::frame_receive() {
	if(callback != NULL)
		callback(receivebuffer[frames_read]);
	frames_read++;
	frames_read%=BUFSIZE;
}

/** Is called, when some byte was received (only for internal use!)
 */
void EnOceanReceptor::raw_receive(int id, uint8_t *buf, int length) {
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
}







EnOceanReceptor::EnOceanReceptor() {

}

EnOceanReceptor::EnOceanReceptor(vector<EnOceanSensor> sensors, char* hostAddress, int portNum) {
	//enocean_error_structure error = enocean_initSock(hostAddress, portNum);
	//if (error.code != E_OK) {
	//	printf("%s\n",error.message);
	//}
	//enocean_set_callback_function(callBack);
}

EnOceanReceptor::~EnOceanReceptor() {
	// TODO Auto-generated destructor stub
}





///**
// * returns a clean data structure, filled with 0
// */
//enocean_data_structure enocean_clean_data_structure() {
//	int i = 0;
//	enocean_data_structure ds;
//	BYTE* b;
//	for (i=0;i < sizeof(ds);i++) {
//		b = (BYTE*) &ds + i;
//		*b = 0x00;
//	}
//	return ds;
//}
//
///**
// * Convert a data_structure into a data_structure_6DT
// * Note: There will be no copy of the passed data_structure.
// *   So if you change data in the returned new structure, also
// *   data in the original struct will be changed (pointers!)
// */
//enocean_data_structure_6DT* enocean_convert_to_6DT(enocean_data_structure* in) {
//	enocean_data_structure_6DT* out;
//	// no conversion necessary - just overlay the other struct
//	out = (enocean_data_structure_6DT*) in;
//	return out;
//}
//
///**
// * Convert a data_structure into a data_structure_MDA
// * Note: There will be no copy of the passed data_structure.
// *   So if you change data in the returned new structure, also
// *   data in the original struct will be changed (pointers!)
// */
//enocean_data_structure_MDA* enocean_convert_to_MDA(enocean_data_structure* in) {
//	enocean_data_structure_MDA* out;
//	// no conversion necessary - just overlay the other struct
//	out = (enocean_data_structure_MDA*) in;
//	return out;
//}
//
//
//void enocean_send_raw(BYTE* data, int size)
//{
//
//	cssl_putdata(serial,(uint8_t*)data,size);
//}
//
//void enocean_send(enocean_data_structure* data)
//{
//	enocean_send_raw((BYTE*)data, sizeof(*data));
//}
//
//void enocean_send_byte(BYTE* data)
//{
//	enocean_send_raw((BYTE*)data, sizeof(*data));
//}
