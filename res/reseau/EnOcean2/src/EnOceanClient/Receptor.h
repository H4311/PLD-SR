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
#include <pthread.h>
#include <string>

//----------------------------------------------------- Personnal Includes
#include "../Libs/blocking_queue.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------
// Description :
//		Receives and saves into a queue the data sent by a server (TCP).
//
//------------------------------------------------------------------------

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

	int readFrame(int nbFrame = 0);
	// Manual :
	//		Reads nbFrame and sends them into the queue.Returns the number of frame read.
	//		If nbFrame = 0, then it reads until the connection is closed by the server.
	// Contract :
	//		The connection has been opened.

	void sendFrame();
	// Manual :
	//		Sends the waiting data to the server.
	// Contract :
	//		The connection has been opened.

	void closeSocket();
	// Manual :
    //		Close the connection with the server.
    // Contract :
    //		The connection is open.

	void run();
	// Manual :
    //		Lauches the thread, which loop on readFrame.
    // Contract :
    //		Not to be used twice without stop() before.
	void stop();
	// Manual :
    //		Stops the thread.
    // Contract :
    //		/

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	Receptor(unsigned int frameS, blocking_queue<string>* msgToSend);
	virtual ~Receptor();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods
	virtual void frame_receive(char* buffer) = 0;
	// Manual :
    //		Processes the receipt of a complete frame.
    // Contract :
    //		/

	bool getFlag();
	// Manual :
    //		Gets the value of the synchro flag.
    // Contract :
    //		/

	void waitData();
	// Manual :
	//		Waits for data to be read.
	// Contract :
	//		The connection is open.

	int recvFrame(char* buffer);
	// Manual :
	//		Receives data (blocking).
	// Contract :
	//		The connection is open.

	int sendFrame(const char* buffer);
	// Manual :
	//		Sends data (blocking).
	// Contract :
	//		The connection is open.

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	unsigned int frameSize;			// Size in octet of a frame
	int sock;						// Socket
	blocking_queue<string>* msgToSend;		// Messages to be sent
	bool flag;						// Synchro flag (for the thread)
	pthread_mutex_t mutexSock;		// Mutex protecting the socket
	pthread_t threadSend;			// Thread running to send data
	pthread_t threadReceive;		// Thread running to receive data

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes
	friend void* ReceptorThread_Receive (void* param);
	friend void* ReceptorThread_Send (void* param);
//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class
void* ReceptorThread_Send (void* param);
void* ReceptorThread_Receive (void* param);
// Manual :
//		Lauches the thread.
// Contract :
//		param is of type (Receptor*).

#endif /* Receptor_H_ */
