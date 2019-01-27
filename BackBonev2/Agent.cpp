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

Agent::Agent(double X, double Y, double energy, UINT uiID)
{
	m_PktPos.SetPkt(X, Y, 0);
	m_PktFRichtung.SetPkt(0, 0, 0);
	m_Energy = energy;
	m_uiID = uiID;

	// Creating the net
	int lSz[3] = {4,4,4};
	double beta = 0.0005, alpha = 0.2;

	bp = new CBackProp(3, lSz, beta, alpha, true);
}

void Agent::Tick()
{
	EvaluateNet();

	TakeAction();

}