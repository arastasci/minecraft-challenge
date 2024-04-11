#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/ext/vector_float2.hpp>
class TextureAtlas
{
public:
	static TextureAtlas* getInstance();
	TextureAtlas();
	~TextureAtlas() = default;
	GLuint generateTexture(const char* path, bool flip = false);
	glm::vec2 getTextureCoords(glm::vec2 indices);
	float textureWidth, textureHeight;

private:
	static TextureAtlas* instance;
};

