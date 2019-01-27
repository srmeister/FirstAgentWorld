// Koerper.h: Schnittstelle für die Klasse CKoerper.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "EnvObject.h"
#include "deepnn/BackProp.H"

class Agent : public EnvObject
{
private:
	//Eigenschaften
	

	//Identifikation
	UINT m_uiID;
	void EvaluateNet();
	void TakeAction();

	// Creating the net
	CBackProp *bp;

public:

	// Konstruktor, Destruktor
	Agent(double X, double Y, double energy, UINT uiID);

	inline ~Agent() {}
	
	// Do Stuff
	void Tick();

	// Eigenschaften
	inline double GetEnergy() {return m_Energy;}
	inline void SetEnergy(double energy){ m_Energy = energy; }


	inline UINT GetID() {return m_uiID;}
};
