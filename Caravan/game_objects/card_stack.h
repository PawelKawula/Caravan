#ifndef CARD_STACK_H
#define CARD_STACK_H

#include "card.h"
#include <vector>
#include <algorithm>

class CardStack
{
	std::vector<Card> cards;
public:
	void displayStack();
	void addCard(Card card);
	bool removeCard(CardSuits sign, CardRanks value);
};
#endif