#include "../table.h"

int Table::Player::getHandSize() const
{
	return this->cards.size();
}

Table::Player::Player(std::string name)
	: name(name) {}

bool Table::Player::gotCard(CardRanks rank, CardSuits suit) const
{
	//std::cout << "gotCard()" << std::endl;
	for (auto card : this->cards)
	{
		return false;
		if (card.getRank() == rank && card.getSuit() == suit)
			return true;
	}
	return false;
}

bool Table::Player::addCard(Card card)
{
	//std::cout << "addCard()" << std::endl;
	CardRanks rank = card.getRank();
	CardSuits suit = card.getSuit();

	if (!this->gotCard(rank, suit))
	{
		this->cards.push_back(card);
		return true;
	}
	else
		return false;
}

bool Table::Player::removeCard(CardRanks rank, CardSuits suit)
{
	//std::cout << "removeCard()" << std::endl;
	if (gotCard(rank, suit))
	{
		for (auto it = this->cards.begin(); it != this->cards.end(); ++it)
		{
			CardRanks r = it->getRank();
			CardSuits s = it->getSuit();
			if (r == rank && s == suit)
			{
				this->cards.erase(it);
				return true;
			}
		}
	}
	return false;
}

Card& Table::Player::getCard(CardRanks rank, CardSuits suit)
{
	for (auto card : this->cards)
	{
		if (card.getRank() == rank && card.getSuit() == suit)
			return card;
	}
		
}

Card& Table::Player::getCard(int index)
{
	if (this->cards.size() > index)
		return cards[index];
}

std::vector<Card>& Table::Player::getHand()
{
	return cards;
	// TODO: insert return statement here
}

//std::shared_ptr<Card> Table::Player::getCard(CardRanks rank, CardSuits suit)
//{
//	std::cout << "getCard()" << std::endl;
//	for (auto card : this->cards)
//		if (*card == table.cards[rank][suit])
//			return card;
//}

void Table::Player::draw(SpriteRenderer * renderer)
{
	for (auto card : this->cards)
	{
		//std::cout << "narysowano " << card.valueEnumToString() << std::endl;
		card.draw(renderer);
	}

}

void Table::Player::drawColor(SpriteRenderer * renderer)
{
	for (auto card : cards)
		card.drawColor(renderer);
}