#pragma once
#include <glad/glad.h>
#include <stb_image.h>
class TextureGenerator
{
public:
	TextureGenerator() = default;
	~TextureGenerator() = delete;
	static GLuint generateTexture(const char* path, bool flip = false);
private:

};

