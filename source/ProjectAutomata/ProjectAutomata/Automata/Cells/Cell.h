#ifndef CELL_H
#define CELL_H

#include "../../Graphics/Color.h"

struct Cell
{
public:
	~Cell();

	void setState(int inState);
	int getState() const;
	void setColor(float r, float g, float b, float a = 1.f);
	void setColor(const Color& inColor);
	Color getColor() const;

protected:
	Cell();

	int state;
	Color color;
};

#endif // CELL_H
