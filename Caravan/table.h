#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include "game.h"
#include "game_objects/card.h"
#include "utilities/texture.h"
#include <exception>
#include "game_objects/player.h"

typedef std::pair<std::string, Card> CardPair;
typedef std::pair<std::string, Card*> CardPairPointer;
typedef std::map<CardSuits, Card> CardSuitsType;

class Table
{
public:
	struct CardConstructor
	{
		glm::vec2 initialOffset;
		glm::vec2 offset;
		glm::vec2 size;
		Texture2D & sprite;
	};
	static const int RANKS_NUMBER = 13;
	static const int SUITS_NUMBER = 4;
	static const int PLAYERS_NUMBER = 2;
private:
	int hand;
	int width;
	int height;
	double scale;
	CardConstructor cardConstructor;
	
	Player players[PLAYERS_NUMBER];
	std::map<CardRanks, std::map<CardSuits, Card>> cards;
	std::stack<Card> cardStack;
	std::list<std::pair<glm::vec2, Card*>> animatedObjectsStack;
public:
	Table(int width, int height, double scale,
		CardConstructor & constructor, int hand,
		std::string name1, std::string name2);

	void newStack();
	bool tossTopCardFromStack(Player & player);
	void tossCards();
	bool passCard(Player & p1, Player & p2, CardRanks rank, CardSuits suit);
	std::vector<Card> & getPlayerCards(int i);
	//void moveCard(std::string name, glm::vec2 destination);

	void processInput(GLfloat dt, SpriteRenderer * renderer);
	void update(GLfloat dt);
	void render(SpriteRenderer * renderer);
};

#endif // !TABLE_H