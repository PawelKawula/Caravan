#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "utilities/resource_manager.h"
#include "utilities/mouse_picker.h"
#include <iostream>
#include "game_objects/card.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game caravan(WINDOW_WIDTH, WINDOW_HEIGHT, 1);
extern std::map<CardRanks, std::map<CardSuits, Card>>	cards;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

struct {
	CardRanks rank;
	CardSuits suit;
} selected;

int main()
{
	selected = { CardRanks::ACE, CardSuits::CLUBS };
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Caravan", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_CULL_FACE);

	caravan.init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	caravan.state = GameState::GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		caravan.processInput(deltaTime);
		if (caravan.state == GameState::GAME_ACTIVE)
		{
			caravan.update(deltaTime);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			caravan.render();
		}
		glfwSwapBuffers(window);
	}

	ResourceManager::clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			caravan.keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			caravan.keys[key] = GL_FALSE;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//for (auto rank : cards)
	//{
	//	auto it = rank.second.rbegin();
	//	for (it; it != rank.second.rend(); ++it)
	//	{
	//		glm::ivec2 position = it->second.getPosition();
	//		glm::ivec2 size = it->second.getSize();
	//		if (xpos >= position.x && xpos <= position.x + size.x && ypos >= position.y && ypos <= position.y + size.y && selected.rank != it->second.getRank() && selected.suit != it->second.getSuit())
	//		{
	//			std::cout << it->second << std::endl;
	//			selected.rank = it->second.getRank();
	//			selected.suit = it->second.getSuit();
	//			break;
	//		}
	//	}
	//}
}