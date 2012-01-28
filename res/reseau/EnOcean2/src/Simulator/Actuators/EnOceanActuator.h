
/*************************************************************************
                           EnOceanActuator  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanActuator> (EnOceanActuator.h file) --------

#ifndef ENOCEAN_ACTUATOR_H_
#define ENOCEAN_ACTUATOR_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "Actuator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating EnOCean actuator, which can edit the value of some EnOcean sensors.
//
//------------------------------------------------------------------------

class EnOceanActuator : public Actuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setStatus(bool status);
	bool getStatus();

	void setEnergeticCostPerSecond(float e);
	float getEnergeticCostPerSecond();
	virtual float update() = 0;


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanActuator(int id, float enerCoef);
	virtual ~EnOceanActuator();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float energeticCostPerSecond;		// cost when on
	bool on;						// on or off

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEAN_ACTUATOR_H_ */
