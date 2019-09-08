#include "mouse_picker.h"
#include <iostream>

MousePicker::MousePicker(GameObject &selectedObject)
	: position(glm::vec2(0, 0)), selectedObject(selectedObject)
{

}

glm::vec2 MousePicker::getPosition() const
{
	return this->position;
}

void MousePicker::setPosition(glm::vec2 pos)
{
	this->position = pos;
}

bool MousePicker::checkSelection(const GameObject& gameObject)
{
	bool selectionX, selectionY;
	glm::vec2 objectPosition = gameObject.getPosition();
	glm::vec2 objectSize = gameObject.getSize();
	if (position.x > objectPosition.x && position.x < objectPosition.x + objectSize.x)
		selectionX = true;
	else
		selectionX = false;
	if (position.y > objectPosition.y && position.y < objectPosition.y + objectSize.x)
		selectionY = true;
	else
		selectionY = false;
	return selectionX && selectionY;
}