#include "stdafx.h"
#include "Viewport.h"

Viewport::Viewport(CWelt *welt)
{
	m_Welt = welt;
	m_SizeX = 200;
	m_SizeY = 300;
}

Viewport::~Viewport()
{
}

void Viewport::SetDrawSize(int x, int y)
{
	m_SizeX = x;
	m_SizeY = y;
}

void Viewport::Darstellen(CClientDC* A)
{
	double factorx, factory;

	factorx = (double)m_SizeX / m_Welt->GetDimX();
	factory = (double)m_SizeY / m_Welt->GetDimY();
	
	CBrush Hintergund;
	Hintergund.CreateSolidBrush(RGB(255, 255, 255));
	A->SelectObject(Hintergund);
	A->Rectangle(6, 6, m_SizeX + 14, m_SizeY + 14);

	CBrush Kugel;

	Kugel.CreateSolidBrush(RGB(224, 224, 224));
	A->SelectObject(Kugel);

	Agent *agent = m_Welt->agentList.ResetConductor();
	while (agent != NULL)
	{
		int x = (int)(agent->GetPos().GetX() * factorx);
		int y = (int)(agent->GetPos().GetY() * factory);

		A->Ellipse(8 + x, m_SizeY + 8 - y, 13 + x, m_SizeY + 13 - y);

		agent = m_Welt->agentList.GetNextAgent();
	}
}