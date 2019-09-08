#include "card.h"
#include <iostream>

std::string Card::RanksNames[13] = {
	"As", "Dwójka", "Trójka", 
	"Czwórka", "Pi¹tka", "Szóstka", 
	"Siódemka", "Ósemka", "Dziewi¹tka", 
	"Dziesi¹tka", "Walet", "Dama", "Król"
};
std::string Card::SuitsNames[4] = {
	"Pik", "Kier", "Trefl", "Karo"
};

std::string Card::RanksNamesEng[13] = {
	"Ace", "Two", "Three",
	"Four", "Five", "Six", 
	"Seven", "Eight", "Nine",
	"Ten", "Walet", "Queen", "King"
};

std::string Card::SuitsNamesEng[4] = {
	"Clubs", "Hearths", "Spades", "Diamonds"
};

Card::Card(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 offset, glm::vec2 subSize, CardRanks val, CardSuits sign, glm::vec3 color)
	: GameObject(pos, size, sprite, color), offset(offset), subSize(subSize), rank(val), suit(sign) {}
Card::Card()
	: offset(glm::vec2(0, 0)), subSize(0, 0), rank(CardRanks::TWO), suit(CardSuits::CLUBS) {}

bool Card::operator==(const Card & card)
{
	//std::cout << "operator==()" << std::endl;
	//std::cout << this << std::endl;
	if (this->rank == card.rank && this->suit == card.suit)
		return true;
	return false;
}

const std::string Card::valueEnumToString() const
{
	std::string str = RanksNamesEng[this->rank] + std::string("-") + SuitsNamesEng[this->suit];
	return str;
}

glm::vec2 Card::getOffset() const { return this->offset; }
glm::vec2 Card::getSubSize() const { return this->subSize; }
CardRanks Card::getRank() const { return this->rank; }
CardSuits Card::getSuit() const { return this->suit; }

void Card::draw(SpriteRenderer* renderer)
{
	GameObject::subDraw(renderer, this->offset, this->subSize);
}

void Card::drawColor(SpriteRenderer * renderer)
{
	GameObject::subDrawColor(renderer, this->offset, this->subSize);
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	//os << Card::RanksNamesEng[card.rank] << " " << Card::SuitsNamesEng[card.suit];
	return os;
}