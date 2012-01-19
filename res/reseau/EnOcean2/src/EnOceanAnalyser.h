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

//------------------------------------------------------ Personnal Include
#include "blocking_queue.h"
#include "PeriphTable.h"
#include "Sensors.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 

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

	void run();
	// Manual :
    //		Loop : waits for coming frames, then analyses and processes them.
    // Contract :
    //		The messageQueue must be defined.

	void setMessagesQueue (blocking_queue<enocean_data_structure>* messagesQueue);
	// Manual :
    //		Set the attribute messagesQueue
    // Contract :
    //		/

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanAnalyser(PeriphTable* periph);
	virtual ~EnOceanAnalyser();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	
private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	PeriphTable* periph;
	blocking_queue<enocean_data_structure>* messagesQueue;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class
void* EnOceanAnalyserThread (void* periphTable);
// Manual :
//		Create a instance of EnOceanAnalyser, and run it.
// Contract :
//		sensorsInfo is a pointer to a map<SensorId, EnOceanCallbackFunction>

#endif /* ENOCEANANALYSER_H_ */
