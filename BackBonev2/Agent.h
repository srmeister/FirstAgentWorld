// Koerper.h: Schnittstelle für die Klasse CKoerper.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Punkt.h"

class Agent
{
	friend class CWelt;
private:
	//Eigenschaften
	double m_Energy;
	
	//Geschwindigkeits- und Richtungsvektoren (Betrag == V)
	CPunkt m_PktFRichtung;
	CPunkt m_PktPos;

	//Identifikation
	UINT m_uiID;
	void EvaluateNet();
	void TakeAction();
public:

	// Konstruktor, Destruktor
	Agent(double dX, double dY, double dZ, double energy, UINT uiID);

	inline ~Agent() {}
	
	// Do Stuff
	void Tick();

	// Eigenschaften
	inline double GetEnergy() {return m_Energy;}
	inline void SetEnergy(double energy){ m_Energy = energy; }

	inline CPunkt GetPos() { return m_PktPos; }

	inline UINT GetID() {return m_uiID;}
	// Linked List stuff
	Agent *nextAgent;
};
