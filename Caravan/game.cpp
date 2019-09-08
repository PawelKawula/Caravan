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
//MousePicker					*mousePicker;
Table						*table;

const int HAND_SIZE = 4;
const float SCALE = 1;
const glm::vec2 CARD_SIZE = glm::vec2(71, 95);
//std::list<Card*> animatedObjectsStack;
std::map < CardRanks, std::map<CardSuits, Card>> cards;
std::list<std::pair<glm::vec2, Card *>> animatedObjectsStack;
std::stack<Card *> cardStack;

void Game::init()
{

	ResourceManager::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
	//ResourceManager::loadTexture("textures/awesomeface.png", GL_TRUE, "face");
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

	//glm::vec2 position = glm::vec2(0.02 * this->width, 0.5 * (this->height - cardConstructor.size.y * this->scale - this->height * 0.02));
	//for (int i = 0; i < 13; ++i)
	//{
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		CardRanks rank = (CardRanks)i;
	//		CardSuits suit = (CardSuits)j;
	//		//glm::vec2 position = glm::vec2(60 * rank, 70 * suit);
	//		//glm::vec2 offset = glm::vec2(2 + rank * 73, 2 + suit * 98);
	//		glm::vec2 offset = glm::vec2(cardConstructor.initialOffset.x + cardConstructor.offset.x * rank, cardConstructor.initialOffset.y + cardConstructor.offset.y * suit);
	//		Card card = Card(position, cardConstructor.size * glm::vec2(this->scale), ResourceManager::getTexture("cards"),
	//			offset, cardConstructor.size, rank, suit);
	//		//std::cout << "wypierdala sie na " << rank << " figury " << suit << std::endl;
	//		cards[rank][suit] = card;
	//		cardStack.push(&cards[rank][suit]);
	//	}
	//}
	//std::vector<std::shared_ptr<Card>> rCards;
	////for (int i = 0; i < 13; ++i)
	////	animatedObjectsStack.push_back(&cards[(CardRanks)i][CardSuits::CLUBS]);
	//for (int i = 0; i < HAND_SIZE * 2; ++i)
	//{
	//	//int player = i % players.size();
	//	//std::cout << player << std::endl;
	//	//players[player].addCard(cardStack.top());
	//	glm::vec2 cardSize = cards[CardRanks::ACE][CardSuits::CLUBS].getSize();
	//	glm::vec2 position = glm::vec2(this->width * 0.02 + (cardSize.x + 10) * (i - i % 2), 10);
	//	if (i % 2)
	//		position.y = this->height - cardSize.y - this->height * 0.02;
	//	animatedObjectsStack.push_back(std::pair<glm::vec2, Card*>(position, cardStack.top()));
	//	cardStack.pop();
	//}
	////std::cout << cards[CardRanks::ACE][CardSuits::SPADES].getPosition().y << std::endl;
	//cards[CardRanks::ACE][CardSuits::CLUBS].setPosition(glm::vec2(500, 600));
}

void Game::update(GLfloat dt)
{
	//glm::vec2 position = cards[CardRanks::ACE][CardSuits::CLUBS].getPosition();

	//if (!animatedObjectsStack.empty())
	//{
	//	std::pair<glm::vec2, Card *> animation = animatedObjectsStack.front();
	//	if (!animation.second->animate_push(animation.first, dt))
	//		animatedObjectsStack.pop_front();
	//}
		
	//if (!animatedObjectsStack.empty())
	//{
	//	std::pair<glm::vec2, Card*> animation = animatedObjectsStack.front();
	//	if (!animation.second->animate_push(animation.first, dt))
	//	{
	//		animatedObjectsStack.pop_front();
	//		if (!animatedObjectsStack.empty());
	//			//std::cout << *animatedObjectsStack.front().second << ": " << animation.first.x << ", " << animation.first.y << std::endl;
	//	}
	//}
	//cards[CardRanks::ACE][CardSuits::CLUBS].setPosition(cardPosition);
	//cards.insert(cards[CardRanks::ACE][CardSuits::CLUBS]);
	table->update(dt);
}

void Game::render()
{
	//for (auto rank : cards)
	//{
	//	for (auto object : rank.second)
	//		object.second.draw(renderer);
	//}
	table->render(renderer);
}

void Game::processInput(GLfloat dt)
{
}
