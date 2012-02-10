/*************************************************************************
                           EventActuatorAwakening  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EventActuatorAwakening> (EventActuatorAwakening.h file) --------

#ifndef EVENTACTUATORAWAKENING_H_
#define EVENTACTUATORAWAKENING_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <vector>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"
#include "../Model/Patient.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating aeration, which can edit the value of some EnOcean sensors (CO2 level).
//
//------------------------------------------------------------------------

class EventActuatorAwakening : public Actuator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void setPower(float e);
	float getPower();

	float update();


//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	EventActuatorAwakening(int id, float power);
	virtual ~EventActuatorAwakening();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

	float power;		// Chosen power
private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* EVENTACTUATORAWAKENING_H_ */
