#include "table.h"
#include "utilities/sprite_renderer.h"

#include <iostream>
#include <algorithm>
#include <exception>



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
	: hand(hand), width(width), height(height), scale(scale), cardConstructor(constructor), players{Player(name1), Player(name2)}
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

	this->newStack();
}

void Table::newStack()
{
	std::vector<Card> cardsPointers;
	for (auto ranks : this->cards)
		for (auto card : ranks.second)
		{
			cardsPointers.push_back(card.second);
		}
	std::random_shuffle(cardsPointers.begin(), cardsPointers.end());
	for (auto cardPointer : cardsPointers)
	{
		this->cardStack.push(cardPointer);
	}
}

bool Table::tossTopCardFromStack(Player & player)
{
	if (this->cardStack.empty())
		return false;
	player.addCard(cards[cardStack.top().getRank()][cardStack.top().getSuit()]);
	this->cardStack.pop();
 	return true;
}

void Table::tossCards()
{
	glm::vec2 cardSize = cardConstructor.size;
	for (int i = 0; i < hand; ++i)
	{
		if (!this->tossTopCardFromStack(players[0]))
			break;
		if (!this->tossTopCardFromStack(players[1]))
			break;
	}

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
}

bool Table::passCard(Player & p1, Player & p2, CardRanks rank, CardSuits suit)
{
	if (p1.gotCard(rank, suit))
	{
		if (!p2.gotCard(rank, suit))
		{
			p1.removeCard(rank, suit);
			p2.addCard(cards[rank][suit]);
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
}

//void Table::moveCard(std::string name, glm::vec2 destination)
//{
//	if (name == cardStack.top().valueEnumToString())
//		std::cout << "Nie moge nic zrobic z karta ze stosu";
//	else
//	{
//		for (int i = 0; i < PLAYERS_NUMBER; ++i)
//		{
//			for (auto & card : players[i].cards)
//			{
//				if (name == card.valueEnumToString())
//				{
//					glm::vec2 pos = card.getPosition();
//					std::cout << name << " - Wczesniej: " << pos.x << ", " << pos.y << "	";
//					card.animate_slide(destination, dt);
//					pos = card.getPosition();
//					std::cout << "Pozniej: " << pos.x << ", " << pos.y << std::endl;
//					std::cout << "Adres karty w Table::moveCard: " << &card << std::endl;
//					return;
//				}
//			}
//				
//		}		//std::cout << "Przesuwam karte z " << position.x << ", " << position.y << " do " << destination.x << ", " << destination.y << std::endl;
//	}
//	std::cout << "Nie znaleziono takiej karty." << std::endl;
//}

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
	if (!this->animatedObjectsStack.empty())
	{
		std::pair<glm::vec2, Card*> animation = animatedObjectsStack.front();
		if (!animation.second->animate_push(animation.first, dt))
		{
			animatedObjectsStack.pop_front();
		}
	}
	std::cout << "Adres damy: " << &players[0].getHand()[1] << std::endl;
}

void Table::render(SpriteRenderer * renderer)
{
	cardStack.top().draw(renderer);

	players[0].draw(renderer);
	players[1].draw(renderer);
	
	if (!animatedObjectsStack.empty())
	{
		std::list<std::pair<glm::vec2, Card*>>::iterator it = std::next(animatedObjectsStack.begin());
		if (it != animatedObjectsStack.end())
		{
			it->second->draw(renderer);
		}
		animatedObjectsStack.front().second->draw(renderer);	}
}