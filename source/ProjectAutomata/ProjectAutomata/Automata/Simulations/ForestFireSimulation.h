#ifndef FOREST_FIRE_SIMULATION_H
#define FOREST_FIRE_SIMULATION_H

#include "Simulation.h"
#include "../Cells/ForestFireCell.h"

// STATES:
// 0 : dead
// 1 : alive

class ForestFireSimulation : public Simulation
{
public:
	static const Color treeColor;
	static const Color fireColor;
	static const Color emptyColor;

	ForestFireSimulation();
	~ForestFireSimulation();

	virtual void setupBuffers() override;
	virtual void reset() override;
	virtual void nextStep() override;

	Color getCellColor(int state, int timeToLive = 0) const;

	int isNeighbourOnFire(int x, int y) const;

private:
	int maxTimeToLive = 50;
	float probabilityCatchFire = 0.000005f;
	float probabilityGrowth = 0.001f;
};

#endif
