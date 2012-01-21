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
#include "EnOceanProtocol.h"
#include "blocking_queue.h"
#include "Receptor.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 
typedef blocking_queue<enocean_data_structure> EnOceanMsgQueue;

//------------------------------------------------------------------------ 
// Description : 
//		Receipts and stocks the frames sent by the EnOcean server.
//
//------------------------------------------------------------------------ 

class EnOceanReceptor : public Receptor
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants
	static const int FRAME_SIZE = 28;
	static const int QUEUE_SIZE = 0;
//--------------------------------------------------------- Public Methods

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanReceptor(blocking_queue<enocean_data_structure>* messagesQueue);
	EnOceanReceptor(blocking_queue<enocean_data_structure>* messagesQueue, unsigned int frames);
	virtual ~EnOceanReceptor();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	void frame_receive(char* buffer);
		// Manual :
	    //		Processes the receipt of a complete frame.
	    // Contract :
	    //		/

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes
	EnOceanMsgQueue* messagesQueue; // Trames en attente de traitement.

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* ENOCEANRECEPTOR_H_ */
