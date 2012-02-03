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
#include <utility>
//----------------------------------------------------- Personnal Includes
#include "../Devices/EnOceanProtocol.h"
#include "../Libs/blocking_queue.h"
#include "Receptor.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types 
typedef blocking_queue< pair<enocean_data_structure*, long long*> > EnOceanMsgQueue;

//------------------------------------------------------------------------ 
// Description : 
//		Receives and stocks the frames sent by the EnOcean server.
//
//------------------------------------------------------------------------ 

class EnOceanReceptor : public Receptor
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants
	static const int QUEUE_SIZE = 0;
//--------------------------------------------------------- Public Methods

	void pushFrame(enocean_data_structure* frame);

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanReceptor(EnOceanMsgQueue* messagesQueue,blocking_queue<string>* msgToSend);
	EnOceanReceptor(EnOceanMsgQueue* messagesQueue, unsigned int frames, blocking_queue<string>* msgToSend);
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
	EnOceanMsgQueue* messagesQueue; // Queue containing the messages we received.

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* ENOCEANRECEPTOR_H_ */
