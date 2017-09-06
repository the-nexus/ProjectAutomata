#include "ForestFireSimulation.h"
#include "../Cells/ForestFireCell.h"
#include "../../Utilities/Math.h"


const Color ForestFireSimulation::treeColor = Color(0.1f, 0.7f, 0.1f);
const Color ForestFireSimulation::fireColor = Color(1.f, 0.f, 0.f);
const Color ForestFireSimulation::emptyColor = Color(0.f, 0.f, 0.f);


ForestFireSimulation::ForestFireSimulation()
{

}

ForestFireSimulation::~ForestFireSimulation()
{

}

void ForestFireSimulation::setupBuffers()
{
	frontBuffer = new Cell**[bufferWidth];
	backBuffer = new Cell**[bufferWidth];
	for (int i = 0; i < bufferWidth; ++i)
	{
		frontBuffer[i] = new Cell*[bufferHeight];
		backBuffer[i] = new Cell*[bufferHeight];
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontBuffer[i][j] = new ForestFireCell();
			backBuffer[i][j] = new ForestFireCell();
		}
	}
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
	ForestFireCell* frontCell = nullptr;
	ForestFireCell* backCell = nullptr;


	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			switch (frontBuffer[i][j]->getState())
			{
			case 0:
				randomProbability = (float)Math::RandRange();
				if (randomProbability <= probabilityGrowth)
				{
					// tree grows
					backBuffer[i][j]->setState(1);
					backBuffer[i][j]->setColor(getCellColor(backBuffer[i][j]->getState()));
				}
				else
				{
					backBuffer[i][j]->setState(frontBuffer[i][j]->getState());
					backBuffer[i][j]->setColor(frontBuffer[i][j]->getColor());
				}
				break;

			case 1:
				randomProbability = (float)Math::RandRange();
				
				if (randomProbability <= probabilityCatchFire || isNeighbourOnFire(i, j))
				{
					// tree catches fire
					backCell = static_cast<ForestFireCell*>(backBuffer[i][j]);
					backCell->setState(2);
					backCell->setTimeToLive(maxTimeToLive);
					backCell->setColor(getCellColor(backCell->getState(), backCell->getTimeToLive()));
				}
				else
				{
					backBuffer[i][j]->setState(frontBuffer[i][j]->getState());
					backBuffer[i][j]->setColor(frontBuffer[i][j]->getColor());
				}
				break;

			case 2:
				frontCell = static_cast<ForestFireCell*>(frontBuffer[i][j]);
				backCell = static_cast<ForestFireCell*>(backBuffer[i][j]);
				currentTimeToLive = frontCell->getTimeToLive();
				if (currentTimeToLive > 1)
				{
					// decrease time to live of fire
					backCell->setState(2);
					backCell->setTimeToLive(currentTimeToLive - 1);
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
