
#ifndef PROJECT_AUTOMATA_H
#define PROJECT_AUTOMATA_H

#include <string>
#include <vector>
#include "../Graphics/Texture.h"
#include "../UI/TextLabel.h"
#include "../Automata/Simulations/Simulation.h"

class ProjectAutomata
{
public:
	static ProjectAutomata* getInstance();
	static void updateViewport(int width, int height);
	static void refreshWindow();
	static void loop(int lastTime);
	static void mouseClickEvent(int button, int state, int x, int y);
	static void mouseMovementEvent(int x, int y);
	static void keyDownEvent(unsigned char key, int x, int y);
	static void keyUpEvent(unsigned char key, int x, int y);
	static void specialKeyDownEvent(int key, int x, int y);
	static void specialKeyUpEvent(int key, int x, int y);

	~ProjectAutomata();

	void setupWindow(int argc, char** argv);
	void cleanupWindow();
	void setupProgram();
	void runProgram();
	void cleanupProgram();
	int getWidth();
	int getHeight();
	void updateScene(float deltaTime);
	void renderScene();
	void processMouseClick(int button, int state, int x, int y);
	void processMouseMovement(int x, int y);
	void processKey(unsigned char key, bool isDown);
	void processSpecialKey(int key, bool isDown);
	int getDelay();

	std::string fixDecimalText(std::string text, int decimalCount);

private:
	ProjectAutomata();

	static ProjectAutomata* instance;

	// Constants
	const int FPS = 60;
	const int DELAY = 1000 / FPS;

	// Execution
	bool isRunning;

	// Inputs
	bool* keys;
	int lastRightClickX;
	int lastRightClickY;
	bool rightMouseDown;

	// View
	int width;
	int height;

	// FPS
	float lastFpsUpdate;
	float fpsUpdateDelay;

	// UI
	TextLabel* lblFps;
	TextLabel* lblFpsVal;

	// Simulation
	Simulation* simulation;
	float padding;
	float tileSize;
	int tileCountX;
	int tileCountY;
};

#endif