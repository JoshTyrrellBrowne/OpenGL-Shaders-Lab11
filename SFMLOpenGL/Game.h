#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <MyVector3.h>
#include <Matrix3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
using namespace sf;
//using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void checkKeyInput();
	void updateResultVerts();
	void setTexels(sf::Vector2f t_centerPoint, int t_i);

	MyVector3 tempVector{ 0,0,0 };

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};

#endif