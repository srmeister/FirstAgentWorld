#include "stdafx.h"
#include "WeltDrawer.h"

WeltDrawer::WeltDrawer(CWelt *welt)
{
	m_Welt = welt;
	m_SizeX = 200;
	m_SizeY = 300;
}

WeltDrawer::~WeltDrawer()
{
}

void WeltDrawer::SetDrawSize(int x, int y)
{
	m_SizeX = x;
	m_SizeY = y;
}

void WeltDrawer::Darstellen(CClientDC* A)
{
	double factorx, factory;

	factorx = (double)m_SizeX / m_Welt->GetDimX();
	factory = (double)m_SizeY / m_Welt->GetDimY();
	
	CKoerper *koerper;
	m_Welt->LLReset();

	CBrush Hintergund;
	Hintergund.CreateSolidBrush(RGB(255, 255, 255));
	A->SelectObject(Hintergund);
	A->Rectangle(6, 6, m_SizeX + 14, m_SizeY + 14);

	CBrush Kugel;

	Kugel.CreateSolidBrush(RGB(224, 224, 224));
	A->SelectObject(Kugel);

	while (koerper = m_Welt->LLGetNext())
	{
		int x = (int)(koerper->GetPosX()*factorx);
		int y = (int)(koerper->GetPosY()*factory);

		A->Ellipse(8 + x, m_SizeY + 8 - y, 13 + x, m_SizeY + 13 - y);
	}
}