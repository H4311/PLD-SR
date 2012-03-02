/*
 * test.cpp
 *
 *  Created on: 13 janv. 2012
 *      Author: bplanche
 */
#include "Config.h"
#include "EnOceanClient/EnOceanReceptor.h"
#include "EnOceanClient/EnOceanAnalyser.h"
#include "Simulator/EnOCeanBaseSimulator.h"
#include "Simulator/Sensors/SensorSimulatorTempHumi.h"
#include "Simulator/Actuators/EnOceanActuatorAirConditioning.h"
#include "Simulator/Actuators/EnOceanActuatorMusic.h"
#include "Simulator/Actuators/EventActuatorFire.h"
#include <iostream>
#include "Devices/DeviceTable.h"
#include "Devices/EnOceanSensorAPI.h"
#include "Simulator/Model/Subject.h"
#include "Simulator/Model/Room.h"
#include "Simulator/Model/Patient.h"
#include <pthread.h>
#include <unistd.h>
#include "EnOceanClient/ServerSettings.h"
#include <map>

int main(int argc, char *argv[]) {
	cout << "Testprogram started...\n";

	DeviceTable table = DeviceTable();
	EnOceanMsgQueue msgQueue = EnOceanMsgQueue();

// ----- SIMULATED SENSORS

	blocking_queue<string> msgToSendSimulator = blocking_queue<string>();
	EnOCeanBaseSimulator simulator = EnOCeanBaseSimulator();

	string adresseSimulatedSensor = "127.0.0.1";
	int portSimulatedSensor = 5025;

	// List of the simulated sensors :
	vector<int> simulatedSensorsID;
	simulatedSensorsID.push_back(1048599);
	//simulatedSensorsID.push_back(1048600);
	//simulatedSensorsID.push_back(1048601);
	//simulatedSensorsID.push_back(1048602);
	simulatedSensorsID.push_back(1048603);
	simulatedSensorsID.push_back(1048604);
	simulatedSensorsID.push_back(1048605);
	simulatedSensorsID.push_back(1048606);
	simulatedSensorsID.push_back(1048607);
	simulatedSensorsID.push_back(1048608);
	simulatedSensorsID.push_back(1048609);
	simulatedSensorsID.push_back(1048610);
	simulatedSensorsID.push_back(1048611);
	simulatedSensorsID.push_back(1048612);
	simulatedSensorsID.push_back(1048613);
	simulatedSensorsID.push_back(1048614);
	simulatedSensorsID.push_back(1048615);
	simulatedSensorsID.push_back(1048616);
	simulatedSensorsID.push_back(1048617);
	simulatedSensorsID.push_back(1048618);
	simulatedSensorsID.push_back(1048619);
	simulatedSensorsID.push_back(1048620);
	simulatedSensorsID.push_back(1048621);
	//simulatedSensorsID.push_back(1048622);
	simulatedSensorsID.push_back(1048623);
	simulatedSensorsID.push_back(1048624);
	simulatedSensorsID.push_back(1048625);
	simulatedSensorsID.push_back(1048626);
	simulatedSensorsID.push_back(1048627);
	simulatedSensorsID.push_back(1048628);
	simulatedSensorsID.push_back(1048629);
	simulatedSensorsID.push_back(1048630);
	simulatedSensorsID.push_back(1048631);
	simulatedSensorsID.push_back(1048632);
	simulatedSensorsID.push_back(1048633);
	simulatedSensorsID.push_back(1048634);
	simulatedSensorsID.push_back(1048635);
	simulatedSensorsID.push_back(1048636);
	simulatedSensorsID.push_back(1048637);
	simulatedSensorsID.push_back(1048638);
	simulatedSensorsID.push_back(1048639);
	simulatedSensorsID.push_back(1048640);
	simulatedSensorsID.push_back(1048641);
	simulatedSensorsID.push_back(1048642);
	simulatedSensorsID.push_back(1048643);
	simulatedSensorsID.push_back(1048644);
	simulatedSensorsID.push_back(1048645);
	simulatedSensorsID.push_back(1048646);
	simulatedSensorsID.push_back(1048647);
	simulatedSensorsID.push_back(1048648);
	simulatedSensorsID.push_back(1048649);
	simulatedSensorsID.push_back(1048650);
	simulatedSensorsID.push_back(1048651);
	simulatedSensorsID.push_back(1048652);
	simulatedSensorsID.push_back(1048653);
	simulatedSensorsID.push_back(1048654);
	simulatedSensorsID.push_back(1048655);
	simulatedSensorsID.push_back(1048656);
	simulatedSensorsID.push_back(1048657);
	simulatedSensorsID.push_back(1048658);
	simulatedSensorsID.push_back(1048659);
	simulatedSensorsID.push_back(1048660);
	simulatedSensorsID.push_back(1048661);
	simulatedSensorsID.push_back(1048662);
	simulatedSensorsID.push_back(1048663);
	simulatedSensorsID.push_back(1048664);
	simulatedSensorsID.push_back(1048665);
	simulatedSensorsID.push_back(1048666);
	simulatedSensorsID.push_back(1048667);
	simulatedSensorsID.push_back(1048668);
	simulatedSensorsID.push_back(1048669);
	simulatedSensorsID.push_back(1048670);
	simulatedSensorsID.push_back(1048671);
	simulatedSensorsID.push_back(1048672);
	simulatedSensorsID.push_back(1048673);

	simulatedSensorsID.push_back(0x00001000);
	simulatedSensorsID.push_back(0x00001001);
	simulatedSensorsID.push_back(0x00001002);
	simulatedSensorsID.push_back(0x00001003);
	simulatedSensorsID.push_back(0x00001004);
	simulatedSensorsID.push_back(0x00001005);
	simulatedSensorsID.push_back(0x00001006);
	simulatedSensorsID.push_back(0x00001007);
	simulatedSensorsID.push_back(0x00001008);
	simulatedSensorsID.push_back(0x00001009);
	simulatedSensorsID.push_back(0x00001010);
	simulatedSensorsID.push_back(0x00001011);
	simulatedSensorsID.push_back(0x00001012);
	simulatedSensorsID.push_back(0x00001013);
	simulatedSensorsID.push_back(0x00001014);
	simulatedSensorsID.push_back(0x00001015);
	simulatedSensorsID.push_back(0x00001016);
	simulatedSensorsID.push_back(0x00001017);
	simulatedSensorsID.push_back(0x00001018);
	simulatedSensorsID.push_back(0x00001019);
	simulatedSensorsID.push_back(0x00001020);
	simulatedSensorsID.push_back(0x00001021);
	simulatedSensorsID.push_back(0x00001022);
	simulatedSensorsID.push_back(0x00001023);
	simulatedSensorsID.push_back(0x00001024);


	// Define Rooms :
	Room room111 = Room(1);
	Room room112 = Room(2);
	Room room113 = Room(3);
	Room room114 = Room(4);
	Room room115 = Room(5);
	Room room116 = Room(6);
	Room room117 = Room(7);
	Room room118 = Room(8);
	Room room119 = Room(9);
	Room room120 = Room(10);
	Room room121 = Room(11);
	Room room122 = Room(12);
	Room roomBl11 = Room(13);
	Room roomBl12 = Room(14);
	Room roomDp1 = Room(15);

	Patient pat1 = Patient(1001);
	pat1.setTemperature(38.9);
	Patient pat2 = Patient(1002);
	Patient pat3 = Patient(1003);
	Patient pat4 = Patient(1004);
	Patient pat5 = Patient(1005);
	Patient pat6 = Patient(1006);
	Patient pat7 = Patient(1007);
	Patient pat8 = Patient(1008);
	Patient pat9 = Patient(1009);
	Patient pat10 = Patient(1010);
	Patient pat11 = Patient(1011);
	Patient pat12 = Patient(1012);
	Patient pat13 = Patient(1013);
	Patient pat14 = Patient(1014);
	Patient pat15 = Patient(1015);
	Patient pat16 = Patient(1016);
	Patient pat17 = Patient(1017);
	Patient pat18 = Patient(1018);
	Patient pat19 = Patient(1019);
	Patient pat20 = Patient(1020);
	Patient pat21 = Patient(1021);
	Patient pat22 = Patient(1022);
	Patient pat23 = Patient(1023);
	Patient pat24 = Patient(1024);
	Patient pat25 = Patient(1025);

	room111.addNeigthborRoom(&room112);
	room111.addNeigthborRoom(&room114);
	room112.addNeigthborRoom(&room111);
	room112.addNeigthborRoom(&room113);
	room112.addNeigthborRoom(&room115);
	room113.addNeigthborRoom(&room115);
	room113.addNeigthborRoom(&room112);
	room113.addNeigthborRoom(&roomBl11);
	roomBl11.addNeigthborRoom(&room113);
	roomBl11.addNeigthborRoom(&room116);
	roomBl11.addNeigthborRoom(&roomBl12);
	room114.addNeigthborRoom(&room111);
	room114.addNeigthborRoom(&room115);
	room114.addNeigthborRoom(&roomDp1);
	room115.addNeigthborRoom(&room112);
	room115.addNeigthborRoom(&room114);
	room115.addNeigthborRoom(&room116);
	room116.addNeigthborRoom(&room113);
	room116.addNeigthborRoom(&room115);
	room116.addNeigthborRoom(&roomBl11);
	roomDp1.addNeigthborRoom(&room114);
	roomDp1.addNeigthborRoom(&room117);
	room117.addNeigthborRoom(&roomDp1);
	room117.addNeigthborRoom(&room120);
	room117.addNeigthborRoom(&room118);
	room118.addNeigthborRoom(&room117);
	room118.addNeigthborRoom(&room121);
	room118.addNeigthborRoom(&room119);
	room119.addNeigthborRoom(&room118);
	room119.addNeigthborRoom(&room122);
	room119.addNeigthborRoom(&roomBl12);
	roomBl12.addNeigthborRoom(&room119);
	roomBl12.addNeigthborRoom(&room122);
	roomBl12.addNeigthborRoom(&roomBl11);
	room120.addNeigthborRoom(&room117);
	room120.addNeigthborRoom(&room121);
	room121.addNeigthborRoom(&room120);
	room121.addNeigthborRoom(&room118);
	room121.addNeigthborRoom(&room122);
	room122.addNeigthborRoom(&room119);
	room122.addNeigthborRoom(&room121);
	room122.addNeigthborRoom(&roomBl12);

	pat1.setRoom(&room111);
	pat2.setRoom(&room111);
	pat3.setRoom(&room111);
	pat4.setRoom(&room112);
	pat5.setRoom(&room112);
	pat6.setRoom(&room113);
	pat7.setRoom(&room113);
	pat8.setRoom(&room114);
	pat9.setRoom(&room115);
	pat10.setRoom(&room115);
	pat11.setRoom(&room116);
	pat12.setRoom(&room117);
	pat13.setRoom(&room118);
	pat14.setRoom(&room119);
	pat15.setRoom(&room120);
	pat25.setRoom(&room121);
	pat16.setRoom(&room121);
	pat17.setRoom(&roomBl12);
	pat18.setRoom(&roomBl11);
	pat19.setRoom(&room116);
	pat20.setRoom(&room120);
	pat21.setRoom(&room121);
	pat22.setRoom(&room117);
	pat23.setRoom(&room115);
	pat24.setRoom(&room119);


	simulator.addSubject(&room111);
	simulator.addSubject(&room112);
	simulator.addSubject(&room113);
	simulator.addSubject(&room114);
	simulator.addSubject(&room115);
	simulator.addSubject(&room116);
	simulator.addSubject(&room117);
	simulator.addSubject(&room118);
	simulator.addSubject(&room119);
	simulator.addSubject(&room120);
	simulator.addSubject(&room121);
	simulator.addSubject(&room122);
	simulator.addSubject(&roomBl11);
	simulator.addSubject(&roomBl12);
	simulator.addSubject(&roomDp1);

	simulator.addSubject(&pat1);
	simulator.addSubject(&pat2);
	simulator.addSubject(&pat3);
	simulator.addSubject(&pat4);
	simulator.addSubject(&pat5);
	simulator.addSubject(&pat6);
	simulator.addSubject(&pat7);
	simulator.addSubject(&pat8);
	simulator.addSubject(&pat9);
	simulator.addSubject(&pat10);
	simulator.addSubject(&pat11);
	simulator.addSubject(&pat12);
	simulator.addSubject(&pat13);
	simulator.addSubject(&pat14);
	simulator.addSubject(&pat15);
	simulator.addSubject(&pat16);
	simulator.addSubject(&pat17);
	simulator.addSubject(&pat18);
	simulator.addSubject(&pat19);
	simulator.addSubject(&pat20);
	simulator.addSubject(&pat21);
	simulator.addSubject(&pat22);
	simulator.addSubject(&pat23);
	simulator.addSubject(&pat24);
	simulator.addSubject(&pat25);

	// Sensors :
	table.fillFromDB(&simulator, &simulatedSensorsID);
	sleep(2);

//	SensorSimulatorTempHumi sensorSimu1 = SensorSimulatorTempHumi(0x00100001, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu1);
//
//	SensorSimulatorTempHumi sensorSimu2 = SensorSimulatorTempHumi(0x00100002, &room2, 0, 40);
//	simulator.addSensor(&sensorSimu2);
//
//	SensorSimulatorTempHumi sensorSimu3 = SensorSimulatorTempHumi(0x00100003, &room3, 0, 40);
//	simulator.addSensor(&sensorSimu3);
//
//	SensorSimulatorTempHumi sensorSimu4 = SensorSimulatorTempHumi(0x00100004, &room4, 0, 40);
//	simulator.addSensor(&sensorSimu4);
//
//	SensorSimulatorTempHumi sensorSimu5 = SensorSimulatorTempHumi(0x00100005, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu5);
//
//	SensorSimulatorTempHumi sensorSimu6 = SensorSimulatorTempHumi(0x00100006, &room2, 0, 40);
//	simulator.addSensor(&sensorSimu6);
//
//	SensorSimulatorTempHumi sensorSimu7 = SensorSimulatorTempHumi(0x00100007, &room3, 0, 40);
//	simulator.addSensor(&sensorSimu7);
//
//	SensorSimulatorTempHumi sensorSimu8 = SensorSimulatorTempHumi(0x00100008, &room4, 0, 40);
//	simulator.addSensor(&sensorSimu8);
//
//	SensorSimulatorTempHumi sensorSimu9 = SensorSimulatorTempHumi(0x00100009, &room2, 0, 40);
//	simulator.addSensor(&sensorSimu9);
//
//	SensorSimulatorTempHumi sensorSimu10 = SensorSimulatorTempHumi(0x00100010, &room3, 0, 40);
//	simulator.addSensor(&sensorSimu10);
//
//	SensorSimulatorTempHumi sensorSimu11 = SensorSimulatorTempHumi(0x00100011, &room4, 0, 40);
//	simulator.addSensor(&sensorSimu11);
//
//	SensorSimulatorTempHumi sensorSimu12 = SensorSimulatorTempHumi(0x00100012, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu12);
//
//	SensorSimulatorTempHumi sensorSimu13 = SensorSimulatorTempHumi(0x00100013, &room1, 0, 40);
//	simulator.addSensor(&sensorSimu13);
//
//	SensorSimulatorTempHumi sensorSimu14 = SensorSimulatorTempHumi(0x00100014, &room2, 0, 40);
//	simulator.addSensor(&sensorSimu14);
//
//	SensorSimulatorTempHumi sensorSimu15 = SensorSimulatorTempHumi(0x00100015, &room3, 0, 40);
//	simulator.addSensor(&sensorSimu15);
//
//	simulator.addSensor(&sensorSimu1);
//	simulator.addSensor(&sensorSimu2);
//	simulator.addSensor(&sensorSimu3);
//	simulator.addSensor(&sensorSimu4);
//	simulator.addSensor(&sensorSimu5);
//	simulator.addSensor(&sensorSimu6);
//	simulator.addSensor(&sensorSimu7);
//	simulator.addSensor(&sensorSimu8);
//	simulator.addSensor(&sensorSimu9);
//	simulator.addSensor(&sensorSimu10);
//	simulator.addSensor(&sensorSimu11);
//	simulator.addSensor(&sensorSimu12);
//	simulator.addSensor(&sensorSimu13);
//	simulator.addSensor(&sensorSimu14);
//	simulator.addSensor(&sensorSimu15);
//
	simulator.openSocket(portSimulatedSensor);
	simulator.run();
//
//	table.add((EnOceanSensorAPI::SensorId)0x00100001, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100002, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100003, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100004, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100005, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100006, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100007, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100008, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x00100009, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000010, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000011, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000012, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000013, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000014, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//	table.add((EnOceanSensorAPI::SensorId)0x001000015, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempAndHumidSensor_EEP_07_04_01);
//
	EnOceanActuatorAirConditioning airCond = EnOceanActuatorAirConditioning(1, 10.0, 12, 0, 40);
	airCond.addSubject(&room111);
	airCond.addSubject(&room121);
	airCond.addSubject(&room118);
	airCond.addSubject(&room115);
	airCond.setStatus(true);
	
	EnOceanActuatorMusic ziq = EnOceanActuatorMusic(4288617991, 0);
	simulator.addActuator(&ziq);

	EventActuatorFire fire = EventActuatorFire(2, 5);
	fire.addSubject(&room113);

	simulator.addActuator(&airCond);
	simulator.addActuator(&fire);


// ----- ENOCEAN SENSORS

	//string adresseEnOcean = "134.214.105.28";

	//system("ssh -f -L 6543:134.214.105.28:5000 -N bplanche@iftpserv2.insa-lyon.fr");
	string adresseEnOcean = "127.0.0.1";
	int portEnOcean = 6543;

	table.add((EnOceanSensorAPI::SensorId)0x00893378, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseTempSensor_EEP_07_02_05);
	table.add((EnOceanSensorAPI::SensorId)0x0021CBE3, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseRockerSwitch_EEP_05_02_01);
	table.add((EnOceanSensorAPI::SensorId)0x0001B596, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseContactSensor_EEP_06_00_01);
	table.add((EnOceanSensorAPI::SensorId)0x0001B595, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseContactSensor_EEP_06_00_01);
	table.add((EnOceanSensorAPI::SensorId)0x00054A7F, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseLumAndOcc_EEP_07_08_01);

	blocking_queue<string> msgToSend = blocking_queue<string>();


// ----- SUNSPOT SENSORS

	//string adresseEnOcean = "134.214.105.28";

	//system("ssh -f -L 6543:134.214.59.17:5000 -N bplanche@iftpserv2.insa-lyon.fr")
	string adresseSunSpot = "127.0.0.1";
	int portSunSpot = 7080;

	table.add((EnOceanSensorAPI::SensorId)0x00005620, (EnOceanSensorAPI::EnOceanCallbackFunction)EnOceanSensorAPI::analyseSunSpot);


	ServerSettings serverSettings = ServerSettings(&table, &msgToSend, &msgToSendSimulator, &simulator);
	serverSettings.openSocket(1234);
	serverSettings.run();

	EnOceanAnalyser analyser = EnOceanAnalyser(&table, &msgQueue);
	analyser.run();

	EnOceanReceptor recepSimulator = EnOceanReceptor(&msgQueue, &msgToSendSimulator);
	recepSimulator.open(adresseSimulatedSensor.c_str(), portSimulatedSensor);
	recepSimulator.run();

	EnOceanReceptor recep = EnOceanReceptor(&msgQueue, &msgToSend);
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
