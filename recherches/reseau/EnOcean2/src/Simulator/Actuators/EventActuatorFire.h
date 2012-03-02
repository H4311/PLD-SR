/*************************************************************************
                           EventActuatorFire  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <EventActuatorFire> (EventActuatorFire.h file) --------

#ifndef EVENTACTUATORFIRE_H_
#define EVENTACTUATORFIRE_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <vector>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuator.h"
#include "../Model/Room.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Element simulating aeration, which can edit the value of some EnOcean sensors (CO2 level).
//
//------------------------------------------------------------------------

class EventActuatorFire : public Actuator
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

	EventActuatorFire(int id, float power);
	virtual ~EventActuatorFire();

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


#endif /* EVENTACTUATORFIRE_H_ */
