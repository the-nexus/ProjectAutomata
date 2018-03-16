#include "ForestFireSimulation.h"
#include "../../Utilities/Math.h"


const Color ForestFireSimulation::treeColor = Color(0.1f, 0.7f, 0.1f);
const Color ForestFireSimulation::fireColor = Color(1.f, 0.f, 0.f);
const Color ForestFireSimulation::emptyColor = Color(0.f, 0.f, 0.f);


ForestFireSimulation::ForestFireSimulation()
{
	simulationType = SimulationType::ForestFire;
	stepDuration = 0.01f;
}

ForestFireSimulation::~ForestFireSimulation()
{

}

void ForestFireSimulation::reset()
{
	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontBuffer[i][j]->setState(0);
			frontBuffer[i][j]->setColor(getCellColor(frontBuffer[i][j]->getState()));
		}
	}

	Simulation::reset();
}

void ForestFireSimulation::nextStep()
{
	// render front buffer
	int currentTimeToLive = 0;
	float randomProbability = 0.f;
	Cell* frontCell = nullptr;
	Cell* backCell = nullptr;


	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontCell = frontBuffer[i][j];
			backCell = backBuffer[i][j];

			switch (frontCell->getState())
			{
			case 0:
				randomProbability = (float)Math::RandRange();
				if (randomProbability <= probabilityGrowth)
				{
					// tree grows
					backCell->setState(1);
					backCell->setColor(getCellColor(backCell->getState()));
				}
				else
				{
					backCell->setState(frontCell->getState());
					backCell->setColor(frontCell->getColor());
				}
				break;

			case 1:
				randomProbability = (float)Math::RandRange();
				
				if (randomProbability <= probabilityCatchFire || isNeighbourOnFire(i, j))
				{
					// tree catches fire
					backCell->setState(2);
					backCell->setTimeToLive(maxTimeToLive);
					backCell->setColor(getCellColor(backCell->getState(), backCell->getTimeToLive()));
				}
				else
				{
					backCell->setState(frontCell->getState());
					backCell->setColor(frontCell->getColor());
				}
				break;

			case 2:
				if (frontCell->getTimeToLive() > 1)
				{
					// decrease time to live of fire
					backCell->setState(2);
					backCell->setTimeToLive(frontCell->getTimeToLive() - 1);
					backCell->setColor(getCellColor(backCell->getState(), backCell->getTimeToLive()));
				}
				else
				{
					// stop burning and empty cell
					backCell->setState(0);
					backCell->setTimeToLive(0);
					backCell->setColor(getCellColor(backCell->getState()));
				}
				break;

			default:
				break;
			}
		}
	}

	Simulation::nextStep();
}

Color ForestFireSimulation::getCellColor(int state, int timeToLive) const
{
	float timeToLiveRatio = 0;
	switch (state)
	{
	case 1:
		return treeColor;

	case 2:
		timeToLiveRatio = (float)timeToLive / (float)maxTimeToLive;
		return fireColor * timeToLiveRatio;

	default:
		return emptyColor;
	}
}

int ForestFireSimulation::isNeighbourOnFire(int x, int y) const
{
	int leftX = x - 1;
	int rightX = x + 1;
	int upY = y - 1;
	int downY = y + 1;

	if (leftX >= 0 && frontBuffer[leftX][y]->getState() == 2)
	{
		return true;
	}

	if (rightX < bufferWidth && frontBuffer[rightX][y]->getState() == 2)
	{
		return true;
	}

	if (upY >= 0 && frontBuffer[x][upY]->getState() == 2)
	{
		return true;
	}

	if (downY < bufferHeight && frontBuffer[x][downY]->getState() == 2)
	{
		return true;
	}

	return false;
}
