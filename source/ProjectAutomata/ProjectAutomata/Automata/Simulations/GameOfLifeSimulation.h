#ifndef GAME_OF_LIFE_SIMULATION_H
#define GAME_OF_LIFE_SIMULATION_H

#include "Simulation.h"
#include "../Cells/GameOfLifeCell.h"

// STATES:
// 0 : dead
// 1 : alive

class GameOfLifeSimulation : public Simulation
{
public:
	static const Color aliveColor;
	static const Color deadColor;

	GameOfLifeSimulation();
	~GameOfLifeSimulation();

	virtual void setupBuffers() override;
	virtual void reset() override;
	virtual void nextStep() override;

	Color getCellColor(int state) const;

	int getAliveNeighbourCount(int x, int y) const;
};

#endif
