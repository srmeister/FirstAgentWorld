// Punkt.cpp: Implementierung der Klasse CPunkt.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include <math.h>
#include "Punkt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CPunkt::CPunkt()
{
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
}

CPunkt::CPunkt(double dX, double dY, double dZ)
{
	m_dX = dX;
	m_dY = dY;
	m_dZ = dZ;
}

double CPunkt::GetAbstand(const CPunkt &ZielPkt)
{
	double DeltadX,DeltadY,DeltadZ;

	DeltadX = GetDelta(m_dX,ZielPkt.m_dX);
	DeltadY = GetDelta(m_dY,ZielPkt.m_dY);
	DeltadZ = GetDelta(m_dZ,ZielPkt.m_dZ);

	return sqrt(DeltadX * DeltadX + DeltadY * DeltadY + DeltadZ * DeltadZ);
}

double CPunkt::GetRelativLaenge()
{
	CPunkt StartPkt; //ein 0,0,0 Punkt

	return GetAbstand(StartPkt);
}

void CPunkt::PrintPkt(HWND hWnd)
{
	CString Tmp1,Tmp2,Tmp3;

	Tmp1.Format("X = %15.4lf\n",m_dX);
	Tmp2.Format("Y = %15.4lf\n",m_dY);
	Tmp3.Format("Z = %15.4lf\n",m_dZ);

	Tmp1 += (Tmp2 + Tmp3);

	MessageBox(hWnd,Tmp1,"CPunkt",0);
}