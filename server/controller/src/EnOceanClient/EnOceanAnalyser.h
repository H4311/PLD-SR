/*************************************************************************
                           EnOceanAnalyser  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanAnalyser> (EnOceanAnalyser.h file) --------

#ifndef ENOCEANANALYSER_H_
#define ENOCEANANALYSER_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <map>
#include <string>
#include <pthread.h>

//------------------------------------------------------ Personnal Include
#include "../Config.h"
#include "../Libs/blocking_queue.h"
#include "../Devices/DeviceTable.h"
#include "../Devices/EnOceanSensorAPI.h"
#include "EnOceanReceptor.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 
typedef struct thread_param {
	EnOceanMsgQueue* messagesQueue;
	DeviceTable* periph;
} Analyser_thread_param;


//------------------------------------------------------------------------ 
// Description : 
//		Analyses the frame provided by the server, and extracts the informations from them, for the chosen sensors.
//
//------------------------------------------------------------------------ 

class EnOceanAnalyser
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void analyse();
	// Manual :
    //		Loop : waits for coming frames, then analyses and processes them.
    // Contract :
    //		The messageQueue must be defined.

	void run();
	// Manual :
    //		Lauches the thread, to run the analysis.
    // Contract :
    //		Not to be used twice without stop() before.
	void stop();
	// Manual :
    //		Stop the thread.
    // Contract :
    //		/

	void setMessagesQueue (EnOceanMsgQueue* messagesQueue);
	// Manual :
    //		Set the attribute messagesQueue
    // Contract :
    //		/

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanAnalyser(DeviceTable* periph, EnOceanMsgQueue* messagesQueue);
	virtual ~EnOceanAnalyser();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	bool getFlag();

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	DeviceTable* periph;				// Table of the known sensors
	EnOceanMsgQueue* messagesQueue;		// Messages to be analysed
	bool flag;							// Synchronisation flag for the thread
	pthread_mutex_t mutex;				// Mutex to protect the data
	pthread_t thread;					// Thread

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

void* EnOceanAnalyserThread (void* param);
// Manual :
//		Lauches the thread.
// Contract :
//		param is of type (EnOceanAnalyser*).

#endif /* ENOCEANANALYSER_H_ */
