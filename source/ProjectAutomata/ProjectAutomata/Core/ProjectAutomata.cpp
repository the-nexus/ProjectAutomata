#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "ProjectAutomata.h"
#include "ResourceInitializer.h"
#include "../IO/FontManager.h"
#include "../Automata/Simulations/GameOfLifeSimulation.h"
#include "../Automata/Simulations/ForestFireSimulation.h"
#include "../Automata/Simulations/VotingSimulation.h"
#include "../Utilities/Math.h"

using namespace std;
ProjectAutomata* ProjectAutomata::instance = nullptr;


ProjectAutomata::ProjectAutomata()
{
	width = 1280;
	height = 720;

	lastRightClickX = 0;
	lastRightClickY = 0;
	rightMouseDown = false;

	isRunning = false;
	keys = new bool[4];
	for (int i = 0; i < 4; i++)
	{
		keys[i] = false;
	}

	lastFpsUpdate = 0.f;
	fpsUpdateDelay = 0.1f;
}

ProjectAutomata::~ProjectAutomata()
{

}

ProjectAutomata* ProjectAutomata::getInstance()
{
	if (instance == nullptr)
		instance = new ProjectAutomata();
	return instance;
}

string ProjectAutomata::fixDecimalText(string text, int decimalCount)
{
	int dotPos = (int)text.find(".");
	if (dotPos != string::npos && text.length() > (unsigned int)(dotPos + decimalCount + 1))
		return text.substr(0, dotPos + decimalCount + 1);
	else
		return text;
}

void ProjectAutomata::setupWindow(int argc, char** argv)
{
	cout << "Creating window..." << endl;

	// Initialize GLUT
	glutInit(&argc, argv);

	// Setup the memory buffers for the display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(width, height);
	// Create the window with a specific title
	glutCreateWindow("Project Epsilon");
	// Bind the two functions above to respond when necessary
	glutReshapeFunc(ProjectAutomata::updateViewport);
	glutDisplayFunc(ProjectAutomata::refreshWindow);

	// FullScreen
	//glutGameModeString("800�600:32@60");
	//glutEnterGameMode();

	// Mouse input
	glutMouseFunc(mouseClickEvent);
	glutPassiveMotionFunc(mouseMovementEvent);
	glutMotionFunc(mouseMovementEvent);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Keyboard input
	glutKeyboardFunc(keyDownEvent);
	glutKeyboardUpFunc(keyUpEvent);
	glutSpecialFunc(specialKeyDownEvent);
	glutSpecialUpFunc(specialKeyUpEvent);

	// Initialize the entry points of the OpenGL Driver to be able to call all the functions in the API
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW failed to initialize");
		exit(1);
	}
}

void ProjectAutomata::cleanupWindow()
{
	cout << "Application terminated!" << endl;
}

void ProjectAutomata::refreshWindow()
{

}

void ProjectAutomata::mouseClickEvent(int button, int state, int x, int y)
{
	instance->processMouseClick(button, state, x, y);
}

void ProjectAutomata::mouseMovementEvent(int x, int y)
{
	instance->processMouseMovement(x, y);
}

void ProjectAutomata::keyDownEvent(unsigned char key, int x, int y)
{
	instance->processKey(key, true);
}

void ProjectAutomata::keyUpEvent(unsigned char key, int x, int y)
{
	instance->processKey(key, false);
}

void ProjectAutomata::specialKeyDownEvent(int key, int x, int y)
{
	instance->processSpecialKey(key, true);
}

void ProjectAutomata::specialKeyUpEvent(int key, int x, int y)
{
	instance->processSpecialKey(key, false);
}

void ProjectAutomata::updateViewport(int width, int height)
{
	double w = instance->width;
	double h = instance->height;

	// 2D
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, h, 0, 1000, -1000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void ProjectAutomata::loop(int lastTime)
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	glutTimerFunc(ProjectAutomata::getInstance()->getDelay(), ProjectAutomata::loop, currentTime);

	float timeDelta = (float)(currentTime - lastTime) / 1000.f;
	ProjectAutomata::getInstance()->updateScene(timeDelta);
	ProjectAutomata::getInstance()->renderScene();
}

int ProjectAutomata::getDelay()
{
	return DELAY;
}

int ProjectAutomata::getWidth()
{
	return width;
}

int ProjectAutomata::getHeight()
{
	return height;
}

void ProjectAutomata::processMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			lastRightClickX = x;
			lastRightClickY = y;
			rightMouseDown = true;
		}
		else
		{
			rightMouseDown = false;
		}
	}
}

void ProjectAutomata::processMouseMovement(int x, int y)
{

}

