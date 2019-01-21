#pragma once
#include "Environment.h"

class Viewport
{
	Environment *m_Welt;

	int m_SizeX, m_SizeY;
public:
	Viewport(Environment *welt);
	~Viewport();
	void SetDrawSize(int x, int y);
	void Darstellen(CClientDC* A);
};

