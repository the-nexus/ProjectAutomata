#include "Cell.h"

Cell::Cell()
{
	state = 0;
	color = Color(0.f, 0.f, 0.f);
	timeToLive = 0;
}

Cell::~Cell()
{

}

void Cell::setState(int inState)
{
	state = inState;
}

int Cell::getState() const
{
	return state;
}

void Cell::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Cell::setColor(const Color& inColor)
{
	color.r = inColor.r;
	color.g = inColor.g;
	color.b = inColor.b;
	color.a = inColor.a;
}

Color Cell::getColor() const
{
	return color;
}

void Cell::setTimeToLive(int inTimeToLive)
{
	timeToLive = inTimeToLive;
}

int Cell::getTimeToLive() const
{
	return timeToLive;
}
