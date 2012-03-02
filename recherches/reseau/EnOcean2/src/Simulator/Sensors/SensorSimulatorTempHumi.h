
/*************************************************************************
                           SensorSimulatorTempHumi  -  description
                             -------------------
    Creation             : 08 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulatorTempHumi> (SensorSimulatorTempHumi.h file) --------

#ifndef SENSORSIMULATORTEMPHUMI_H_
#define SENSORSIMULATORTEMPHUMI_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------

class SensorSimulatorTempHumi : public SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

//	float getTemperature();
//	void setTemperature(float t);
//	float getHumidity();
//	void setHumidity(float h);

	void update();

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulatorTempHumi(int id, Subject* r, float tMin, float tMax);
	virtual ~SensorSimulatorTempHumi();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

//	float temperature;
	float tempMin;
	float tempMax;
//	float humidity;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* SENSORSIMULATORTEMPHUMI_H_ */
