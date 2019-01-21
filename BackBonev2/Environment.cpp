// Welt.cpp: Implementierung der Klasse CWelt.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Environment.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CWelt::CWelt()
{
	laufZeit = 0;

	m_SizeX=100;
	m_SizeY=100;
	m_SizeZ=100;

}
CWelt::CWelt(double X, double Y, double Z)
{
	laufZeit = 0;

	m_SizeX=X;
	m_SizeY=Y;
	m_SizeZ=Z;
}

CWelt::~CWelt()
{

}


void CWelt::AddKoerper(double x, double y, double Energy)
{
	agentList.AppendAgent( new Agent(x, y, 0, Energy, GetCount()));
}

Agent* CWelt::GetKoerper(int Nr)
{
	Agent *agent = agentList.ResetConductor();
	for (int i = 0; i < Nr && agent != NULL; i++)
	{
		agent = agentList.GetNextAgent();
	}
	return agent;
}

void CWelt::Update()
{
	laufZeit++;

	Agent *agent = agentList.ResetConductor();
	do
	{
		agent->Tick();
	} while ((agent = agentList.GetNextAgent()) != NULL);
}

int CWelt::GetCount()
{
	int i=0;
	if(agentList.ResetConductor() == NULL) return 0;
	else i++;
	while (agentList.GetNextAgent() != NULL)
	{
		i++;
	};
	return i;
}

double CWelt::GetDimX()
{
	return m_SizeX;
}

double CWelt::GetDimY()
{
	return m_SizeY;
}

double CWelt::GetDimZ()
{
	return m_SizeZ;
}

void CWelt::SetDim(double X,double Y,double Z)
{
	m_SizeX=X;
	m_SizeY=Y;
	m_SizeZ=Z;
}