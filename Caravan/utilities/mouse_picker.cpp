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
				id = 19 + 18 * rank;
				break;
			case 2:
				id = 20 + 18 * rank;
				break;
			case 3:
				id = 21 + 18 * rank;
				break;
			}
			std::cout << Card::RanksNamesEng[rank] << " " << Card::SuitsNamesEng[suit] << id << std::endl;
			IDs[CardRanks(rank)][CardSuits(suit)] = id;
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
	GLfloat data[3];
	glReadPixels(position.x, resolution.y - position.y, 1, 1, GL_RGB, GL_FLOAT, data);
	// TODO: zle przemyslane wywolywanie id powinienem spradziwc czy jakis kolor jset lub nie
	int pickedId, objectId;
	objectId = IDs[object.getRank()][object.getSuit()];
	if (data[0] != 0 && data[1] != 0)
		pickedId = data[0] * 255;
	else
		pickedId = data[0] * 255 + data[1] * 255 + data[2] * 255;
	std::cout << "pickedId: " << pickedId << ", objectId: " << objectId << std::endl;
	if (pickedId == objectId)
	{
		std::cout << "Wybrales: " << object.valueEnumToString() << std::endl;
		return true;
	}
	return false;
}