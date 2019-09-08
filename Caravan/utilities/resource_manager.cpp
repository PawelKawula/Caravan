#include "resource_manager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

std::map<std::string, Shader>		ResourceManager::shaders;
std::map<std::string, Texture2D>	ResourceManager::textures;

Shader ResourceManager::loadShader(const GLchar* vShaderPath, const GLchar* fShaderPath, const GLchar* gShaderPath, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderPath, fShaderPath, gShaderPath);
	return shaders[name];
}

Shader & ResourceManager::getShader(std::string name)
{
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const GLchar * file, GLboolean alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture2D & ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	for (auto iter : shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderPath, const GLchar* fShaderPath, const GLchar* gShaderPath)
{
	std::string vertexString, fragmentString, geometryString;
	try
	{
		std::ifstream vertexFile, fragmentFile;
		vertexFile.open(vShaderPath);
		fragmentFile.open(fShaderPath);
		if (!vertexFile.is_open())
			std::cout << "ERROR: Couldn't load vertex shader" << std::endl;
		if (!fragmentFile.is_open())
			std::cout << "ERROR: Couldn't load fragment shader" << std::endl;

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();

		vertexString = vShaderStream.str();
		fragmentString = fShaderStream.str();
		if (gShaderPath)
		{
			std::ifstream geometryFile;
			geometryFile.open(gShaderPath);
			if (!geometryFile.is_open())
				std::cout << "ERROR: Could't load geometry shader" << std::endl;
			std::stringstream gShaderStream;
			gShaderStream << geometryFile.rdbuf();
			geometryString = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error can't read shader files" << std::endl;
	}

	const GLchar *vShaderSource, *fShaderSource, *gShaderSource;
	vShaderSource = vertexString.c_str();
	fShaderSource = fragmentString.c_str();
	gShaderSource = geometryString.c_str();
	
	Shader shader;
	shader.Compile(vShaderSource, fShaderSource, gShaderPath != nullptr ? gShaderSource : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	int width, height, nrChannels;
	unsigned char * data = stbi_load(file, &width, &height, &nrChannels, 0);

	texture.Generate(width, height, data);
	stbi_image_free(data);

	return texture;
}
