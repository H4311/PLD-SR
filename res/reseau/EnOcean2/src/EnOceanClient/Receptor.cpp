/*************************************************************************
                           Receptor  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <Receptor> (Receptor.cpp file) -----

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
#include "Receptor.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* ReceptorThread_Receive (void* param) {
	Receptor* receptor = (Receptor*)param;
	receptor->readFrame();
	return NULL;
}//----- End of ReceptorThread_Receive

void* ReceptorThread_Send (void* param) {
	Receptor* receptor = (Receptor*)param;
	receptor->sendFrame();
	return NULL;
}//----- End of ReceptorThread_Receive

int Receptor::open(const char* address, const int portno) {
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

int Receptor::readFrame(int nbFrame) {
	int nbFrameRead = 0;
	int n;
	char* buffer = (char*)malloc(frameSize*sizeof(char));
	if (nbFrame == 0) {
		while (getFlag() == true) {
			if((n = recvFrame(buffer)) < 0)
			{
				cout << "<Receptor> Error - Read | " << n << endl;
				break;
			}

			cout << "<Receptor> Frame Received.\n";
			frame_receive(buffer);
			cout << "<Receptor> Frame Sent.\n";
			nbFrameRead++;
		}
	}
	else {
		while (nbFrameRead < nbFrame) {
			if((n = recv(sock, buffer, frameSize, 0)) < 0)
			{
				cout << "<Erreur> Read | " << n << endl;
				break;
			}
			cout << "<Receptor> Frame Sent.\n";
			frame_receive(buffer);
			nbFrameRead++;
		}
	}
	free(buffer);
	return nbFrameRead;
} //----- End of readFrame

void Receptor::sendFrame() {
	int n;
	string* buffer;
	while ((getFlag() == true) && (msgToSend->front(buffer, NULL) == 0)) {
		if((n = sendFrame(buffer->c_str())) < 0)
		{
			cout << "<Receptor> Error - Send | " << n << endl;
			break;
		}
		cout << "<Receptor> Frame Sent.\n";
		//free(buffer);
		msgToSend->pop();
	}
}

void Receptor::closeSocket() {
	pthread_mutex_lock(&mutexSock);
	close(sock);
	pthread_mutex_unlock(&mutexSock);
} //----- End of close

bool Receptor::getFlag() {
	bool f;
	pthread_mutex_lock(&mutexSock);
	f = flag;
	pthread_mutex_unlock(&mutexSock);
	return f;
} //----- End of getFlag

void Receptor::run() {
	pthread_mutex_lock(&mutexSock);
	flag = true;
	pthread_mutex_unlock(&mutexSock);
	pthread_create(&threadSend, NULL, ReceptorThread_Send, this);
	pthread_create(&threadReceive, NULL, ReceptorThread_Receive, this);
} //----- End of run

void Receptor::stop() {
	pthread_mutex_lock(&mutexSock);
	flag = false;
	pthread_mutex_unlock(&mutexSock);
	pthread_join(threadSend, NULL);
	pthread_join(threadReceive, NULL);
} //----- End of stop

///**
// * returns a clean data structure, filled with 0
// */
//enocean_data_structure enocean_clean_data_structure() {
//	int i = 0;
//	enocean_data_structure ds;
//	BYTE* b;
//	for (i=0;i < sizeof(ds);i++) {
//		b = (BYTE*) &ds + i;
//		*b = 0x00;
//	}
//	return ds;
//}
//
///**
// * Convert a data_structure into a data_structure_6DT
// * Note: There will be no copy of the passed data_structure.
// *   So if you change data in the returned new structure, also
// *   data in the original struct will be changed (pointers!)
// */
//enocean_data_structure_6DT* enocean_convert_to_6DT(enocean_data_structure* in) {
//	enocean_data_structure_6DT* out;
//	// no conversion necessary - just overlay the other struct
//	out = (enocean_data_structure_6DT*) in;
//	return out;
//}
//
///**
// * Convert a data_structure into a data_structure_MDA
// * Note: There will be no copy of the passed data_structure.
// *   So if you change data in the returned new structure, also
// *   data in the original struct will be changed (pointers!)
// */
//enocean_data_structure_MDA* enocean_convert_to_MDA(enocean_data_structure* in) {
//	enocean_data_structure_MDA* out;
//	// no conversion necessary - just overlay the other struct
//	out = (enocean_data_structure_MDA*) in;
//	return out;
//}
//
//
//void enocean_send_raw(BYTE* data, int size)
//{
//
//	cssl_putdata(serial,(uint8_t*)data,size);
//}
//
//void enocean_send(enocean_data_structure* data)
//{
//	enocean_send_raw((BYTE*)data, sizeof(*data));
//}
//
//void enocean_send_byte(BYTE* data)
//{
//	enocean_send_raw((BYTE*)data, sizeof(*data));
//}


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
Receptor::Receptor(unsigned int frameS, blocking_queue<string>* msg): frameSize(frameS), msgToSend(msg), flag(false){
	pthread_mutex_init(&mutexSock, NULL);
} //----- End of Receptor

Receptor::~Receptor() {
	stop();
	pthread_mutex_destroy(&mutexSock);
} //----- End of ~Receptor


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods

int Receptor::recvFrame(char* buffer) {
	int n;
	pthread_mutex_lock(&mutexSock);
	n = recv(sock, buffer, frameSize, 0);
	pthread_mutex_unlock(&mutexSock);
	return n;
}

int Receptor::sendFrame(const char* buffer) {
	int n;
	pthread_mutex_lock(&mutexSock);
	n = send(sock, buffer, frameSize, 0);
	pthread_mutex_unlock(&mutexSock);
	return n;
}