void ProjectAutomata::processKey(unsigned char key, bool isDown)
{

}

void ProjectAutomata::processSpecialKey(int key, bool isDown)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (simulation != nullptr && !isDown)
		{
			int maxSimTypeValue = (int)SimulationType::MAX_VALUE;
			int currentSimTypeValue = (int)simulation->getSimulationType();
			SimulationType newSimulationType = (SimulationType)((currentSimTypeValue - 1 + maxSimTypeValue) % maxSimTypeValue);
			changeSimulation(newSimulationType);
		}
		break;

	case GLUT_KEY_RIGHT:
		if (simulation != nullptr && !isDown)
		{
			int maxSimTypeValue = (int)SimulationType::MAX_VALUE;
			int currentSimTypeValue = (int)simulation->getSimulationType();
			SimulationType newSimulationType = (SimulationType)((currentSimTypeValue + 1 + maxSimTypeValue) % maxSimTypeValue);
			changeSimulation(newSimulationType);
		}
		break;

	default:
		break;
	}
}

void ProjectAutomata::setupProgram()
{
	// Utilities
	Math::Initialize();

	// OpenGL
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Resources
	FontManager::getInstance()->addFont("Press Start", "./resources/textures/fonts/pressStart.png");

	TCHAR pwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pwd);
	cout << "Current Directory = " << pwd << endl;

	// UI
	lblFps = new TextLabel(FontManager::getInstance()->getFont(0), 8.0, "FPS: ", 10.0, 10.0);
	lblFpsVal = new TextLabel(FontManager::getInstance()->getFont(0), lblFps->getSize(), "", lblFps->getWidth(), lblFps->getY());

	padding = 60.f;
	tileSize = 4.f;
	tileCountX = (int)((width - (2.f * padding)) / tileSize);
	tileCountY = (int)((height - (2.f * padding)) / tileSize);

	changeSimulation(SimulationType::GameOfLife);
}

void ProjectAutomata::runProgram()
{
	if (!isRunning)
	{
		loop(glutGet(GLUT_ELAPSED_TIME));
		isRunning = true;
		glutMainLoop();
	}
}

void ProjectAutomata::cleanupProgram()
{
	if (simulation != nullptr)
	{
		simulation->cleanupSimulation();
	}

	cout << "Cleaned up program!" << endl;
}

void ProjectAutomata::changeSimulation(SimulationType newSimulationType)
{
	if (simulation != nullptr)
	{
		// Check if we are already using this type of simulation
		if (simulation->getSimulationType() == newSimulationType)
		{
			return;
		}

		// Cleanup old simulation
		if (simulation != nullptr)
		{
			simulation->cleanupSimulation();
			delete simulation;
		}
	}

	// Create new simulation
	switch (newSimulationType)
	{
	case SimulationType::GameOfLife:
		simulation = new GameOfLifeSimulation();
		break;

	case SimulationType::ForestFire:
		simulation = new ForestFireSimulation();
		break;

	case SimulationType::Voting:
		simulation = new VotingSimulation();
		break;

	default:
		break;
	}

	// Setup new simulation
	if (simulation != nullptr)
	{
		simulation->setBufferSize(tileCountX, tileCountY);
		simulation->setupSimulation();
	}
}

void ProjectAutomata::updateScene(float deltaTime)
{
	if (simulation != nullptr)
	{
		simulation->tick(deltaTime);
	}

	//UI
	lblFps->update(deltaTime);
	lblFpsVal->update(deltaTime);
	lastFpsUpdate += deltaTime;
	if (lastFpsUpdate > fpsUpdateDelay)
	{
		float fps = 1.f / deltaTime;
		string fpsText = std::to_string(fps);
		lblFpsVal->setText(fixDecimalText(fpsText, 2));
		lastFpsUpdate = 0.f;
	}
}

void ProjectAutomata::renderScene()
{
	int polyCount = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glColor3d(1.0, 1.0, 1.0);

	glPushMatrix();

	// TODO: Draw scene

	glTranslatef(padding, padding, 0.f);
	glScalef(tileSize, tileSize, 1.f);

	if (simulation != nullptr)
	{
		simulation->render();
	}

	glPopMatrix();


	// UI
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	lblFps->draw();
	lblFpsVal->draw();

	if (glutGetWindow() != 0)
		glutSwapBuffers();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}



int main(int argc, char** argv)
{
	// Init random seed
	srand((unsigned int)time(nullptr));

	ProjectAutomata* program = ProjectAutomata::getInstance();
	program->setupWindow(argc, argv);
	program->setupProgram();
	program->runProgram();
	program->cleanupProgram();
	program->cleanupWindow();
	delete program;

	return 0;
}