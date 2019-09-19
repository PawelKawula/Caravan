#include "mouse_picker.h"
#include <iostream>
#include "../game.h"

extern GLFWwindow * window;

MousePicker::MousePicker(int scrWidth, int scrHeight, Card * selectedObject, Table & table)
	: position(-1, -1), resolution(scrWidth, scrHeight), selectedObject(selectedObject), focus(false), table(table)
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

void MousePicker::setPosition(glm::vec2 position)
{
	this->position = position;
}

void MousePicker::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

bool MousePicker::getFocus() const
{
	return focus;
}

void MousePicker::setFocus(bool focus)
{
	this->focus = focus;
}

Card * MousePicker::getSelectedObject()
{
	return selectedObject;
}

void MousePicker::update()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	this->position.x = xpos;
	this->position.y = ypos;
	if (!focus)
	{
		std::cout << "Wybieram nowa karte" << std::endl;
		for (int i = 0; i < Table::PLAYERS_NUMBER; ++i)
		{
			std::vector<Card> & hand = table.getPlayerCards(i);
			for (auto & card : hand)
			{
				if (checkSelection(card))
				{
					std::cout << "Wybrano: " << card.valueEnumToString() << ", adres: " << &card << std::endl;
					this->selectedObject = &card;
					this->focus = true;
					std::cout << "Adres karty w mousePicker: " << &this->selectedObject << std::endl;
					return;
				}
			}
		}
	}
}



bool MousePicker::checkSelection(Card & object)
{
	glFlush();
	glFinish();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLfloat data[3];
	glReadPixels(position.x, resolution.y - position.y, 1, 1, GL_RGB, GL_FLOAT, data);
	// TODO: Wybiera dobrze tylko clubs ktore jest na czerwonych
	int pickedId, objectId;
	objectId = IDs[object.getRank()][object.getSuit()];
	pickedId = data[0] * 255;
	if (data[0] != 0 && data[1] != 0 && data[2] != 0)
		pickedId = pickedId - 1;
	else if (data[1] != 0)
		pickedId = data[1] * 255 + 2;
	else if (data[2] != 0)
		pickedId = data[2] * 255 - 1;
	// std::cout << "Kolor: " << data[0] << ", " << data[1] << ", " << data[2] <<", pickedId: " << pickedId << ", objectId: " << objectId << std::endl;
	if (pickedId == objectId)
	{
		std::cout << "Wybrales: " << object.valueEnumToString() << std::endl;
		return true;
	}
	return false;
}