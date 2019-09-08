#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include "texture.h"
#include "shader.h"

class ResourceManager
{
	static std::map<std::string, Texture2D> textures;
	static std::map<std::string, Shader> shaders;
	static Shader loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
public:
	static Shader loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	static Shader& getShader(std::string name);
	static Texture2D loadTexture(const GLchar* file, GLboolean alpha, std::string name);
	static Texture2D& getTexture(std::string name);
	static void clear();
};
#endif // !RESOURCE_MANAGER_H

