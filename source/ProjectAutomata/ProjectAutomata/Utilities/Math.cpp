#include "Math.h"


const float Math::PI = 3.14159;

std::mt19937 Math::generator;
bool Math::initialized = false;

int Math::Rand()
{
	return Rand(0, INT_MAX);
}

int Math::Rand(int minVal, int maxVal)
{
	std::uniform_int_distribution<> integerDistribution(minVal, maxVal);
	return integerDistribution(Math::generator);
}

double Math::RandRange()
{
	return RandRange(0.f, 1.f);
}

double Math::RandRange(double minVal, double maxVal)
{
	std::uniform_real_distribution<> realDistribution(minVal, maxVal);
	return realDistribution(generator);
}

void Math::Initialize()
{
	if (!initialized)
	{
		std::random_device rd;
		generator = std::mt19937(rd());
		initialized = true;
	}
}
