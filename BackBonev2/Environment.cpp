// Welt.cpp: Implementierung der Klasse CWelt.
//
//////////////////////////////////////////////////////////////////////

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

	foodVector.reserve(1024);
	agentVector.reserve(128);
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


void Environment::AddAgent(double x, double y, double Energy)
{
	agentVector.push_back(Agent(x, y, Energy, GetAgentCount()));
}

Agent* Environment::GetFirstAgent()
{
	if(agentVector.size()>0)
		return &agentVector[0];
	else
		return NULL;
}

void Environment::Update()
{
	laufZeit++;
	for (size_t i = 0; i < agentVector.size(); i++)
	{
		agentVector[i].Tick();
	}
}

int Environment::GetAgentCount()
{

	return agentVector.size();
}

Food * Environment::GetFirstFood()
{
	if(foodVector.size()>0)
		return &foodVector[0];
	else
		return NULL;
}

int Environment::GetFoodCount()
{
	return foodVector.size();
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

void Environment::PlaceFood(int amount)
{
	std::default_random_engine gen;
	std::uniform_real_distribution<double> disx(0, m_SizeX);
	std::uniform_real_distribution<double> disy(0, m_SizeY);

	for (int i = 0; i < amount; i++)
	{
		foodVector.push_back(Food(disx(gen),disy(gen),10));
	}

}
