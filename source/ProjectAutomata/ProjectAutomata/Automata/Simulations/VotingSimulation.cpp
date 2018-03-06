#include "VotingSimulation.h"
#include "../../Utilities/Math.h"


const Color VotingSimulation::aOpinionColor = Color(1.f, 0.f, 0.f);
const Color VotingSimulation::bOpinionColor = Color(0.f, 1.f, 0.f);
const Color VotingSimulation::cOpinionColor = Color(0.f, 0.f, 1.f);
const Color VotingSimulation::dOpinionColor = Color(1.f, 1.f, 0.f);
const Color VotingSimulation::eOpinionColor = Color(0.f, 1.f, 1.f);
const Color VotingSimulation::fOpinionColor = Color(1.f, 0.f, 1.f);
const Color VotingSimulation::gOpinionColor = Color(1.f, 0.6f, 0.f);
const Color VotingSimulation::hOpinionColor = Color(0.f, 0.f, 0.f);
const Color VotingSimulation::iOpinionColor = Color(1.f, 1.f, 1.f);
const Color VotingSimulation::jOpinionColor = Color(0.5f, 0.5f, 0.5f);


VotingSimulation::VotingSimulation()
{
	simulationType = SimulationType::Voting;
	stepDuration = 0.05f;
	opinionCount = 2;
	majorityThreshold = 0.5f;
}

VotingSimulation::~VotingSimulation()
{

}

void VotingSimulation::reset()
{
	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontBuffer[i][j]->setState(Math::Rand() % opinionCount);
			frontBuffer[i][j]->setColor(getCellColor(frontBuffer[i][j]->getState()));
		}
	}

	Simulation::reset();
}

void VotingSimulation::nextStep()
{
	// render front buffer
	for (int i = 0; i < bufferWidth; ++i)
	{
		for (int j = 0; j < bufferHeight; ++j)
		{
			backBuffer[i][j]->setState(getOpinionFromNeighbors(i, j));
			backBuffer[i][j]->setColor(getCellColor(frontBuffer[i][j]->getState()));
		}
	}
	
	Simulation::nextStep();
}

Color VotingSimulation::getCellColor(int state) const
{
	switch(state)
	{
	case 1:
		return bOpinionColor;

	case 2:
		return cOpinionColor;

	case 3:
		return dOpinionColor;

	case 4:
		return eOpinionColor;

	case 5:
		return fOpinionColor;

	case 6:
		return gOpinionColor;

	case 7:
		return hOpinionColor;

	case 8:
		return iOpinionColor;

	case 9:
		return jOpinionColor;

	default:
		return aOpinionColor;
	}
}

int VotingSimulation::getOpinionFromNeighbors(int x, int y) const
{
	int aOpinionCount = 0;
	int bOpinionCount = 0;
	int cOpinionCount = 0;
	int dOpinionCount = 0;
	int eOpinionCount = 0;
	int fOpinionCount = 0;
	int gOpinionCount = 0;
	int hOpinionCount = 0;
	int iOpinionCount = 0;
	int jOpinionCount = 0;

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
					if (!(currentX == x && currentY == y))
					{
						switch (frontBuffer[currentX][currentY]->getState())
						{
						case 1:
							++bOpinionCount;
							break;

						case 2:
							++cOpinionCount;
							break;

						case 3:
							++dOpinionCount;
							break;

						case 4:
							++eOpinionCount;
							break;

						case 5:
							++fOpinionCount;
							break;

						case 6:
							++gOpinionCount;
							break;

						case 7:
							++hOpinionCount;
							break;

						case 8:
							++iOpinionCount;
							break;

						case 9:
							++jOpinionCount;
							break;

						default:
							++aOpinionCount;
							break;
						}
					}
				}
			}
		}
	}

	float totalOpinionCount = (float)aOpinionCount + (float)bOpinionCount + (float)cOpinionCount + (float)dOpinionCount + (float)eOpinionCount + (float)fOpinionCount + (float)gOpinionCount + (float)hOpinionCount + (float)iOpinionCount + (float)jOpinionCount;

	if ((float)aOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 0;
	}
	else if ((float)bOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 1;
	}
	else if ((float)cOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 2;
	}
	else if ((float)dOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 3;
	}
	else if ((float)eOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 4;
	}
	else if ((float)fOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 5;
	}
	else if ((float)gOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 6;
	}
	else if ((float)hOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 7;
	}
	else if ((float)iOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 8;
	}
	else if ((float)jOpinionCount / totalOpinionCount > majorityThreshold)
	{
		return 9;
	}

	// otherwise, return current state
	return frontBuffer[x][y]->getState();
}
