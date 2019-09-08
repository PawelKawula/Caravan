#include "card_stack.h"
#include <iostream>

void CardStack::displayStack()
{
	for (Card& card : cards)
		std::cout << card << std::endl;
}

void CardStack::addCard(Card card)
{
	cards.push_back(card);
}

bool CardStack::removeCard(CardSuits sign, CardRanks value)
{
	std::vector<Card>::iterator it;
	for (it = cards.begin(); it != cards.end(); ++it)
		if (it->getSuit() == sign && it->getRank() == value)
			break;
	if (it != cards.end())
	{
		cards.erase(it);
		return true;
	}
	return false;
}