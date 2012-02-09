/*
 * Subject.h
 *
 *  Created on: 9 févr. 2012
 *      Author: bill
 */

#ifndef SUBJECT_H_
#define SUBJECT_H_

using namespace std;
#include <pthread.h>
#include <vector>

class Subject {
public:
	int getId();

	float getTemperature();
	void setTemperature(float v);

	float getMovement();
	void setMovement(float v);

	Subject(int i, float temp, float mov);
	virtual ~Subject();

protected:
	int id;
	float temperature;
	float movement;


	pthread_mutex_t mutex;
};

#endif /* SUBJECT_H_ */
