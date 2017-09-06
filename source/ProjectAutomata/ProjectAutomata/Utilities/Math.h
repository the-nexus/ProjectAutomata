#ifndef MATH_H
#define MATH_H

#include <random>

class Math
{
public:
	static const float PI;

	static int Rand();
	static int Rand(int minVal, int maxVal);
	static double RandRange();
	static double RandRange(double minVal, double maxVal);

	static void Initialize();

private:
	static bool initialized;
	static std::mt19937 generator;
};

#endif