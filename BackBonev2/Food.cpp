#include "stdafx.h"
#include "Food.h"


Food::Food(double X, double Y, double amount)
{
	m_PktPos.SetPkt(X, Y, 0);
	m_PktFRichtung.SetPkt(0, 0, 0);
	remainingEnergy = amount;
}

Food::~Food()
{
}

double Food::TryEat(double amount)
{
	if (amount < remainingEnergy)
	{
		remainingEnergy = remainingEnergy - amount;
		return amount;
	}
	else
	{
		double tmp = remainingEnergy;
		remainingEnergy = 0;
		return tmp;
	}
}
