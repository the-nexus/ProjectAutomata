#include "Simulation.h"
#include "GL/glew.h"
#include "GL/freeglut.h"


Simulation::Simulation()
{
	stepDuration = 1.f;
	paused = true;
}

Simulation::~Simulation()
{
	cleanupBuffers();
}

// Runtime functions
void Simulation::setupSimulation()
{
	reset();

	// Transient variables init
	paused = false;
}

void Simulation::cleanupSimulation()
{
	// Transient variables uninit
	paused = true;
}

void Simulation::render()
{
	glPushMatrix();

	// render front buffer
	if (frontBuffer != nullptr)
	{
		for (int i = 0; i < bufferWidth; ++i)
		{
			if (frontBuffer[i] != nullptr)
			{
				for (int j = 0; j < bufferHeight; ++j)
				{
					if (frontBuffer[i][j] != nullptr)
					{

						Color color = frontBuffer[i][j]->getColor();

						int startX = i;
						int startY = j;
						int endX = i + 1;
						int endY = j + 1;

						glColor3d(color.r, color.g, color.b);
						glBegin(GL_QUADS);
						{
							glVertex2i(startX, startY);
							glVertex2i(endX, startY);
							glVertex2i(endX, endY);
							glVertex2i(startX, endY);
						}
						glEnd();
					}
				}
			}
		}
	}

	// Render the outline
	float endX = (float)bufferWidth;
	float endY = (float)bufferHeight;
	glColor3f(0.25f, 0.25f, 0.25f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(0, 0);
		glVertex2i(bufferWidth, 0);
		glVertex2i(bufferWidth, bufferHeight);
		glVertex2i(0, bufferHeight);
	}
	glEnd();

	glPopMatrix();
}

void Simulation::tick(float deltaTime)
{
	if (!isPaused())
	{
		stepTime += deltaTime;
		if (stepTime >= stepDuration)
		{
			stepTime = 0.f;
			nextStep();
		}
	}
}


// Simulation management
void Simulation::setupBuffers()
{
	frontBuffer = new Cell**[bufferWidth];
	backBuffer = new Cell**[bufferWidth];
	for (int i = 0; i < bufferWidth; ++i)
	{
		frontBuffer[i] = new Cell*[bufferHeight];
		backBuffer[i] = new Cell*[bufferHeight];
		for (int j = 0; j < bufferHeight; ++j)
		{
			frontBuffer[i][j] = new Cell();
			backBuffer[i][j] = new Cell();
		}
	}
}

void Simulation::cleanupBuffers()
{
	// front buffer
	if (frontBuffer != nullptr)
	{
		for (int i = 0; i < bufferWidth; ++i)
		{
			if (frontBuffer[i] != nullptr)
			{
				for (int j = 0; j < bufferHeight; ++j)
				{
					if (frontBuffer[i][j] != nullptr)
					{
						delete frontBuffer[i][j];
					}
				}
				delete frontBuffer[i];
			}
		}
		delete frontBuffer;
	}

	// back buffer
	if (backBuffer != nullptr)
	{
		for (int i = 0; i < bufferWidth; ++i)
		{
			if (backBuffer[i] != nullptr)
			{
				for (int j = 0; j < bufferHeight; ++j)
				{
					if (backBuffer[i][j] != nullptr)
					{
						delete backBuffer[i][j];
					}
				}
				delete backBuffer[i];
			}
		}
		delete backBuffer;
	}
}

void Simulation::setBufferSize(int inBufferWidth, int inbufferHeight)
{
	// release old buffers
	cleanupBuffers();

	// set new dimensions
	bufferWidth = inBufferWidth;
	bufferHeight = inbufferHeight;

	// make new buffers
	setupBuffers();

	// reset simulation
	reset();
}

int Simulation::getBufferWidth() const
{
	return bufferWidth;
}

int Simulation::getBufferHeight() const
{
	return bufferHeight;
}

void Simulation::reset()
{
	stepTime = 0.f;
}

void Simulation::pause()
{
	if (!isPaused())
	{
		paused = true;
	}
}

void Simulation::resume()
{
	if (isPaused())
	{
		paused = false;
	}
}

bool Simulation::isPaused() const
{
	return paused;
}


// Simulation step management
void Simulation::nextStep()
{
	// swap the back buffer to the front
	swapBuffers();
}

void Simulation::setGenerationDuration(float inGenerationDuration)
{
	stepDuration = inGenerationDuration;
}

float Simulation::getGenerationDuration() const
{
	return stepDuration;
}


void Simulation::swapBuffers()
{
	Cell*** tempBuffer = frontBuffer;
	frontBuffer = backBuffer;
	backBuffer = tempBuffer;
}