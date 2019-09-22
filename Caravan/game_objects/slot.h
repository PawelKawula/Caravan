#ifndef SLOT_H
#define SLOT_H

#include "game_object.h"
#include "card.h"
#include "../utilities/sprite_renderer.h"

class Slot : public GameObject
{
	Card * card;
	float outline;
public:
	Slot(glm::vec2 pos, glm::vec2 size, Texture2D sprite, float outline);
	//void draw(SpriteRenderer * renderer);
	void setCardPosition(glm::vec2 position);

	Card * getCard();
	void setCard(Card * card);
	void removeCard();
	bool isEmpty() const;

	bool cardInRange(const Card * card);
};
#endif // ! SLOT_H
