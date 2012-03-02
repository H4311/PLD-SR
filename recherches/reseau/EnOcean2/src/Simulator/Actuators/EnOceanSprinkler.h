/*************************************************************************
                           EnOceanSprinkler  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanSprinkler> (EnOceanSprinkler.h file) --------

#ifndef ENOCEANSPRINKLER_H_
#define ENOCEANSPRINKLER_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <vector>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"
#include "EventActuatorFire.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating aeration, which can edit the value of some EnOcean sensors (CO2 level).
//
//------------------------------------------------------------------------

class EnOceanSprinkler : public EnOceanActuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setDebit(float e);
	float getDebit();

	void setFire(EventActuatorFire*f);
	EventActuatorFire* getFire();

	float update();
	void set(enocean_data_structure *frame);


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanSprinkler(int id, float enerCoef, float power, float powerMin, float powerMax);
	virtual ~EnOceanSprinkler();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float debit;		// Chosen power
	float debitMin;
	float debitMax;
	EventActuatorFire* fire;

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANSPRINKLER_H_ */
