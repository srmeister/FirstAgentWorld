#pragma once

#include "Point.h"

class EnvObject
{
public:
	EnvObject();
	~EnvObject();

	inline Point GetPos() { return m_PktPos; }

protected:
	double m_Energy;

	//Geschwindigkeits- und Richtungsvektoren (Betrag == V)
	Point m_PktFRichtung;
	Point m_PktPos;

};

