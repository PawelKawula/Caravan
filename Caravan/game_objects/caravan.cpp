#include "caravan.h"
#include "player.h"

void Player::Caravan::updateValue()
{
	int val = 0;
	for (Slot & slot : this->slots)
		val += slot.getCard()->getValue();
	this->value = val;
}

bool Player::Caravan::addCard(const Card & card)
{
	
}
