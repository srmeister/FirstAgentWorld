// Koerper.cpp: Implementierung der Klasse CKoerper.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Agent.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void Agent::EvaluateNet()
{
}

void Agent::TakeAction()
{
}

Agent::Agent(double dX, double dY, double dZ, double energy, UINT uiID)
{
	nextAgent  = NULL;

	m_PktPos.SetPkt(dX, dY, dZ);
	m_PktFRichtung.SetPkt(0, 0, 0);
	m_Energy = energy;
	m_uiID = uiID;
}

void Agent::Tick()
{
	EvaluateNet();

	TakeAction();

}