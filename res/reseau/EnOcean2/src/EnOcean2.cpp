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
#include "Simulator/Model/Room.h"
#include <pthread.h>
#include <unistd.h>
/**
 * main? Don't know, what main does ;)
 */
int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";
//	string adresse = "134.214.105.28";
//	int port = 5000;
	string adresse = "127.0.0.1";
	int port = 5014;

	EnOCeanBaseSimulator simulator = EnOCeanBaseSimulator();

	Room room1 = Room(1);
	Room room2 = Room(2);
	Room room3 = Room(3);
	Room room4 = Room(4);

	room1.addNeigthborRoom(&room2);
	room2.addNeigthborRoom(&room3);
	room3.addNeigthborRoom(&room4);

	SensorSimulatorTempHumi sensorSimu1 = SensorSimulatorTempHumi(0x012345, &room1, 0, 40);
	simulator.addSensor(&sensorSimu1);

	SensorSimulatorTempHumi sensorSimu2 = SensorSimulatorTempHumi(0x01, &room2, 0, 40);
	simulator.addSensor(&sensorSimu2);

	SensorSimulatorTempHumi sensorSimu3 = SensorSimulatorTempHumi(0x02, &room3, 0, 40);
	simulator.addSensor(&sensorSimu3);

	SensorSimulatorTempHumi sensorSimu4 = SensorSimulatorTempHumi(0x03, &room4, 0, 40);
	simulator.addSensor(&sensorSimu4);

	SensorSimulatorTempHumi sensorSimu5 = SensorSimulatorTempHumi(0x04, &room1, 0, 40);
	simulator.addSensor(&sensorSimu5);

	simulator.addSensor(&sensorSimu1);
	simulator.addSensor(&sensorSimu2);
	simulator.addSensor(&sensorSimu3);
	simulator.addSensor(&sensorSimu4);
	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);


	simulator.openSocket(port);
	simulator.run();

	DeviceTable table = DeviceTable();
	table.add((EnOceanSensorAPI::SensorId)0x012345, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x1, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x2, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x3, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
	table.add((EnOceanSensorAPI::SensorId)0x4, (EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);

	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();
	blocking_queue<string> msgToSend = blocking_queue<string>();

	EnOceanAnalyser analyser = EnOceanAnalyser(&table, &msgQueue);
	analyser.run();

	EnOceanReceptor recep = EnOceanReceptor(&msgQueue, &msgToSend);
	recep.open(adresse.c_str(), port);
	recep.run();

	EnOceanActuatorAirConditioning airCond = EnOceanActuatorAirConditioning(1, 10.0, 12, 0, 40);
	airCond.addRoom(&room1);
	airCond.addRoom(&room2);
	airCond.addRoom(&room3);
	airCond.addRoom(&room4);
	airCond.setStatus(true);

	EventActuatorFire fire = EventActuatorFire(2, 5);
	fire.addRoom(&room1);

	simulator.addActuator(&airCond);
	simulator.addActuator(&fire);
//
//	Emettor em = Emettor();
//	em.open(adresse.c_str(), port);

	enocean_data_structure* frame = new enocean_data_structure();
	EnOceanSensorAPI::toFrame_AirConditioning(frame, 1,true,0,0,40);
	recep.pushFrame(frame);

	for (;;) {
//		simulator.addSensor(&sensorSimu1);
//		cout << "<Main> Ajout d'un capteur. Total = " << simulator.countSensors() << endl;
//		airCond.update();
		usleep(1000000);
	}
	simulator.stop();
	simulator.closeSocket();



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
