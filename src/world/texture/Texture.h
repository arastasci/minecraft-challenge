#pragma once
#include "TextureGenerator.h"

struct Texture
{
	Texture(const char* path, bool flip = false)
	{
		textureId = TextureGenerator::generateTexture(path, flip);
	}
	Texture(GLuint textureId)
	{
		this->textureId = textureId;
	}
	void bindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
	void unbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	GLuint textureId;


};