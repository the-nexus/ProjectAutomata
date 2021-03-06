#ifndef SIMULATION_H
#define SIMULATION_H

#include "../Cells/Cell.h"

enum class SimulationType
{
	GameOfLife,
	ForestFire,
	Voting,
	MAX_VALUE
};

class Simulation
{
public:
	~Simulation();

	// Runtime functions
	virtual void setupSimulation();
	virtual void cleanupSimulation();
	virtual void render();
	virtual void tick(float deltaTime);

	// Simulation management
	virtual void setupBuffers();
	void cleanupBuffers();
	void setBufferSize(int inBufferWidth, int inbufferHeight);
	int getBufferWidth() const;
	int getBufferHeight() const;
	virtual void reset();
	void pause();
	void resume();
	bool isPaused() const;

	// Simulation step management
	virtual void nextStep();
	void setGenerationDuration(float inGenerationDuration);
	float getGenerationDuration() const;

	// Other getters and setters
	SimulationType getSimulationType() const;

protected:
	Simulation();

	void swapBuffers();

	SimulationType simulationType;

	Cell*** frontBuffer;
	Cell*** backBuffer;

	int bufferWidth;
	int bufferHeight;

	bool paused;

	float stepTime;
	float stepDuration;
};


#endif