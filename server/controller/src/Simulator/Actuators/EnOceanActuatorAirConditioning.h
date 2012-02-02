
/*************************************************************************
                           EnOceanActuatorAirConditioning  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanActuatorAirConditioning> (EnOceanActuatorAirConditioning.h file) --------

#ifndef ENOCEAN_ACTUATOR_AIRCONDITIONING_H_
#define ENOCEAN_ACTUATOR_AIRCONDITIONING_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <vector>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating air conditioning, which can edit the value of some EnOcean sensors (Temp & Humi).
//
//------------------------------------------------------------------------

class EnOceanActuatorAirConditioning : public EnOceanActuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setTemperature(float e);
	float getTemperature();

	float update();
	void set(enocean_data_structure *frame);


//------------------------------------------------- Static public Methods
	static enocean_data_structure toFrame(int id, bool on, float temp, float tempMin, float tempMax);

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanActuatorAirConditioning(int id, float enerCoef, float temp, float tempMin, float tempMax);
	virtual ~EnOceanActuatorAirConditioning();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float temperature;		// Chosen temperature
	float tempMin;
	float tempMax;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEAN_ACTUATOR_AIRCONDITIONING_H_ */
