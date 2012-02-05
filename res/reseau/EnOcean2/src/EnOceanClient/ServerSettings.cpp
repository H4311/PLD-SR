/*************************************************************************
                           ServerSettings  -  description
                             -------------------
    Creation             : 05 Febr. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <ServerSettings> (ServerSettings.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <unistd.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "ServerSettings.h"
#include "../Libs/jsoncpp-src-amalgamation0.6.0-rc2/json/json.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

void* ServerSettingsThread_Receive (void* param) {
	int n;
	string msg;
	ServerSettings* server = (ServerSettings*)param;

	// Wait for client :
	server->acceptClient();


	// Sends data from each sensor, sleeping between two sending :
	while(server->getFlag() == 0) {

		// Waiting for data to be read :
		server->server.waitData();

		if((n = server->server.readClientJSON(msg)) < 0)
		{
			cout << "<Server Settings> Error - Read | " << n << " - Message : " << msg << endl;
			break;
		}

		cout << "<Server Settings> Order Received - " << msg << ".\n";

		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( msg, root );
		if ( !parsingSuccessful )
		{
		    // report to the user the failure and their locations in the document.
		    cout << "<Server Settings> Error - Parsing | Message : " << msg  << " | Error : "<< reader.getFormatedErrorMessages() << endl;
		}
		else {
			// Get the ID :
			int idDevice = root.get("i", 0).asInt();
			// Get the action :
			int idAction = root.get("a", 0).asInt();
				// idAction :	1 -> Add Device			Needed values : ID, type, Rooms/Peoples, Simulated
				//				2 -> Delete Device		Needed values : ID
				//				3 -> Set Actuator		Needed values : ID, type, on/off, value

			if (idAction == 1) {

			}
			else if (idAction == 2) {
				pthread_mutex_lock(&(server->mutex));
				if (server->sensors->del(idDevice)) { // If we are deleting a sensor :
					// TO DO:
					//		DELETE FROM THE MYSQL DB !
					cout << "<Server Settings> Sensor n°" << idDevice << " - Deleted !\n";
					if (server->simu->delSensor(idDevice)) {
						cout << "<Server Settings> Simulated Sensor n°" << idDevice << " - Deleted !\n";
					}
				}
				else { // If we are deleting an actuator :
					// TO DO:
					//		DELETE FROM THE MYSQL DB !
					cout << "<Server Settings> Actuator n°" << idDevice << " - Deleted !\n";
					if (server->simu->delActuator(idDevice)) {
						cout << "<Server Settings> Simulated Actuator n°" << idDevice << " - Deleted !\n";
					}
				}
				pthread_mutex_unlock(&(server->mutex));
			}
			else if (idAction == 3) {
				int type = root.get("t", 0).asInt();
				bool on = root.get("o", false).asBool();
				float value = (double)root.get("v", 0.0).asDouble();
				enocean_data_structure frame;
				EnOceanSensorAPI::toFrame_Actuator(&frame, (EnOceanSensorAPI::SensorId)idDevice, type, on, value);
				char buffer[EnOceanSensorAPI::FRAME_SIZE];
				EnOceanSensorAPI::toString(&frame, buffer);
				pthread_mutex_lock(&(server->mutex));
				server->msgToSend->push(new string(buffer));
				pthread_mutex_unlock(&(server->mutex));
			}

		}
	}

	server->closeClient();

	return NULL;
}//----- End of EnOceanBaseSimulatorThread_Send


int ServerSettings::openSocket(int port) {
	return server.openSocket(port);
}

int ServerSettings::acceptClient() {
	return server.acceptClient();
}

int ServerSettings::closeClient() {
	return server.closeClient();

}
int ServerSettings::closeSocket() {
	return server.closeSocket();
}

int ServerSettings::readClient(char* msg, int length) {
	return server.readClient(msg, length);
}

int ServerSettings::getFlag() {
	int f;
	pthread_mutex_lock(&mutex);
	f = flag;
	pthread_mutex_unlock(&mutex);
	return f;
}

void ServerSettings::run() {
	pthread_mutex_lock(&mutex);
	flag = 0;
	pthread_mutex_unlock(&mutex);
	pthread_create(&thread_Receive, NULL, EnOceanBaseSimulatorThread_Receive, this);
}

void ServerSettings::stop() {
	pthread_mutex_lock(&mutex);
	flag = 1;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread_Receive, NULL);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
ServerSettings::ServerSettings(DeviceTable* sens,  blocking_queue<string>* msg, EnOCeanBaseSimulator* sim): sensors(sens), msgToSend(msg), simu(sim){
	pthread_mutex_init(&mutex, NULL);
	flag = 0;
} //----- End of ServerSettings

ServerSettings::~ServerSettings() {
	// TODO Auto-generated destructor stub
	stop();
	pthread_mutex_destroy(&mutex);
} //----- End of ~ServerSettings


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
