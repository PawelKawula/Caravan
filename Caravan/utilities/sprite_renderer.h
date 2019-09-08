#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader & shader);
	~SpriteRenderer();
	void drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10),
		GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), bool renderColor = false);
	void drawSubSprite(Texture2D texture, glm::vec2 position, glm::vec2 offset, glm::vec2 subSize,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f),
		bool renderColor = false);
private:
	Shader shader;
	GLuint quadVAO, quadVBO;

	void initRenderData(bool first);
	void initSubRenderData(Texture2D & texture, glm::vec2 offset, glm::vec2 subSize);
};
#endif // !SPRITE_RENDERER
