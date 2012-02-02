/*************************************************************************
                           EnOceanActuatorLight  -  description
                             -------------------
    Creation             : 29 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanActuatorLight> (EnOceanActuatorLight.h file) --------

#ifndef ENOCEANACTUATORLAMP_H_
#define ENOCEANACTUATORLAMP_H_

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

class EnOceanActuatorLight : public EnOceanActuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setIlluminance(float e);
	float getIlluminance();

	float update();
	void set(enocean_data_structure *frame);


//------------------------------------------------- Static public Methods
	static enocean_data_structure toFrame(int id, bool on, float lum, float luxMin, float luxMax);

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanActuatorLight(int id, float enerCoef, float temp, float luxMin, float luxMax);
	virtual ~EnOceanActuatorLight();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float illuminance;
	float luxMin;
	float luxMax;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANACTUATORLAMP_H_ */
