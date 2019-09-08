#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "game_objects/card.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{

public:
	GameState state;
	int width;
	int height;
	GLboolean keys[1024];
	double scale;

	Game(int width, int height, double scale)
		: width(width), height(height), scale(scale) {}
	void init();
	void update(GLfloat dt);
	void render();
	void processInput(GLfloat dt);
};

#endif // GAME_H
