/*************************************************************************
                           SensorSimulatorCO2  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulatorCO2> (SensorSimulatorCO2.h file) --------

#ifndef ENOCEANSIMULATORCO2_H_
#define ENOCEANSIMULATORCO2_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------

class SensorSimulatorCO2 : public SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	float getCo2Level();
	void update();

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulatorCO2(int id, Subject* r, float ppmMin, float ppMax);
	virtual ~SensorSimulatorCO2();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float ppmMin;
	float ppmMax;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANSIMULATORCO2_H_ */
