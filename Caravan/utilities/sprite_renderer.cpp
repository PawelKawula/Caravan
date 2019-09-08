#include "sprite_renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

SpriteRenderer::SpriteRenderer(Shader & shader)
	: shader(shader)
{
	this->initRenderData(true);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData(bool first)
{	
	GLfloat vertices[] = {
		// Pos // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	if (first)
	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
	}
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	if (first)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	else
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindVertexArray(quadVAO);
	if (first)
		glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::initSubRenderData(Texture2D & texture, glm::vec2 offset, glm::vec2 subSize)
{
	//if (offset.x + subSize.x > texture.Width || offset.y + subSize.y > texture.Height)
	//	std::cout << "ERROR: Inappropriate offset values for SpriteRenderer::drawSubSprite function" << std::endl;

	glm::vec2 TexCoords[2][2];

	TexCoords[0][0] = glm::vec2(offset.x / texture.Width, offset.y / texture.Height);

	TexCoords[1][0] = TexCoords[0][1] = TexCoords[0][0];

	TexCoords[0][1].y += subSize.y / texture.Height;
	TexCoords[1][0].x += subSize.x / texture.Width;

	TexCoords[1][1].x = TexCoords[1][0].x;
	TexCoords[1][1].y = TexCoords[0][1].y;

	GLfloat vertices[] = {
		// Pos // Tex
		0.0f, 1.0f, TexCoords[0][1].x, TexCoords[0][1].y,
		1.0f, 0.0f, TexCoords[1][0].x, TexCoords[1][0].y,
		0.0f, 0.0f, TexCoords[0][0].x, TexCoords[0][0].y,
		0.0f, 1.0f, TexCoords[0][1].x, TexCoords[0][1].y,
		1.0f, 1.0f, TexCoords[1][1].x, TexCoords[1][1].y,
		1.0f, 0.0f, TexCoords[1][0].x, TexCoords[1][0].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size,
	GLfloat rotate, glm::vec3 color, bool renderColor)
{
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 0.0f));

	this->shader.SetVector3f("spriteColor", color);
	this->shader.SetMatrix4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}



void SpriteRenderer::drawSubSprite(Texture2D texture, glm::vec2 position, glm::vec2 offset, glm::vec2 subSize,
	glm::vec2 size, GLfloat rotate, glm::vec3 color, bool renderColor)
{
	this->initSubRenderData(texture, offset, subSize);
	this->drawSprite(texture, position, size, rotate, color, renderColor);
	this->initRenderData(false);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

