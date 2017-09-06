#include "Color.h"

/* -----------------------------------------
 *		Construction / Destruction
 * -----------------------------------------
 */

Color::Color()
{
	r = 1.f;	//Red
	g = 1.f;	//Green
	b = 1.f;	//Blue
	a = 1.f;	//Alpha
}

Color::Color(float red, float green, float blue, float alpha)
{
	r = red;		//Red
	g = green;		//Green
	b = blue;		//Blue
	a = alpha;		//Alpha
}

Color::Color(const Color& col)
{
	r = col.r;	//Red
	g = col.g;	//Green
	b = col.b;	//Blue
	a = col.a;	//Alpha
}

/* -----------------------------------------
 *				Other methods
 * -----------------------------------------
 */

float Color::operator[](int index)
{
	float result = -1.f;
	switch (index)
	{
	case 0:
		result = r;
		break;

	case 1:
		result = g;
		break;

	case 2:
		result = b;
		break;

	case 3:
		result = a;
		break;

	default:
		break;
	}
	return result;
}

Color Color::operator*(float value)
{
	return Color(r * value, g * value, b * value);
}

Color Color::operator*(float value) const
{
	return Color(r * value, g * value, b * value);
}

void  Color::operator*=(float value)
{
	r *= value;
	g *= value;
	b *= value;
}

bool Color::equals(const Color& col) const
{
	return r == col.r && g == col.g && b == col.b;
}