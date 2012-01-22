
/*************************************************************************
                           ServerSimulator  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <ServerSimulator> (ServerSimulator.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//------------------------------------------------------ Personnal Include
#include "ServerSimulator.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int ServerSimulator::openSocket (int port)
{
	struct sockaddr_in serv_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return sockfd;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		return sockfd;
	}

	listen(sockfd, 1);

	return sockfd;
}

int ServerSimulator::acceptClient () {
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(struct sockaddr_in);
	sockClient = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	return sockClient;
}

int ServerSimulator::writeClient(char* msg, int length) {
	int n;
	pthread_mutex_lock(&mutex);
	n = write(sockClient,"I got your message", length);
	pthread_mutex_unlock(&mutex);
	return n;
}

int ServerSimulator::closeClient() {
	return close(sockClient);
}

int ServerSimulator::closeSocket() {
	return close(sockfd);
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
ServerSimulator::ServerSimulator(): sockfd(0), sockClient(0) {
	pthread_mutex_init(&mutex, NULL);
} //----- End of ServerSimulator

ServerSimulator::~ServerSimulator() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
} //----- End of ~ServerSimulator


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


