/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#include "EnOceanReceptor.h"
#include "EnOceanAnalyser.h"
#include <iostream>
#include "PeriphTable.h"
#include "Sensors.h"
#include <pthread.h>

/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";
	string adresse = "134.214.105.28";

	PeriphTable table = PeriphTable();
	table.add((SensorId)0x21CBE3, (EnOceanCallbackFunction)analyseTempAndHumidSensor);

	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();

	Analyser_thread_param param;
	param.messagesQueue = &msgQueue;
	param.periph = &table;

	pthread_t analyser;
	runAnalyser(&analyser, &param);

	EnOceanReceptor recep = EnOceanReceptor(&msgQueue);
	recep.open(adresse.c_str(), 5000);
	recep.read();


	cout << "Fin\n";

	return EXIT_SUCCESS;
}
