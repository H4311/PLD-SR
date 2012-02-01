///*************************************************************************
//                           EnOceanDevice  -  description
//                             -------------------
//    Creation             : 29 Jan. 2012
//    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
//*************************************************************************/
//
////------- Definition - <EnOceanDevice> (EnOceanDevice.h file) --------
//
//#ifndef ENOCEANDEVICE_H_
//#define ENOCEANDEVICE_H_
//
////---------------------------------------------------------------- INCLUDE
//
////-------------------------------------------------------- System Includes
//using namespace std;
////----------------------------------------------------- Personnal Includes
//#include "EnOceanProtocol.h"
////------------------------------------------------------------- Constantes
//
////------------------------------------------------------------------ Types
//
////------------------------------------------------------------------------
//// Description :
////		Object representing an EnOcean device.
////
////------------------------------------------------------------------------
//
//class EnOceanDevice
//{
////----------------------------------------------------------------- PUBLIC
//
//public:
////------------------------------------------------------- Public Constants
//	typedef int32_t SensorId;
//
//	static const unsigned int FRAME_SIZE = 28;
//
////--------------------------------------------------------- Public Methods
//	void fromBuffer(char* buffer, unsigned int length);
//	// Manual :
//    //		Extract the data of a frame.
//    // Contract :
//    //		/
//
//	virtual void processData() = 0;
//	// Manual :
//    //		Process the current data of the device (for example to send it to a DB).
//    // Contract :
//    //		/
//
//	SensorId getId();
//
////------------------------------------------------- Static public Methods
//
////------------------------------------------------------------- Operators
//
////-------------------------------------------------- Builder / Destructor
//
//	EnOceanDevice(SensorId id);
//	virtual ~EnOceanDevice();
//
////---------------------------------------------------------------- PRIVATE
//
//protected:
////------------------------------------------------------ Protected Methods
//
//private:
////----------------------------------------------------- Protected Methods
//
//protected:
////-------------------------------------------------- Protected Attributes
//	SensorId id;
//	enocean_data_structure frame;
//
//private:
////----------------------------------------------------- Private Attributes
//
////--------------------------------------------------------- Friend Classes
//
////-------------------------------------------------------- Private Classes
//
////---------------------------------------------------------- Private Types
//
//};
//
////------------------------------ Other definition, depending on this class
//
//#endif /* ENOCEANDEVICE_H_ */
//
