/*
 * Subject.cpp
 *
 *  Created on: 9 févr. 2012
 *      Author: bill
 */

#include "Subject.h"


int Subject::getId() {
	return id;
}

float Subject::getTemperature() {
	float r;
	pthread_mutex_lock(&mutex);
	r = temperature;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Subject::setTemperature(float v) {
	pthread_mutex_lock(&mutex);
	temperature = v;
	pthread_mutex_unlock(&mutex);
}

float Subject::getMovement() {
	float r;
	pthread_mutex_lock(&mutex);
	r = movement;
	pthread_mutex_unlock(&mutex);
	return r;
}

void Subject::setMovement(float v) {
	pthread_mutex_lock(&mutex);
	movement = v;
	pthread_mutex_unlock(&mutex);
}

void Subject::setClick(int v) {
	pthread_mutex_lock(&mutex);
	click = v;
	pthread_mutex_unlock(&mutex);
}

int Subject::getClick() {
	int r;
	pthread_mutex_lock(&mutex);
	r = click;
	pthread_mutex_unlock(&mutex);
	return r;
}

Subject::Subject(int i, float temp, float mov) :
		id(i),
		temperature(temp),
		movement(mov),
		click(0){
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&mutex, NULL);
}

Subject::~Subject() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mutex);
}
