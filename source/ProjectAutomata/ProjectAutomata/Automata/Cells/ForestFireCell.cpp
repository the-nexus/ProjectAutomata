#include "ForestFireCell.h"


ForestFireCell::ForestFireCell()
{
	state = 0;
	timeToLive = 0;
	color = Color(0.f, 0.f, 0.f);
}

ForestFireCell::~ForestFireCell()
{

}

void ForestFireCell::setTimeToLive(int inTimeToLive)
{
	timeToLive = inTimeToLive;
}

int ForestFireCell::getTimeToLive() const
{
	return timeToLive;
}
