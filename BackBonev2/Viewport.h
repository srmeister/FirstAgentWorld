#pragma once
#include "Environment.h"

class Viewport
{
	CWelt *m_Welt;

	int m_SizeX, m_SizeY;
public:
	Viewport(CWelt *welt);
	~Viewport();
	void SetDrawSize(int x, int y);
	void Darstellen(CClientDC* A);
};

