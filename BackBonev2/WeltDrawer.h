#pragma once
#include "Welt.h"

class WeltDrawer
{
	CWelt *m_Welt;

	int m_SizeX, m_SizeY;
public:
	WeltDrawer(CWelt *welt);
	~WeltDrawer();
	void SetDrawSize(int x, int y);
	void Darstellen(CClientDC* A);
};

