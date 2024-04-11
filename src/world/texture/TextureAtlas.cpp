#include "TextureAtlas.h"
#include <iostream>	

TextureAtlas* TextureAtlas::instance = nullptr;

//float textureWidth = 1.0f / 16.0f;
//float textureHeight = 1.0f / 16.0f;
TextureAtlas::TextureAtlas()
{

}
TextureAtlas* TextureAtlas::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureAtlas();
		instance->textureWidth = 1.0f / 16.0f;
		instance->textureHeight = 1.0f / 16.0f;
	}
	return instance;
}

glm::vec2 TextureAtlas::getTextureCoords(glm::vec2 indices)
{
	float x = indices.x * textureWidth;
	float y = indices.y * textureHeight;
	return glm::vec2(x , y);

}


GLuint TextureAtlas::generateTexture(const char* path, bool flip)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (flip)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);


	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}