#include "Math.h"


const float Math::PI = 3.14159f;

std::mt19937 Math::generator;
std::uniform_int_distribution<> Math::integerDistribution;
std::uniform_real_distribution<> Math::realDistribution;
bool Math::initialized = false;

int Math::Rand()
{
	return integerDistribution(generator);
}

double Math::RandRange()
{
	return realDistribution(generator);
}

void Math::Initialize()
{
	if (!initialized)
	{
		std::random_device rd;
		generator = std::mt19937(rd());
		integerDistribution = std::uniform_int_distribution<>(0, INT_MAX);
		realDistribution = std::uniform_real_distribution<>(0.0, 1.0);
		initialized = true;
	}
}
