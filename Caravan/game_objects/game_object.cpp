#include "game_object.h"
#include <iostream>

GameObject::GameObject()
	: position(0, 0), size(1, 1), rotation(0.0f), color(glm::vec3(1.0f))
{}
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, GLfloat rotation, glm::vec2 velocity)
	: position(pos), size(size), sprite(sprite), color(color), rotation(rotation), velocity(velocity)
{}

glm::vec2 GameObject::getPosition() const
{
	return this->position;
}
void GameObject::setPosition(glm::vec2 pos)
{
	this->position = pos;
}
glm::vec2 GameObject::getSize() const
{
	return this->size;
}
void GameObject::setSize(glm::vec2 size)
{
	this->size = size;
}
glm::vec3 GameObject::getColor() const
{
	return this->color;
}
void GameObject::setColor(glm::vec3 color)
{
	this->color = color;
}
GLfloat GameObject::getRotation() const
{
	return this->rotation;
}
void GameObject::setRotation(GLfloat rotation)
{
	this->rotation = rotation;
}

bool GameObject::operator<(const GameObject &object) const
{
	if (this->position.x < object.position.x)
		return true;
	else return false;
}

bool GameObject::animate_slide(glm::vec2 pos, GLfloat dt)
{
	this->velocity = glm::normalize(pos - this->position);
	glm::vec2 distance = (pos - this->position);
	//std::cout << "pos: " << pos.x << ", " << pos.y << "		this->position: " << this->position.x << ", " << this->position.y << std::endl;
	glm::vec2 travel = this->velocity * (50 * dt);
	//std::cout << glm::length(distance) << std::endl;
	bool posX = false, posY = false;
	if (glm::length(pos - travel - this->position) < glm::length(pos - this->position))
	{
		this->position += travel;
		return true;
	}
	else
	{
		this->position = pos;
		return false;
	}
		
}

//P³ynne przejscie: 
bool GameObject::animate_push(glm::vec2 pos, GLfloat dt)
{
	this->velocity = pos - this->position;
	glm::vec2 distance = (pos - this->position);
	double distanceLength = glm::length(distance);
	glm::vec2 travel = this->velocity * (10 * dt);
	glm::vec2 toGo = travel - pos;
	this->position += travel;

	//std::cout << distanceLength << std::endl;

	if (distanceLength > 0.1 || distanceLength < -0.1)
		return true;
	else
	{
		this->position = pos;
		return false;
	}
}

void GameObject::draw(SpriteRenderer * renderer)
{
	renderer->drawSprite(this->sprite, this->position, this->size, this->rotation, glm::vec3(1.0f));
}

void GameObject::drawColor(SpriteRenderer * renderer)
{
	renderer->drawSprite(ResourceManager::getTexture("blankcard"), this->position, this->size, this->rotation, this->color);
}

void GameObject::subDraw(SpriteRenderer * renderer, glm::vec2 offset, glm::vec2 subSize)
{
	renderer->drawSubSprite(sprite, position, offset, subSize, size, rotation, glm::vec3(1.0f));
}

void GameObject::subDrawColor(SpriteRenderer * renderer, glm::vec2 offset, glm::vec2 subSize)
{
	renderer->drawSubSprite(ResourceManager::getTexture("blankcard"), position, offset, subSize, size, rotation, this->color);
}
