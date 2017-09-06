#ifndef FOREST_FIRE_CELL_H
#define FOREST_FIRE_CELL_H

#include "Cell.h"

struct ForestFireCell : public Cell
{
public:
	ForestFireCell();
	~ForestFireCell();

	void setTimeToLive(int inTimeToLive);
	int getTimeToLive() const;

private:
	int timeToLive;
};

#endif // FOREST_FIRE_CELL_H
