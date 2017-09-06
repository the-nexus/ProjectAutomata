
#ifndef PROJECT_AUTOMATA_H
#define PROJECT_AUTOMATA_H

#include <string>
#include <vector>
#include "../Graphics/Texture.h"
#include "../UI/TextLabel.h"

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

	void initializeWindow(int argc, char** argv);
	void initialize();
	int getWidth();
	int getHeight();
	void updateScene(int timeDelta);
	void renderScene();
	void processMouseClick(int button, int state, int x, int y);
	void processMouseMovement(int x, int y);
	void processKey(unsigned char key, bool isDown);
	void processSpecialKey(int key, bool isDown);
	int getDelay();
	void release();

	std::string fixDecimalText(std::string text, int decimalCount);

private:
	ProjectAutomata();
	~ProjectAutomata();

	static ProjectAutomata* instance;

	// Constants
	const int FPS = 60;
	const int DELAY = 1000 / FPS;
	const double PI = 3.14159;

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
	int lastFpsUpdate;
	int fpsUpdateDelay;

	// UI
	TextLabel* lblFps;
	TextLabel* lblFpsVal;
};

#endif