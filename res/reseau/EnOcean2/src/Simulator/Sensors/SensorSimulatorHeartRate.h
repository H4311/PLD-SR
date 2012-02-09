/*************************************************************************
                           SensorSimulatorHeartRate  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulatorHeartRate> (SensorSimulatorHeartRate.h file) --------

#ifndef ENOCEANSIMULATORHEARTRATE_H_
#define ENOCEANSIMULATORHEARTRATE_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------

class SensorSimulatorHeartRate : public SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void update();

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulatorHeartRate(int id, Subject* r, float rateMin, float rateMax);
	virtual ~SensorSimulatorHeartRate();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float rateMin;
	float rateMax;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANSIMULATORHEARTRATE_H_ */
