/*************************************************************************
                           SensorSimulatorLumAndOcc  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//------- Definition - <SensorSimulatorLumAndOcc> (SensorSimulatorLumAndOcc.h file) --------

#ifndef ENOCEANSIMULATORLUMANDOCC_H_
#define ENOCEANSIMULATORLUMANDOCC_H_

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
//------------------------------------------------------ Personnal Include
#include "SensorSimulator.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Description :
//		Analyses the frame provided by the server, and extracts the informations from them, for the chosen sensors.
//
//------------------------------------------------------------------------

class SensorSimulatorLumAndOcc : public SensorSimulator
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------------------------------------- Public Constants

//--------------------------------------------------------- Public Methods

//	float getIlluminance();
//	void setIlluminance(float i);
//	float getVoltage();
//	void setVoltage(float v);
//	bool getPIRStatus();
//	void setPIRStatus(bool h);
//	bool getOccupancy();
//	void setOccupancy(bool o);

	void update();
//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators

//-------------------------------------------------- Builder / Destructor

	SensorSimulatorLumAndOcc(int id, Room* r, float minLum, float maxLum, float minV, float maxV);
	virtual ~SensorSimulatorLumAndOcc();

//---------------------------------------------------------------- PRIVATE

protected:
//------------------------------------------------------ Protected Methods

private:
//----------------------------------------------------- Protected Methods

protected:
//-------------------------------------------------- Protected Attributes

//	float illuminance;
//	float voltage;
//	bool pirStatus;
//	bool occupancy;
	float minLum;
	float maxLum;
	float minV;
	float maxV;


private:
//----------------------------------------------------- Private Attributes

//--------------------------------------------------------- Friend Classes

//-------------------------------------------------------- Private Classes

//---------------------------------------------------------- Private Types

};

//------------------------------ Other definition, depending on this class


#endif /* ENOCEANSIMULATORLUMANDOCC_H_ */
