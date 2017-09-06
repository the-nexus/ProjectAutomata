#include "GameOfLifeSimulation.h"
#include "../Cells/GameOfLifeCell.h"


const Color GameOfLifeSimulation::aliveColor = Color(1.f, 1.f, 1.f);
const Color GameOfLifeSimulation::deadColor = Color(0.f, 0.f, 0.f);


GameOfLifeSimulation::GameOfLifeSimulation()
{

}

GameOfLifeSimulation::~GameOfLifeSimulation()
{

}

void GameOfLifeSimulation::setupBuffers()
{
	frontBuffer = new Cell**[bufferWidth];
	backBuffer = new Cell**[bufferWidth];
	for (int i = 0; i < bufferWidth; ++i)
	{
		frontBuffer[i] = new Cell*[bufferHeight];
		backBuffer[i] = new Cell*[bufferHeight];
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontBuffer[i][j] = new GameOfLifeCell();
			backBuffer[i][j] = new GameOfLifeCell();
		}
	}
}

void GameOfLifeSimulation::reset()
{
	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			int randVal = rand() % 2;
			frontBuffer[i][j]->setState(randVal);
			Color col = getCellColor(frontBuffer[i][j]->getState());
			frontBuffer[i][j]->setColor(col);
		}
	}

	Simulation::reset();
}

void GameOfLifeSimulation::nextStep()
{
	// render front buffer
	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			bool isAlive = (frontBuffer[i][j]->getState() == 1);
			int aliveNeighbourCount = getAliveNeighbourCount(i, j);

			if (isAlive && (aliveNeighbourCount < 2 || aliveNeighbourCount > 3))
			{
				// die
				backBuffer[i][j]->setState(0);
				backBuffer[i][j]->setColor(getCellColor(frontBuffer[i][j]->getState()));
			}
			else if (!isAlive && aliveNeighbourCount == 3)
			{
				// come alive
				backBuffer[i][j]->setState(1);
				backBuffer[i][j]->setColor(getCellColor(frontBuffer[i][j]->getState()));
			}
			else
			{
				backBuffer[i][j]->setState(frontBuffer[i][j]->getState());
				backBuffer[i][j]->setColor(getCellColor(backBuffer[i][j]->getState()));
			}
		}
	}
	
	Simulation::nextStep();
}

Color GameOfLifeSimulation::getCellColor(int state) const
{
	Color result = deadColor;

	switch(state)
	{
	case 1:
		return aliveColor;

	default:
		return deadColor;
	}
}

int GameOfLifeSimulation::getAliveNeighbourCount(int x, int y) const
{
	int aliveNeighbourCount = 0;

	for (int i = -1; i < 2; ++i)
	{
		int currentX = x + i;
		if (currentX >= 0 && currentX < bufferWidth)
		{
			for (int j = -1; j < 2; ++j)
			{
				int currentY = y + j;
				if (currentY >= 0 && currentY < bufferHeight)
				{
					if (!(currentX == x && currentY == y) && frontBuffer[currentX][currentY]->getState() == 1)
					{
						++aliveNeighbourCount;
					}
				}
			}
		}
	}

	return aliveNeighbourCount;
}
