/*
 * Room.cpp
 *
 *  Created on: 1 févr. 2012
 *      Author: bill
 */

#include "Room.h"


void Room::addNeigthborRoom(Room* r) {
	pthread_mutex_lock(&mutex);
	neigthborRooms.push_back(r);
	pthread_mutex_unlock(&mutex);
}

vector<Room*> Room::getNeigthborRooms() {
	vector<Room*> r;
	pthread_mutex_lock(&mutex);
	r = neigthborRooms;
	pthread_mutex_unlock(&mutex);
	return r;
}

float Room::getHumidity() {
	float r;
	pthread_mutex_lock(&mutex);
	r = humidity;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Room::setHumidity(float v) {
	pthread_mutex_lock(&mutex);
	humidity = v;
	pthread_mutex_unlock(&mutex);
}

void Room::setCO2Level(float v) {
	pthread_mutex_lock(&mutex);
	co2Level = v;
	pthread_mutex_unlock(&mutex);
}

float Room::getCO2Level() {
	float r;
	pthread_mutex_lock(&mutex);
	r = co2Level;
	pthread_mutex_unlock(&mutex);
	return r;
}

float Room::getLuminosity() {
	float r;
	pthread_mutex_lock(&mutex);
	r = luminosity;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Room::setLuminosity(float v) {
	pthread_mutex_lock(&mutex);
	luminosity = v;
	pthread_mutex_unlock(&mutex);
}

bool Room::getPIRStatus() {
	float r;
	pthread_mutex_lock(&mutex);
	r = pirStatus;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Room::setPIRStatus(bool v) {
	pthread_mutex_lock(&mutex);
	pirStatus = v;
	pthread_mutex_unlock(&mutex);
}

bool Room::getOccupancy() {
	float r;
	pthread_mutex_lock(&mutex);
	r = occupancy;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Room::setOccupancy(bool v) {
	pthread_mutex_lock(&mutex);
	occupancy = v;
	pthread_mutex_unlock(&mutex);
}

Room::Room(int i) :
		Subject(i, 23, 0),
		humidity(30),
		co2Level(400),
		luminosity(1000),
		pirStatus(false),
		occupancy(false) {
	// TODO Auto-generated constructor stub
}

Room::~Room() {
}
