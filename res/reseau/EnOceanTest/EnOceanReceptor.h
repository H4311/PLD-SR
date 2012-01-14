/*
 * EnOceanReceptor.h
 *
 *  Created on: 8 janv. 2012
 *      Author: bill
 */

#ifndef ENOCEANRECEPTOR_H_
#define ENOCEANRECEPTOR_H_

#include <vector>
#include "sensors/EnOceanSensor.h"
#include "csslType.h"

using namespace std;


typedef void (*EnOceanCallbackFunction)(enocean_data_structure frame);

/**
 * @defgroup Definitions for the string representation
 * The definitions for the human-readable string representation
 * @{
 */
#define HR_TYPE "Type: "
#define HR_RPS  "RPS "
#define HR_1BS  "1BS "
#define HR_4BS  "4BS "
#define HR_HRC  "HRC "
#define HR_6DT  "6DT "
#define HR_MDA  "MDA "
#define HR_DATA " Data: "
#define HR_SENDER "Sender: "
#define HR_STATUS " Status: "
#define HR_CHECKSUM " Checksum: "
#define HR_TYPEUNKN "unknown "

class EnOceanReceptor {
public:

	const int ERR_DEVICE_OPEN_FAILURE = -1;

	int nQueueID;

	cssl_t *serial;

	enocean_data_structure receivebuffer[5]; ///< the buffer for received dataframes
	int frames_received = 0; ///< The actual dataframe being received (=write position) - ringbuffer -> modulo BUFSIZE
	int bytes_received = 0; ///< the position in the actual (receiving) frame
	int frames_read = 0; ///< some variable for read-position

	EnOceanCallbackFunction callback = NULL;






	EnOceanReceptor();
	EnOceanReceptor(vector<EnOceanSensor> sensors, char* hostAddress, int portNum);
	virtual ~EnOceanReceptor();

	void connect(char* address, int portno, EnOceanCallbackFunction cb);
	void close();
	void frame_receive();
	void rawReceive();

protected:
	vector<EnOceanSensor> sensors;
};

#endif /* ENOCEANRECEPTOR_H_ */
