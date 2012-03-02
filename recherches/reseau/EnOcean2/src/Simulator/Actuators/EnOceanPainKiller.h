/*************************************************************************
                           EnOceanPainKiller  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EnOceanPainKiller> (EnOceanPainKiller.h file) --------

#ifndef ENOCEANPAINKILLER_H_
#define ENOCEANPAINKILLER_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating aeration, which can edit the value of some EnOcean sensors (CO2 level).
//
//------------------------------------------------------------------------

class EnOceanPainKiller : public EnOceanActuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setDebit(float e);
	float getDebit();

	float update();
	void set(enocean_data_structure *frame);


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanPainKiller(int id, float enerCoef, float power, float powerMin, float powerMax);
	virtual ~EnOceanPainKiller();

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

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANPAINKILLER_H_ */
