/*
 * EnOceanSensor.h
 *
 *  Created on: 8 janv. 2012
 *      Author: bill
 */

#ifndef ENOCEANSENSOR_H_
#define ENOCEANSENSOR_H_

#include "../enoceanlib/EnOceanProtocol.h"

class EnOceanSensor {
public:
	EnOceanSensor(int i);
	virtual ~EnOceanSensor();

protected:
	int id;

};

#endif /* ENOCEANSENSOR_H_ */
