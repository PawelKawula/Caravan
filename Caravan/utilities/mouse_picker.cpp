#include "mouse_picker.h"
#include <iostream>

MousePicker::MousePicker(int scrWidth, int scrHeight, GameObject & selectedObj, Table & table)
	: position(-1, -1), resolution(scrWidth, scrHeight), selectedObject(selectedObj), table(table)
{
	std::cout << "Lista id kart: ";
	for (int rank = 0; rank < Table::RANKS_NUMBER; ++rank)
	{
		for (int suit = 0; suit < Table::SUITS_NUMBER; ++suit)
		{
			int id;
			switch (suit)
			{
			case 0:
				id = 18 + 18 * rank;
				break;
			case 1:
				id = 19 + 18 * rank + 255;
				break;
			case 2:
				id = 20 + 18 * rank + 510;
				break;
			case 3:
				id = 21 + 18 * rank + 765;
				break;
			}
			std::cout << Card::RanksNamesEng[rank] << " " << Card::SuitsNamesEng[suit] << id << std::endl;
			IDs[CardRanks(rank)][CardSuits(suit)] = id;
			if (765 == id)
				std::cout << "EUREKA!";
		}
	}
}

glm::vec2 MousePicker::getPosition() const
{
	return this->position;
}



void MousePicker::clickEvent(double xpos, double ypos)
{
	position.x = xpos;
	position.y = ypos;
	for (int i = 0; i < Table::PLAYERS_NUMBER; ++i)
	{
		std::vector<Card> & hand = table.getPlayerCards(i);
		for (auto card : hand)
			checkSelection(card);
	}
}

bool MousePicker::checkSelection(Card & object)
{
	glFlush();
	glFinish();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLubyte data[3];
	glReadPixels(position.x, resolution.y - position.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	CardSuits suit = object.getSuit();
	CardRanks rank = object.getRank();
	int id;
	switch (suit)
	{
	case 0:
		id = data[0] * 255;
		break;
	case 1:
		id = data[1] * 255 + 255;
		break;
	case 2:
		id = data[2] * 255 + 510;
		break;
	case 3:
		id = data[0] * 255 + 765;
		break;
	}
	std::cout << id << std::endl;
	if (IDs[rank][suit] == id)
	{
		std::cout << "Wybrales: " << object.valueEnumToString() << std::endl;
		return true;
	}
	return false;
}