#ifndef MATH_H
#define MATH_H

#include <random>

class Math
{
public:
	static const float PI;

	static int Rand();
	static double RandRange();

	static void Initialize();

private:
	static bool initialized;
	static std::mt19937 generator;
	static std::uniform_int_distribution<> integerDistribution;
	static std::uniform_real_distribution<> realDistribution;
};

#endif