#include "stdafx.h"
#include "Viewport.h"

Viewport::Viewport(Environment *welt)
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

void Viewport::Display(CClientDC* A)
{
	double factorx, factory;

	factorx = (double)m_SizeX / m_Welt->GetDimX();
	factory = (double)m_SizeY / m_Welt->GetDimY();
	
	CBrush Background;
	Background.CreateSolidBrush(RGB(255, 255, 255));
	A->SelectObject(Background);
	A->Rectangle(6, 6, m_SizeX + 14, m_SizeY + 14);


	Agent *agent = m_Welt->GetFirstAgent();
	if (agent != NULL)
	{
		CBrush AgentCircle;
		AgentCircle.CreateSolidBrush(RGB(124, 124, 124));
		A->SelectObject(AgentCircle);
		int agentcount = m_Welt->GetAgentCount();
		for (int i = 0; i < agentcount; i++)
		{
			int x = (int)(agent[i].GetPos().GetX() * factorx);
			int y = (int)(agent[i].GetPos().GetY() * factory);

			A->Ellipse(8 + x, m_SizeY + 8 - y, 13 + x, m_SizeY + 13 - y);
		}
	}


	Food *food = m_Welt->GetFirstFood();
	if (food != NULL)
	{
		CBrush FoodCircle;
		FoodCircle.CreateSolidBrush(RGB(255, 255, 50));
		A->SelectObject(FoodCircle);

		int foodcount = m_Welt->GetFoodCount();
		for (int i = 0; i < foodcount; i++)
		{
			int x = (int)(food[i].GetPos().GetX() * factorx);
			int y = (int)(food[i].GetPos().GetY() * factory);

			A->Ellipse(8 + x, m_SizeY + 8 - y, 13 + x, m_SizeY + 13 - y);
		}
	}
}