
/*************************************************************************
                           TCPServer  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <TCPServer> (TCPServer.cpp file) -----

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
#include "TCPServer.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

int TCPServer::openSocket (int port)
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
		cout << "<TCP Server> Error - Socket.\n";
		return sockfd;
	}

	listen(sockfd, 1);
	cout << "<TCP Server> Connecté.\n";
	return sockfd;
}

int TCPServer::acceptClient () {
	int s;
	pthread_mutex_lock(&mutex);
	if (sockClient == 0) {
		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(struct sockaddr_in);
		s = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		cout << "<TCP Server> Client accepté.\n";
		sockClient = s;
	}
	else {
		s = sockClient;
	}
	pthread_mutex_unlock(&mutex);
	return s;
}

void TCPServer::waitData() {
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sockClient, &set);
	select(FD_SETSIZE, &set, NULL, NULL, NULL);
}

int TCPServer::writeClient(char* msg, int length) {
	int n;
	pthread_mutex_lock(&mutex);
	n = write(sockClient,msg, length);
	pthread_mutex_unlock(&mutex);
	return n;
}

int TCPServer::readClient(char* msg, int length) {
	int n;
	pthread_mutex_lock(&mutex);
	n = read(sockClient,msg, length);
	pthread_mutex_unlock(&mutex);
	return n;
}

int TCPServer::readClientJSON(string msg) {
	char c = 0;
	int n = 1;
	pthread_mutex_lock(&mutex);
	do {
		n = read(sockClient, &c, 1);
	} while ((c!='{') && (n>0));
	if (n<0) { return n; }

	int nbAcc = 1;
	msg = c;
	do {
		n = read(sockClient, &c, 1);
		msg += c;
		if (c == '{') { nbAcc++; }
		else if (c == '}') { nbAcc--; }
	} while ((nbAcc > 0) && (n>0));
	pthread_mutex_unlock(&mutex);
	return n;
}

int TCPServer::closeClient() {
	return close(sockClient);
}

int TCPServer::closeSocket() {
	return close(sockfd);
}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
TCPServer::TCPServer(): sockfd(0), sockClient(0) {
	pthread_mutex_init(&mutex, NULL);
} //----- End of TCPServer

TCPServer::~TCPServer() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
} //----- End of ~TCPServer


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods


