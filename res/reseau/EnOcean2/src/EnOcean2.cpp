/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */

#include "EnOceanClient/EnOceanReceptor.h"
#include "EnOceanClient/EnOceanAnalyser.h"
#include "Simulator/EnOCeanBaseSimulator.h"
#include "Simulator/Sensors/SensorSimulatorTempHumi.h"
#include "Simulator/Actuators/EnOceanActuatorAirConditioning.h"
#include "Simulator/Actuators/EventActuatorFire.h"
#include <iostream>
#include "Devices/DeviceTable.h"
#include "Devices/EnOceanSensorAPI.h"
#include "Simulator/Model/Subject.h"
#include <pthread.h>
#include <unistd.h>
#include "EnOceanClient/ServerSettings.h"
/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";

	DeviceTable table = DeviceTable();
	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();

// ----- SIMULATED SENSORS

	blocking_queue<string> msgToSendSimulator = blocking_queue<string>();

	string adresseSimulatedSensor = "127.0.0.1";
	int portSimulatedSensor = 5008;
//
//	Room room1 = Room(1);
//	Room room2 = Room(2);
//	Room room3 = Room(3);
//	Room room4 = Room(4);
//
//	room1.addNeigthborRoom(&room2);
//	room2.addNeigthborRoom(&room3);
//	room3.addNeigthborRoom(&room4);
//
//	EnOCeanBaseSimulator simulator = EnOCeanBaseSimulator();
//	SensorSimulatorTempHumi sensorSimu1 = SensorSimulatorTempHumi(0x012345, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu1);
//
//	SensorSimulatorTempHumi sensorSimu2 = SensorSimulatorTempHumi(0x01, &room2, 0, 40);
//	simulator.addSensor(&sensorSimu2);
//
//	SensorSimulatorTempHumi sensorSimu3 = SensorSimulatorTempHumi(0x02, &room3, 0, 40);
//	simulator.addSensor(&sensorSimu3);
//
//	SensorSimulatorTempHumi sensorSimu4 = SensorSimulatorTempHumi(0x03, &room4, 0, 40);
//	simulator.addSensor(&sensorSimu4);
//
//	SensorSimulatorTempHumi sensorSimu5 = SensorSimulatorTempHumi(0x04, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu5);
//
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//
//
//	simulator.openSocket(portSimulatedSensor);
//	simulator.run();
//
//	table.add((EnOceanSensorAPI::SensorId)0x012345, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x1, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x2, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x3, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x4, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//
//	EnOceanActuatorAirConditioning airCond = EnOceanActuatorAirConditioning(1, 10.0, 12, 0, 40);
//	airCond.addSubject(&room1);
//	airCond.addSubject(&room2);
//	airCond.addSubject(&room3);
//	airCond.addSubject(&room4);
//	airCond.setStatus(true);
//
//	EventActuatorFire fire = EventActuatorFire(2, 5);
//	fire.addSubject(&room1);
//
//	simulator.addActuator(&airCond);
//	simulator.addActuator(&fire);


// ----- ENOCEAN SENSORS

	//string adresseEnOcean = "134.214.105.28";

	//system("ssh -f -L 6543:134.214.105.28:5000 -N bplanche@iftpserv2.insa-lyon.fr")
	string adresseEnOcean = "127.0.0.1";
	int portEnOcean = 6543;

	table.add((EnOceanSensorAPI::SensorId)0x00893378, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempSensor_EEP_07_02_05);
	table.add((EnOceanSensorAPI::SensorId)0x0021CBE3, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseRockerSwitch_EEP_05_02_01);
	table.add((EnOceanSensorAPI::SensorId)0x0001B592, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseContactSensor_EEP_06_00_01);
	table.add((EnOceanSensorAPI::SensorId)0x00054A7F, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseLumAndOcc_EEP_07_08_01);

	blocking_queue<string> msgToSend = blocking_queue<string>();


// ----- SUNSPOT SENSORS

	//string adresseEnOcean = "134.214.105.28";

	//system("ssh -f -L 6543:134.214.105.28:5000 -N bplanche@iftpserv2.insa-lyon.fr")
	string adresseSunSpot = "127.0.0.1";
	int portSunSpot = 5555;

	table.add((EnOceanSensorAPI::SensorId)0x00005896, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseSunSpot);


	ServerSettings serverSettings = ServerSettings(&table, &msgToSend, NULL);
	serverSettings.openSocket(1234);
	serverSettings.run();

	EnOceanAnalyser analyser = EnOceanAnalyser(&table, &msgQueue);
	analyser.run();

	EnOceanReceptor recepSimulator = EnOceanReceptor(&msgQueue, &msgToSendSimulator);
	recepSimulator.open(adresseSimulatedSensor.c_str(), portSimulatedSensor);
	recepSimulator.run();

	EnOceanReceptor recep = EnOceanReceptor(&msgQueue, &msgToSendSimulator);
	recep.open(adresseEnOcean.c_str(), portEnOcean);
	recep.run();

	EnOceanReceptor recepSunSpot = EnOceanReceptor(&msgQueue, &msgToSendSimulator);
	recepSunSpot.open(adresseSunSpot.c_str(), portSunSpot);
	recepSunSpot.run();





	enocean_data_structure* frame = new enocean_data_structure();
	EnOceanSensorAPI::toFrame_AirConditioning(frame, 1,true,0,0,40);
	recepSimulator.pushFrame(frame);

	for (;;) {
//		simulator.addSensor(&sensorSimu1);
//		cout << "<Main> Ajout d'un capteur. Total = " << simulator.countSensors() << endl;
//		airCond.update();
		usleep(1000000);
	}
//	simulator.stop();
//	simulator.closeSocket();



//
//	DeviceTable table = DeviceTable();
//	table.add((EnOceanSensorAPI::SensorId)0x00893378, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempSensor_EEP_07_02_05);
//	table.add((EnOceanSensorAPI::SensorId)0x0021CBE3, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseRockerSwitch_F6_02_01);
//	table.add((EnOceanSensorAPI::SensorId)0x0001B592, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseContactSensor_D5_00_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00054A7F, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseLumAndOcc_EEP_07_08_01);
//
//	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();
//
//	EnOceanAnalyser analyser = EnOceanAnalyser(&table, &msgQueue);
//	analyser.run();
//
//	blocking_queue<string> msgToSend = blocking_queue<string>();
//	EnOceanReceptor recep = EnOceanReceptor(&msgQueue, &msgToSend);
//	recep.open(adresse.c_str(), port);
//	recep.run();
//
//	int i = 0;
//	for (;;) {
//		i++;
//		string* msg = new string();
//		if (i%2 == 0) {
//			*msg = "A55A6B0570000000FF9F1E0630D2";
//		} else {
//			*msg = "A55A6B0550000000FF9F1E0630D2";
//		}
//		msgToSend.push(msg);
//		cout << "<MAIN> Message to be sent : " << *msg <<".\n";
//		usleep(3000000);
//	}

	cout << "Fin\n";

	return EXIT_SUCCESS;
}
