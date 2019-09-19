#include "game.h"
#include "utilities/resource_manager.h"
#include "utilities/sprite_renderer.h"

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <array>
#include <algorithm>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "game_objects/card.h"
#include "utilities/mouse_picker.h"
#include "table.h"

SpriteRenderer				*renderer;
MousePicker					*mousePicker;
Table						*table;
extern GLFWwindow*			window;

const int HAND_SIZE = 4;
const float SCALE = 1;
const glm::vec2 CARD_SIZE = glm::vec2(71, 95);
std::map < CardRanks, std::map<CardSuits, Card>> cards;
std::list<std::pair<glm::vec2, Card *>> animatedObjectsStack;
std::stack<Card *> cardStack;

void Game::init()
{

	ResourceManager::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::loadTexture("textures/cards.png", GL_TRUE, "cards");
	ResourceManager::loadTexture("textures/blankcard.png", GL_FALSE, "blankcard");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	ResourceManager::getShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
	
	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	Table::CardConstructor cardConstructor = {
		glm::vec2(2, 2),
		glm::vec2(73, 98),
		CARD_SIZE,
		ResourceManager::getTexture("cards")
	};
	table = new Table(this->width, this->height, 1, cardConstructor, 4, "player1", "player2");
	table->tossCards();
	Card& firstCard = table->getPlayerCards(0)[0];
	mousePicker = new MousePicker(this->width, this->height, &firstCard, *table);
}

void Game::update(GLfloat dt)
{
	table->update(dt);
}

void Game::render()
{
	table->render(renderer);
}

void Game::processInput(GLfloat dt)
{
	table->processInput(dt, renderer);
	if (state == GAME_ACTIVE)
	{
		if (this->keys[GLFW_KEY_SPACE])
		{
			bool focus = mousePicker->getFocus();
			mousePicker->update();
			std::cout << "Adres w game::processInput: " << mousePicker->getSelectedObject() << std::endl;
			glm::vec2 position = mousePicker->getPosition();
			if (focus)
			{
				glm::vec2 pos = mousePicker->getSelectedObject()->getPosition();
				std::cout << "Najpierw: " << pos.x << ", " << pos.y << "	";
				mousePicker->getSelectedObject()->animate_push(position, dt);
				pos = mousePicker->getSelectedObject()->getPosition();
				std::cout << "Potem: " << pos.x << ", " << pos.y << std::endl;
			}
				
				//table->moveCard(mousePicker->getSelectedObject().valueEnumToString(), position);
			//if (focus && (selectedCard = dynamic_cast<Card &>(&mousePicker->getSelectedObject())))
				//table->moveCard(selectedObject.valueEnumToString(), position);
		}
		if (this->release[GLFW_KEY_SPACE])
		{
			mousePicker->setFocus(false);
			this->release[GLFW_KEY_SPACE] = GL_FALSE;
		}
	}
}
