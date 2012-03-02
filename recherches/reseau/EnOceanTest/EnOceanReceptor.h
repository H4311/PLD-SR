/*************************************************************************
                           EnOceanReceptor  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanReceptor> (EnOceanReceptor.h file) --------

#ifndef ENOCEANRECEPTOR_H_
#define ENOCEANRECEPTOR_H_

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System Includes
using namespace std;

//----------------------------------------------------- Personnal Includes
#include "sensors/EnOceanSensor.h"
#include "cssl.h"
#include "blocking_queue.h"

//------------------------------------------------------------- Constantes
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
//------------------------------------------------------------------ Types 
typedef void (*EnOceanCallbackFunction)(enocean_data_structure frame);

//------------------------------------------------------------------------ 
// Description : 
//		Receipts and stocks the frames sent by the EnOcean server.
//
//------------------------------------------------------------------------ 

class EnOceanReceptor
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

	static const int ERR_DEVICE_OPEN_FAILURE = -1;	
	static const int BUFSIZE = 5;
	static const int QUEUESIZE = 0;
	static const int CSSL_BAUDS = 9600;
	static const int CSSL_BITS = 8;
	static const int CSSL_PARITY = 0;
	static const int CSSL_STOP = 1;

//--------------------------------------------------------- Public Methods

	void connect(char* address, int portno, EnOceanCallbackFunction cb);
	// Manual :
    //		Connects to the EnOcean server, using TCP socket.
    // Contract :
    //		The server is listening.
	
	void close();
	// Manual :
    //		Close the connextion with the server.
    // Contract :
    //		The connection is open.

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanReceptor();
	virtual ~EnOceanReceptor();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	void frame_receive();
	// Manual :
    //		Processes the receipt of a complete frame.
    // Contract :
    //		/
	
	void rawReceive();
	// Manual :
    //		Processes the receipt of data.
    // Contract :
    //		/
	
private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

    int nQueueID;
	cssl_t *serial;
	enocean_data_structure receivebuffer[BUFSIZE]; ///< the buffer for received dataframes
	int frames_received = 0; ///< The actual dataframe being received (=write position) - ringbuffer -> modulo BUFSIZE
	int bytes_received = 0; ///< the position in the actual (receiving) frame
	int frames_read = 0; ///< some variable for read-position
	
	//EnOceanCallbackFunction callback = NULL;
	blocking_queue<enocean_data_structure> messagesQueue = blocking_queue<enocean_data_structure>(QUEUESIZE); // Trames en attente de traitement.

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* ENOCEANRECEPTOR_H_ */
