#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct Color
{
public:
	Color();
	Color(float red, float green, float blue, float alpha = 1.f);
	Color(const Color& col);

	float operator[](int index);
	Color operator*(float value);
	Color operator*(float value) const;
	void operator*=(float value);
	bool equals(const Color& col) const;

	float r;
	float g;
	float b;
	float a;
};

#endif