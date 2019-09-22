#ifndef PLAYER_H
#define PLAYER_H

#include "slot.h"
#include <vector>

class Player
{
	int hand;
	std::string name;
	std::vector<Slot> slots;
	std::vector<Slot> actionSlots;
	std::vector<Card> cards;
	std::vector<Card> actionCards;
	class Caravan
	{
		enum Direction { UP, DOWN };
		std::vector<Slot> slots;
		std::vector<Slot> actionSlots;
		void updateValue();
		int value;
	public:
		bool addCard(const Card & card);
	};
	Caravan caravans[3];
public:
	int getHandSize() const;
	Player(std::string name);
	void reset();

	bool gotCard(CardRanks rank, CardSuits suit) const;
	bool addCard(Card card);
	bool addCard(Card card, int slotNumber);
	bool passActionCardToCaravan(Slot & playerSlot, Slot & caravanActionSlot);
	bool passCardToCaravan(Slot & playerSlot, Slot & caravanSlot);
	bool removeCard(CardRanks rank, CardSuits suit);
	Card& getCard(CardRanks rank, CardSuits suit);
	Card& getCard(int index);

	void draw(SpriteRenderer * renderer);
	void drawColor(SpriteRenderer * renderer);
};

#endif // !PLAYER_H



