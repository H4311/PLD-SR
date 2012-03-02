/*************************************************************************
                           EnOceanActuatorMusic  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Thibaut PATEL (TPL)
*************************************************************************/

//------- Definition - <EnOceanActuatorMusic> (EnOceanActuatorMusic.h file) --------

#ifndef EnOceanActuatorMusic_H_
#define EnOceanActuatorMusic_H_

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
//		Element simulating aeration, which can edit the value of some EnOcean sensors (CO2 level).
//
//------------------------------------------------------------------------

class EnOceanActuatorMusic : public EnOceanActuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setPower(float e);
	float getPower();

	float update();
	void set(enocean_data_structure *frame);


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EnOceanActuatorMusic(int id, float enerCoef);
	virtual ~EnOceanActuatorMusic();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* EnOceanActuatorMusic_H_ */
