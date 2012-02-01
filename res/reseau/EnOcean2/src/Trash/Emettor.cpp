/*************************************************************************
                           Emettor  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <Emettor> (Emettor.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <string.h>

#include <iostream>
typedef int SOCKET;


//------------------------------------------------------ Personnal Include
#include "Emettor.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int Emettor::open(const char* address, const int portno) {
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt;
	long hostAddr;

	bzero(&serverSockAddr,sizeof(serverSockAddr));
	hostAddr = inet_addr(address);
	if ( (long)hostAddr != (long)-1)
		bcopy(&hostAddr,&serverSockAddr.sin_addr,sizeof(hostAddr));
	else
	{
		serverHostEnt = gethostbyname(address);
		if (serverHostEnt == NULL)
		{
			cout << "<Error> EnOcean - gethost\n";
			return -1;
		}
		bcopy(serverHostEnt->h_addr,&serverSockAddr.sin_addr,serverHostEnt->h_length);
	}
	serverSockAddr.sin_port = htons(portno);
	serverSockAddr.sin_family = AF_INET;

	/* creation de la socket */
	if ( (sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	  cout << "<Error> EnOcean - Creation socket client\n";
	  return sock;
	}

	if (connect(sock, (sockaddr*)&serverSockAddr, sizeof(serverSockAddr)) < 0) {
		/* error */
		cout << "<Error> EnOcean - Connection socket client\n";
		return -1;
	}


	return sock;

} //----- End of connect

int Emettor::sendFrame(char* frame, int length) {
	return send(sock, frame, length, 0);
} //----- End of sendFrame

void Emettor::closeSocket() {
	close(sock);
} //----- End of close



//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
Emettor::Emettor() {

} //----- End of Emettor

Emettor::~Emettor() {

} //----- End of ~Emettor


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


