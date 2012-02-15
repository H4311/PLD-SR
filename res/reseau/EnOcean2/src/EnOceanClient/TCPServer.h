
/*************************************************************************
                           TCPServer  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <TCPServer> (TCPServer.h file) --------

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <string.h>
#include <pthread.h>
//------------------------------------------------------ Personnal Include

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Analyses the frame provided by the server, and extracts the informations from them, for the chosen sensors.
//
//------------------------------------------------------------------------

class TCPServer
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	int openSocket(int port);
	// Manual :
    //		Open the socket.

	int acceptClient();
	// Manual :
    //		Accept a client connection.
    // Contract :
    //		open()
	//		Connexion du client en lecture avant en écriture !

	int writeClient(char* msg, int length);
	// Manual :
	//		Write to the client.
	// Contract :
	//		open() & accept()

	int readClient(char* msg, int length);
	int readClientJSON(string* msg);
	// Manual :
	//		Read from the client.
	// Contract :
	//		open() & accept()

	void waitData();
	int closeClient();
	int closeSocket();


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	TCPServer();
	virtual ~TCPServer();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	int sockfd;
	int sockClient;
	pthread_mutex_t mutex;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* TCP_SERVER_H_ */
