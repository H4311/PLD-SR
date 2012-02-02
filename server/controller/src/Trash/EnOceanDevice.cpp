///*************************************************************************
//                           EnOceanDevice  -  description
//                             -------------------
//    Creation             : 29 Jan. 2012
//    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
//*************************************************************************/
//
////---- Implementation - <EnOceanDevice> (EnOceanDevice.cpp file) -----
//
////---------------------------------------------------------------- INCLUDE
//
////--------------------------------------------------------- System Include
//using namespace std;
//#include <stdlib.h>
////------------------------------------------------------ Personnal Include
//#include "EnOceanDevice.h"
////-------------------------------------------------------------- Constants
//
//
////----------------------------------------------------------------- PUBLIC
//
////--------------------------------------------------------- Public Methods
//void EnOceanDevice::fromBuffer(char* buffer, unsigned int length) {
//	BYTE* byte = (BYTE*)(&frame);
//	BYTE temp;
//	char c[3] = {'0', '0', 0};
//	for (unsigned int i = 0; i < length; i += 2) {
//		c[0] = buffer[i];
//		c[1] = buffer[i+1];
//		temp = strtol(c,NULL,16);
//		*byte = temp;
//		byte += sizeof(BYTE);
//	}
//}
//
//EnOceanDevice::SensorId EnOceanDevice::getId() {
//	return id;
//}
//
////------------------------------------------------- Static public Methods
//
////------------------------------------------------------------- Operators
//
//
////-------------------------------------------------- Builder / Destructor
//EnOceanDevice::EnOceanDevice() {
//} //----- End of EnOceanDevice
//
//EnOceanDevice::~EnOceanDevice() {
//} //----- End of ~EnOceanDevice
//
//
////---------------------------------------------------------------- PRIVATE
//
////------------------------------------------------------ Protected Methods
