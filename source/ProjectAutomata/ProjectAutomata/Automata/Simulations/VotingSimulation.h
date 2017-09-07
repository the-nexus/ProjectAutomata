#ifndef VOTING_SIMULATION_H
#define VOTING_SIMULATION_H

#include "Simulation.h"

// STATES:
// 0 : opinion a
// 1 : opinion b

class VotingSimulation : public Simulation
{
public:
	static const Color aOpinionColor;
	static const Color bOpinionColor;
	static const Color cOpinionColor;
	static const Color dOpinionColor;
	static const Color eOpinionColor;
	static const Color fOpinionColor;
	static const Color gOpinionColor;
	static const Color hOpinionColor;
	static const Color iOpinionColor;
	static const Color jOpinionColor;

	VotingSimulation();
	~VotingSimulation();

	virtual void reset() override;
	virtual void nextStep() override;

	Color getCellColor(int state) const;

	int getOpinionFromNeighbors(int x, int y) const;

private:
	int opinionCount;
	float majorityThreshold;
};

#endif //VOTING_SIMULATION_H
