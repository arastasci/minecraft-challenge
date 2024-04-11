#pragma once
#include "TextureAtlas.h"
#include "../BlockData.h"

struct Texture
{
	Texture() = default;
	Texture(BlockData data)
	{
		texHeight = 1.0f / 16.0f;
		texWidth = 1.0f / 16.0f;
		topTexCoords = TextureAtlas::getInstance()->getTextureCoords(data.TopTextureIndices);
		bottomTexCoords = TextureAtlas::getInstance()->getTextureCoords(data.BottomTextureIndices);
		sideTexCoords = TextureAtlas::getInstance()->getTextureCoords(data.SideTextureIndices);
		
	}

	glm::vec2 topTexCoords;
	glm::vec2 bottomTexCoords;
	glm::vec2 sideTexCoords;
	float texWidth, texHeight;


};