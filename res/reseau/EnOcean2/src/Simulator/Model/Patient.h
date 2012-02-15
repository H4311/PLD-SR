/*
 * Patient.h
 *
 *  Created on: 9 févr. 2012
 *      Author: bill
 */

#ifndef PATIENT_H_
#define PATIENT_H_

#include "Subject.h"
#include "Room.h"

class Patient : public Subject {
public:
public:

	Room* getRoom();
	void setRoom(Room* v);
	bool getStatus();
	void setStatus(bool v);
	float getHeartRate();
	void setHeartRate(float v);

	Patient(int id);
	virtual ~Patient();

protected:
	Room* room;
	bool alive;
	float heartRate;
};

#endif /* PATIENT_H_ */
