#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include "../utilities/texture.h"
#include "../utilities/resource_manager.h"
#include "../utilities/sprite_renderer.h"

class GameObject
{
	glm::vec2	size, position, velocity;
	glm::vec3	color;
	GLfloat		rotation;
	Texture2D	sprite;
	bool		renderColor;
public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), GLfloat rotation = 0.0f, glm::vec2 velocity = glm::vec2(0, 0));

	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 pos);
	glm::vec2 getSize() const;
	void setSize(glm::vec2 size);
	glm::vec3 getColor() const;
	void setColor(glm::vec3 color);
	GLfloat getRotation() const;
	void setRotation(GLfloat rotation);
	void setRenderColor(bool renderColor);

	bool operator<(const GameObject &object) const;

	bool animate_slide(glm::vec2 pos, GLfloat dt);
	bool animate_push(glm::vec2 pos, GLfloat dt);
	virtual void draw(SpriteRenderer * renderer);
	virtual void drawColor(SpriteRenderer * renderer);
	void subDraw(SpriteRenderer * renderer, glm::vec2 offset, glm::vec2 subSize);
	void subDrawColor(SpriteRenderer * renderer, glm::vec2 offset, glm::vec2 subSize);
};
#endif // !GAME_OBJECT_H

