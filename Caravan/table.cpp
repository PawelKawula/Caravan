#include "table.h"
#include "utilities/sprite_renderer.h"

#include <iostream>
#include <algorithm>
#include <exception>

int Table::Player::getHandSize() const
{
	return this->cards.size();
}

Table::Player::Player(Table & table, std::string name)
	: table(table), name(name) {}

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

bool Table::Player::addCard(CardRanks rank, CardSuits suit)
{
	//std::cout << "addCard()" << std::endl;
	if (!this->gotCard(rank, suit))
	{
		this->cards.push_back(table.cards[rank][suit]);
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
			if (*it == table.cards[rank][suit])
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
		if (card == table.cards[rank][suit])
			return card;
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

//Table::Table(Game & game, Card & sampleCard)
//{
//	glm::vec2 sampleSize = sampleCard.getSize();
//	glm::vec2 sampleOffset = sampleCard.getSubSize();
//	for (int i = 0; i < this->RANKS_NUMBER; ++i)
//	{
//		for (int j = 0; j < this->SUITS_NUMBER; ++j)
//		{
//			CardRanks rank = (CardRanks)i;
//			CardSuits suit = (CardSuits)j;
//			//glm::vec2 position = glm::vec2(60 * rank, 70 * suit);
//			glm::vec2 position = glm::vec2(0.02 * this->width, 0.5 * (this->height - sampleCard.y * SCALE - this->height * 0.02));
//			//glm::vec2 offset = glm::vec2(2 + rank * 73, 2 + suit * 98);
//			glm::vec2 offset = glm::vec2(sampleOffset.x)
//			glm::vec2 subSize = glm::vec2(CARD_SIZE.x, CARD_SIZE.y - 2);
//			Card card = Card(position, CARD_SIZE * SCALE, ResourceManager::getTexture("cards"),
//				offset, CARD_SIZE, rank, suit);
//			cards[rank][suit] = card;
//			rCards.push_back(&cards[rank][suit]);
//		}
//	}
//
//}

Table::Table(int width, int height, double scale, Table::CardConstructor & constructor, int hand, std::string name1, std::string name2)
	: hand(hand), width(width), height(height), scale(scale), cardConstructor(constructor), players{Player(*this, name1), Player(*this, name2)}
{
	std::cout << "<!--Poczatek konstruktora--!>" << std::endl;
	glm::vec2 position = glm::vec2(0.02 * this->width, 0.5 * (this->height - constructor.size.y * this->scale - this->height * 0.02));
	for (int i = 0; i < this->RANKS_NUMBER; ++i)
	{
		for (int j = 0; j < this->SUITS_NUMBER; ++j)
		{
			CardRanks rank = (CardRanks)i;
			CardSuits suit = (CardSuits)j;
			glm::vec3 color;
			switch (suit)
			{
			case CardSuits::CLUBS:
				color = glm::vec3((18 + 18 * rank) / 255.0, 0, 0);
				break;
			case CardSuits::DIAMONDS:
				color = glm::vec3(0, (19 + 18 * rank) / 255.0, 0);
				break;
			case CardSuits::HEARTHS:
				color = glm::vec3(0, 0, (20 + 18 * rank) / 255.0);
				break;
			case CardSuits::SPADES:
				color = glm::vec3((21 + 18 * rank) / 255.0, (21 + 18 * rank) / 255.0, (21 + 18 * rank) / 255.0);
				break;
			}
			//glm::vec2 position = glm::vec2(60 * rank, 70 * suit);
			//glm::vec2 offset = glm::vec2(2 + rank * 73, 2 + suit * 98);
			glm::vec2 offset = glm::vec2(constructor.initialOffset.x + constructor.offset.x * rank, constructor.initialOffset.y + constructor.offset.y * suit);
			Card card = Card(position, constructor.size * glm::vec2(this->scale), ResourceManager::getTexture("cards"),
				offset, constructor.size, rank, suit, color);
			cards[rank][suit] = card;
			//std::cout << card.valueEnumToString() << std::endl;
		}
	}

	for (auto ranks : cards)
		for (auto card : ranks.second)
			std::cout << "Pozycja karty " << card.second << " : " << card.second.getPosition().x << ", " << card.second.getPosition().y << std::endl;
	std::cout << "cardConsturcor size in table constructor: " <<  constructor.size.x << ", " << constructor.size.y << std::endl;
	//std::random_shuffle(cards.begin(), cards.end());
	this->newStack();
	std::cout << "Koniec konstruktora" << std::endl;
}

void Table::newStack()
{
	std::cout << "Poczatek newStack()" << std::endl;
	std::vector<Card> cardsPointers;
	for (auto ranks : this->cards)
		for (auto card : ranks.second)
		{
			cardsPointers.push_back(card.second);
			//std::cout << card.second << std::endl;
		}
	std::random_shuffle(cardsPointers.begin(), cardsPointers.end());
	for (auto cardPointer : cardsPointers)
	{
		this->cardStack.push(cardPointer);
		//std::cout << *cardPointer << std::endl;
	}
		
	std::cout << "Koniec newStack()" << std::endl;
}

bool Table::tossTopCardFromStack(Player & player)
{
	std::cout << "Poczatek tossTopCardFromStack()" << std::endl;
	if (this->cardStack.empty())
		return false;
	player.addCard(cardStack.top().getRank(), cardStack.top().getSuit());
	this->cardStack.pop();
	std::cout << "Koniec tossTopCardFromStack()" << std::endl;
 	return true;
}

void Table::tossCards()
{
	std::cout << "Poczatek tossCards()" << std::endl;
	glm::vec2 cardSize = cardConstructor.size;
	std::cout << "Rozmiar karty: " << cardConstructor.size.x << ", " << cardConstructor.size.y << std::endl;
	for (int i = 0; i < hand; ++i)
	{
		//glm::vec2 position = glm::vec2(this->width * 0.02 + (cardSize.x + 10) * i, this->height * 0.02);
		if (!this->tossTopCardFromStack(players[0]))
			break;
		//this->animatedObjectsStack.push_back(std::pair<glm::vec2, std::shared_ptr<Card>>(position, animation));
		//position.y = this->height - cardSize.y - 0.02 * this->height;
		if (!this->tossTopCardFromStack(players[1]))
			break;
		//this->animatedObjectsStack.push_back(std::pair<glm::vec2, std::shared_ptr<Card>>(position, animation));
	}
	//std::cout << "Rozmiar reki gracza 0: " << players[0].getHandSize() << std::endl;
	//std::cout << "Rozmiar reki gracza 1: " << players[1].getHandSize() << std::endl;

	for (int i = 0; i < this->hand; ++i)
	{
		Card* animation;
		glm::vec2 position = glm::vec2(this->width * 0.02 + (cardSize.x + 10) * i, this->height * 0.02);

		if (i < this->players[0].getHandSize())
		{
			animation = &players[0].getCard(i);
			this->animatedObjectsStack.push_back(std::pair<glm::vec2, Card*>(position, animation));

		}
		if (i < this->players[1].getHandSize())
		{
			position.y = this->height - cardSize.y - this->height * 0.02;
			animation = &players[1].getCard(i);
			animatedObjectsStack.push_back(std::pair<glm::vec2, Card*>(position, animation));
		}
	}
	std::cout << cardStack.size() << std::endl;
	std::cout << "Koniec tossCards()" << std::endl;
}

bool Table::passCard(Player & p1, Player & p2, CardRanks rank, CardSuits suit)
{
	std::cout << "Poczatek passCard()" << std::endl;
	if (p1.gotCard(rank, suit))
	{
		if (!p2.gotCard(rank, suit))
		{
			p1.removeCard(rank, suit);
			p2.addCard(rank, suit);
			return true;
		}
		else
		{
			std::cout << "ERROR::TABLE::TWO_SAME_CARDS" << std::endl;
			return false;
		}
	}
	else
		return false;
}

std::vector<Card>& Table::getPlayerCards(int i)
{
	return players[i].getHand();
	// TODO: insert return statement here
}

void Table::processInput(GLfloat dt, SpriteRenderer * renderer)
{
	cardStack.top().drawColor(renderer);

	players[0].drawColor(renderer);
	players[1].drawColor(renderer);

	if (!animatedObjectsStack.empty())
	{
		std::list<std::pair<glm::vec2, Card*>>::iterator it = std::next(animatedObjectsStack.begin());
		if (it != animatedObjectsStack.end())
		{
			it->second->drawColor(renderer);
		}
		animatedObjectsStack.front().second->drawColor(renderer);
	}
}

void Table::update(GLfloat dt)
{
	//std::cout << "table.update()" << std::endl;
	//std::cout << animatedObjectsStack.size() << std::endl;

	if (!this->animatedObjectsStack.empty())
	{
		std::pair<glm::vec2, Card*> animation = animatedObjectsStack.front();
		//std::cout << animation.second->valueEnumToString();
		//std::cout << Card::RanksNamesEng[animation.second->getRank()] << " " << Card::SuitsNamesEng[animation.second->getRank()] << std::endl;
		//std::cout << "Pozycja animatedObjectStack: " << animation.second->getPosition().x << "-" << animation.second->getPosition().y << std::endl;
		if (!animation.second->animate_push(animation.first, dt))
		{
			animatedObjectsStack.pop_front();
		}
	}
}

void Table::render(SpriteRenderer * renderer)
{
	//std::cout << "table.render()" << std::endl;
	//std::cout << this->cardStack.top()->getPosition().x << ", " << this->cardStack.top()->getPosition().y << std::endl;
	//std::cout << players[0].getCard(0)->getPosition().x << players[0].getCard(0)->getPosition().y << std::endl;
	cardStack.top().draw(renderer);

	players[0].draw(renderer);
	players[1].draw(renderer);
	//std::cout << "players[0] hand size: " << players[0].getHandSize() << std::endl;
	
	if (!animatedObjectsStack.empty())
	{
		std::list<std::pair<glm::vec2, Card*>>::iterator it = std::next(animatedObjectsStack.begin());
		if (it != animatedObjectsStack.end())
		{
			it->second->draw(renderer);
			//std::cout << *it->second << std::endl;
			//std::cout << "next: " << it->second->valueEnumToString() << std::endl;
		}
		animatedObjectsStack.front().second->draw(renderer);
		//std::cout << "front: " << animatedObjectsStack.front().second->valueEnumToString() << std::endl;
		//std::cout << *animatedObjectsStack.front().second << std::endl;
	}
		
	//players[0].draw(renderer);
	//players[0].draw(renderer);
}