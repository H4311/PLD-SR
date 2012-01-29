
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
#include <iostream>

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
		cout << "<Base Simu> Error - Socket.\n";
		return sockfd;
	}

	listen(sockfd, 1);
	cout << "<Base Simu> Connecté.\n";
	return sockfd;
}

int ServerSimulator::acceptClient () {
	int s;
	pthread_mutex_lock(&mutex);
	if (sockClient == 0) {
		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(struct sockaddr_in);
		s = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		cout << "<Base Simu> Client accepté.\n";
		sockClient = s;
	}
	else {
		s = sockClient;
	}
	pthread_mutex_unlock(&mutex);
	return s;
}

void ServerSimulator::waitData() {
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sockClient, &set);
	select(FD_SETSIZE, &set, NULL, NULL, NULL);
}

int ServerSimulator::writeClient(char* msg, int length) {
	int n;
	pthread_mutex_lock(&mutex);
	n = write(sockClient,msg, length);
	pthread_mutex_unlock(&mutex);
	return n;
}

int ServerSimulator::readClient(char* msg, int length) {
	int n;
	pthread_mutex_lock(&mutex);
	n = read(sockClient,msg, length);
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


