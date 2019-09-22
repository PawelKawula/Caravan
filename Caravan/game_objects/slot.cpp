#include "slot.h"

Slot::Slot(glm::vec2 pos, glm::vec2 size, Texture2D sprite, float outline)
	: GameObject(pos, size, sprite), outline(outline)
{
	glm::vec2 initialSize = this->getSize();
	glm::vec2 initialPosition = this->getPosition();
	GameObject::setPosition(glm::vec2(initialPosition.x - outline / 2 * initialSize.x, initialPosition.x - outline / 2 * initialSize.x));
	GameObject::setSize(glm::vec2(initialSize.x + initialSize.x * outline, initialSize.x + initialSize.x * outline));
}

void Slot::setCardPosition(glm::vec2 position)
{
	position.x = position.x - outline / 2;
	position.y = position.x - outline / 2;
	GameObject::setPosition(position);
}

Card * Slot::getCard()
{
	return this->card;
}

void Slot::setCard(Card * card)
{
	this->card = card;
}

void Slot::removeCard()
{
	this->card = nullptr;
}

bool Slot::isEmpty() const
{
	return this->card == nullptr;
}

bool Slot::cardInRange(const Card * card)
{
	glm::vec2 cardPos = card->getPosition();
	glm::vec2 cardSize = card->getSize();
	glm::vec2 slotPos = this->getPosition();
	glm::vec2 slotSize = this->getSize();
	bool x = (((cardPos.x + cardSize.x / 2) > slotPos.x) || ((slotPos.x > cardSize.x * 1.5)));
	bool y = (((cardPos.y + cardSize.y / 2) < slotPos.y) || ((slotPos.y > cardSize.y * 1.5)));
	return x && y;
}
