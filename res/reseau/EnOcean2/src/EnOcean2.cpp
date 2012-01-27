/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#include "EnOceanReceptor.h"
#include "EnOceanAnalyser.h"
#include "Simulator/EnOCeanBaseSimulator.h"
#include "Simulator/SensorSimulatorTempHumi.h"
#include <iostream>
#include "PeriphTable.h"
#include "Sensors.h"
#include <pthread.h>
#include <unistd.h>
/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";
	//string adresse = "134.214.105.28";
	//int port = 5000;
	string adresse = "127.0.0.1";
	int port = 2559;

	EnOCeanBaseSimulator simulator = EnOCeanBaseSimulator();

	SensorSimulatorTempHumi sensorSimu1 = SensorSimulatorTempHumi(0x012345, 0, 40);
	simulator.addSensor(&sensorSimu1);

	SensorSimulatorTempHumi sensorSimu2 = SensorSimulatorTempHumi(0x01, 0, 40);
	simulator.addSensor(&sensorSimu2);

	SensorSimulatorTempHumi sensorSimu3 = SensorSimulatorTempHumi(0x02, 0, 40);
	simulator.addSensor(&sensorSimu3);

	SensorSimulatorTempHumi sensorSimu4 = SensorSimulatorTempHumi(0x03, 0, 40);
	simulator.addSensor(&sensorSimu4);

	SensorSimulatorTempHumi sensorSimu5 = SensorSimulatorTempHumi(0x04, 0, 40);
	simulator.addSensor(&sensorSimu5);

	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);


	simulator.openSocket(port);
	simulator.run();

	PeriphTable table = PeriphTable();
	table.add((EnOceanSensorAPI::SensorId)0x012345, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x1, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x2, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x3, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x4, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);

	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();


	EnOceanAnalyser analyser = EnOceanAnalyser(&table, &msgQueue);
	analyser.run();

	EnOceanReceptor recep = EnOceanReceptor(&msgQueue);
	recep.open(adresse.c_str(), port);
	recep.run();

	for (;;) {
		simulator.addSensor(&sensorSimu1);
		cout << "<Main> Ajout d'un capteur. Total = " << simulator.countSensors() << endl;
		usleep(5000000);
	}
	simulator.stop();
	simulator.closeSocket();

	cout << "Fin\n";

	return EXIT_SUCCESS;
}
