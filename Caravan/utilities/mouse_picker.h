#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H

#include <glm/glm.hpp>
#include "../game_objects/game_object.h"

class MousePicker
{
	glm::vec2 position;
	GameObject &selectedObject;
public:
	MousePicker(GameObject &selectedObject);

	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 pos);

	bool checkSelection(const GameObject& gameObject);
};

extern MousePicker *mousePicker;
#endif // !MOUSE_PICKER_H
