/*************************************************************************
                           SensorSimulatorContact  -  description
                             -------------------
    Creation             : 09 Feb. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulatorContact> (SensorSimulatorContact.h file) --------

#ifndef ENOCEANSIMULATORCONTACT_H_
#define ENOCEANSIMULATORCONTACT_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------

class SensorSimulatorContact : public SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

	void update();

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulatorContact(int id, Subject* r);
	virtual ~SensorSimulatorContact();

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


#endif /* ENOCEANSIMULATORCONTACT_H_ */
