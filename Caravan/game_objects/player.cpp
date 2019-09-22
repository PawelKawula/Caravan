#include "../table.h"

int Player::getHandSize() const
{
	int size = this->cards.size() + this->actionCards.size();
	return size;
}

Player::Player(std::string name)
	: name(name) {}

void Player::reset()
{
	for (auto slot : this->slots)
		slot.removeCard();
	this->cards.resize(0);
}

bool Player::gotCard(CardRanks rank, CardSuits suit) const
{
	//std::cout << "gotCard()" << std::endl;
	for (auto card : this->cards)
	{
		if (card.getRank() == rank && card.getSuit() == suit)
			return true;
	}
	return false;
}

bool Player::addCard(Card card)
{
	//std::cout << "addCard()" << std::endl;
	CardRanks rank = card.getRank();
	CardSuits suit = card.getSuit();

	if (cards.size() < slots.size())
	{
		if (!this->gotCard(rank, suit))
		{
			for (int i = 0; i < slots.size(); ++i)
				if (!gotCard(rank, suit))
				{
					cards.push_back(card);
					for (int j = 0; j < slots.size(); ++j)
						if (slots[j].getCard() == nullptr)
							slots[j].setCard(&cards[cards.size() - 1]);
				}
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool Player::addCard(Card card, int slotNumber)
{
	CardRanks rank = card.getRank();
	CardSuits suit = card.getSuit();

	if (cards.size() < slots.size())
	{
		if (!this->gotCard(rank, suit))
		{
			for (int i = 0; i < slots.size(); ++i)
				if (!gotCard(rank, suit))
				{
					cards.push_back(card);
					if (slots[slotNumber].getCard() == nullptr)
					{
						slots[slotNumber].setCard(&cards[cards.size() - 1]);
						return true;
					}
					else return false;
				}
		}
		else
			return false;
	}
	else
		return false;
}

bool Player::passCardToCaravan(Slot & playerSlot, Slot & caravanSlot, int caravan)
{
	Card * card = playerSlot.getCard();
	if (!card->isActionCard())
	{
		if (caravanSlot.isEmpty())
		{
			for (Slot & slot : this->slots)
				if (&slot == &caravanSlot)
				{
					playerSlot.removeCard();
					this->caravans[caravan].
					return true;
				}
		}
		else
			return false;
	}
}

bool Player::removeCard(CardRanks rank, CardSuits suit)
{
	//std::cout << "removeCard()" << std::endl;
	if (gotCard(rank, suit))
	{
		for (int i = 0; i < cards.size(); ++i)
		{
			CardRanks r = this->cards[i].getRank();
			CardSuits s = this->cards[i].getSuit();
			if (r == rank && s == suit)
			{
				auto it = cards.begin() + i;
				for (int j = 0; j < slots.size(); ++j)
					if (slots[j].getCard() == &cards[i])
					{
						this->cards.erase(it);
						slots[j].setCard(nullptr);
						return true;
					}
				return false;
			}
		}
	}
	return false;
}

Card& Player::getCard(CardRanks rank, CardSuits suit)
{
	for (auto card : this->cards)
	{
		if (card.getRank() == rank && card.getSuit() == suit)
			return card;
	}
		
}

Card& Player::getCard(int index)
{
	if (this->cards.size() > index)
		return cards[index];
}

std::vector<Card>& Player::getHand()
{
	return cards;
}

void Player::draw(SpriteRenderer * renderer)
{
	for (auto card : this->cards)
	{
		//std::cout << "narysowano " << card.valueEnumToString() << std::endl;
		card.draw(renderer);
	}

}

void Player::drawColor(SpriteRenderer * renderer)
{
	for (auto card : cards)
		card.drawColor(renderer);
}