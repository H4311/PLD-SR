/*************************************************************************
                           Receptor  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <Receptor> (Receptor.h file) --------

#ifndef Receptor_H_
#define Receptor_H_

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System Includes
using namespace std;
#include <stdint.h>
#include <signal.h>
#include <termios.h>


//----------------------------------------------------- Personnal Includes
#include "blocking_queue.h"

//------------------------------------------------------------- Constantes

class Receptor
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

	int read(int nbFrame = 0);
	// Manual :
	    //		Reads nbFrame and sends them into the queue.Returns the number of frame read.
		//		If nbFrame = 0, then it reads until the connection is closed by the server.
	    // Contract :
	    //		The connection has been opened.

	void close();
	// Manual :
    //		Close the connection with the server.
    // Contract :
    //		The connection is open.


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	Receptor(unsigned int frameS);
	virtual ~Receptor();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	virtual void frame_receive(char* buffer) = 0;
	// Manual :
    //		Processes the receipt of a complete frame.
    // Contract :
    //		/

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	unsigned int frameSize;
	int sock;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class

#endif /* Receptor_H_ */
