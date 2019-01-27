#pragma once

#include "EnvObject.h"

class Food : public EnvObject
{
	double remainingEnergy;

public:
	Food(double X, double Y, double amount);
	~Food();

	double TryEat(double amount);
};

