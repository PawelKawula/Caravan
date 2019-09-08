#ifndef CARD_H
#define CARD_H

#include "game_object.h"

enum CardRanks
{
	ACE,
	TWO, THREE, FOUR,
	FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN,
	WALET, QUEEN, KING,
};

enum CardSuits
{
	CLUBS, HEARTHS, SPADES, DIAMONDS
};


class Card : public GameObject
{
	glm::vec2 offset;
	glm::vec2 subSize;
	CardRanks rank;
	CardSuits suit;
public:
	static std::string RanksNames[13];
	static std::string SuitsNames[4];
	static std::string RanksNamesEng[13];
	static std::string SuitsNamesEng[4];

	glm::vec2 getOffset() const;
	glm::vec2 getSubSize() const;
	CardRanks getRank() const;
	CardSuits getSuit() const;

	Card(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 offset, glm::vec2 subSize, CardRanks val, CardSuits sign, glm::vec3 color = glm::vec3(1.0f));
	Card();

	bool operator==(const Card & card);

	const std::string valueEnumToString() const;

	void draw(SpriteRenderer * renderer);
	void drawColor(SpriteRenderer * renderer);
	friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

#endif // !CARD_H
