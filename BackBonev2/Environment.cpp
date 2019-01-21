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

Environment::Environment()
{
	laufZeit = 0;

	m_SizeX=100;
	m_SizeY=100;
	m_SizeZ=100;

}
Environment::Environment(double X, double Y, double Z)
{
	laufZeit = 0;

	m_SizeX=X;
	m_SizeY=Y;
	m_SizeZ=Z;
}

Environment::~Environment()
{

}


void Environment::AddKoerper(double x, double y, double Energy)
{
	agentList.AppendAgent( new Agent(x, y, 0, Energy, GetCount()));
}

Agent* Environment::GetKoerper(int Nr)
{
	Agent *agent = agentList.ResetConductor();
	for (int i = 0; i < Nr && agent != NULL; i++)
	{
		agent = agentList.GetNextAgent();
	}
	return agent;
}

void Environment::Update()
{
	laufZeit++;

	Agent *agent = agentList.ResetConductor();
	do
	{
		agent->Tick();
	} while ((agent = agentList.GetNextAgent()) != NULL);
}

int Environment::GetCount()
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

double Environment::GetDimX()
{
	return m_SizeX;
}

double Environment::GetDimY()
{
	return m_SizeY;
}

double Environment::GetDimZ()
{
	return m_SizeZ;
}

void Environment::SetDim(double X,double Y,double Z)
{
	m_SizeX=X;
	m_SizeY=Y;
	m_SizeZ=Z;
}