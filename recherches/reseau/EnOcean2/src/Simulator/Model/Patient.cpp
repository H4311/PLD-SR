/*
 * Patient.cpp
 *
 *  Created on: 9 févr. 2012
 *      Author: bill
 */

#include "Patient.h"

Room* Patient::getRoom() {
	Room* r;
	pthread_mutex_lock(&mutex);
	r = room;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Patient::setRoom(Room* v) {
	pthread_mutex_lock(&mutex);
	room = v;
	pthread_mutex_unlock(&mutex);
}

bool Patient::getStatus() {
	bool r;
	pthread_mutex_lock(&mutex);
	r = alive;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Patient::setStatus(bool v) {
	pthread_mutex_lock(&mutex);
	alive = v;
	pthread_mutex_unlock(&mutex);
}

float Patient::getHeartRate() {
	float r;
	pthread_mutex_lock(&mutex);
	r = heartRate;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Patient::setHeartRate(float v) {
	pthread_mutex_lock(&mutex);
	heartRate = v;
	pthread_mutex_unlock(&mutex);
}

Patient::Patient(int i) :
		Subject(i, 37.6, 0),
		room(NULL),
		alive(true),
		heartRate(70) {
	// TODO Auto-generated constructor stub
}

Patient::~Patient() {
}

