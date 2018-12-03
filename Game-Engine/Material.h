#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glm.hpp>
#include "Exports.h"
#include "Texture.h"
using namespace std;
using namespace glm;

class Texture;

/*
A class that is used to generate vertex and pixel shaders that will ultimately define
the way the entities will look like in the game.
*/

class ENGINE_API Material
{
private:
	Texture* _texture;
	
	unsigned int _programID;
	unsigned int _matrixID;
	unsigned int _textureID;

	Material();
	~Material();
	
	unsigned int loadShaders(const string& vertexShaderPath, const string& pixelShaderPath);

public:

	static Material* generateMaterial(const string& vertexShaderPath, const string& pixelShaderPath);
	static void destroyMaterial(Material* material);
	
	void setMatrixProperty(const char* propertyName, mat4& matrix);
	void setTexture(Texture* texture, const char* propertyName);
	void bind();
	void bindTexture();

	inline unsigned int getTextureWidth() const { return _texture->getWidth(); }
	inline unsigned int getTextureHeight() const { return _texture->getHeight(); }
};