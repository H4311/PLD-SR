/*************************************************************************
                           Emettor  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <Emettor> (Emettor.h file) --------

#ifndef EMETTOR_H_
#define EMETTOR_H_

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System Includes
using namespace std;
#include <stdint.h>
#include <signal.h>
#include <termios.h>
#include <pthread.h>

//----------------------------------------------------- Personnal Includes
#include "../Libs/blocking_queue.h"

//------------------------------------------------------------- Constantes


//------------------------------------------------------------------------
// Description :
//		Class using an TCP socket to send frames to a server.
//
//------------------------------------------------------------------------

class Emettor
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants


//--------------------------------------------------------- Public Methods

	int open(const char* address, const int portno);
	// Manual :
    //		Connects to the server, using TCP socket.
    // Contract :
    //		The server is listening.

	int sendFrame(char* frame, int length);
	// Manual :
	    //		Sends the given string to the server.
	    // Contract :
	    //		The connection has been opened.

	void closeSocket();
	// Manual :
    //		Close the connection with the server.
    // Contract :
    //		The connection is open.

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	Emettor();
	virtual ~Emettor();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	int sock;	// Socket.


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* EMETTOR_H_ */
