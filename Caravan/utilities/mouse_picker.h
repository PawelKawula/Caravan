#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H

#include <glm/glm.hpp>
#include "../game_objects/game_object.h"
#include "../game_objects/card.h"
#include "../table.h"

class MousePicker
{
	glm::vec2 resolution;
	glm::vec2 position;
	Card * selectedObject;
	bool focus;
	Table & table;
public:
	std::map<CardRanks, std::map<CardSuits, int>> IDs;

	MousePicker(int scrWidth, int scrHeight, Card * selectedObject, Table & table);

	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 position);
	void setPosition(float x, float y);
	bool getFocus() const;
	void setFocus(bool focus);
	Card * getSelectedObject();

	void update();
	void move();
	void moveEvent(double xpos, double ypos);
	bool checkSelection(Card & object);
};

extern MousePicker *mousePicker;
#endif // !MOUSE_PICKER_H
