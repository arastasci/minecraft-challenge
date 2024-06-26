#pragma once
#include <glm/vec2.hpp>
#include "texture/TextureAtlas.h"
#include <vector>
#include "BlockTypes.h"
struct BlockData
{
	BlockId id;
	glm::vec2 TopTextureIndices;
	glm::vec2 BottomTextureIndices;
	glm::vec2 SideTextureIndices;

	glm::vec2 TopTextureCoords;
	glm::vec2 BottomTextureCoords;
	glm::vec2 SideTextureCoords;
	
	std::vector<float> sideFaceTexCoords;
	std::vector<float> topFaceTexCoords;
	std::vector<float> bottomFaceTexCoords;


	BlockData(BlockId id, glm::vec2 ttI, glm::vec2 btI, glm::vec2 stI)
		:id(id), TopTextureIndices(ttI), BottomTextureIndices(btI), SideTextureIndices(stI)
	{
		float width = TextureAtlas::getInstance()->textureWidth;
		float height = TextureAtlas::getInstance()->textureHeight;
		TopTextureCoords = glm::vec2(TopTextureIndices.x * width,
			TopTextureIndices.y * height);
		BottomTextureCoords = glm::vec2(BottomTextureIndices.x * width,
			BottomTextureIndices.y * height);
		SideTextureCoords = glm::vec2(SideTextureIndices.x * width,
			SideTextureIndices.y * height);



		sideFaceTexCoords =
		{
			SideTextureCoords.x, SideTextureCoords.y,
			SideTextureCoords.x + width, SideTextureCoords.y,
			SideTextureCoords.x + width, SideTextureCoords.y + height,
			SideTextureCoords.x + width,  SideTextureCoords.y + height,
			SideTextureCoords.x,  SideTextureCoords.y + height,
			SideTextureCoords.x, SideTextureCoords.y,
		};
		bottomFaceTexCoords = {
			BottomTextureCoords.x, BottomTextureCoords.y,
			BottomTextureCoords.x + width, BottomTextureCoords.y,
			BottomTextureCoords.x + width, BottomTextureCoords.y + height,
			BottomTextureCoords.x + width,  BottomTextureCoords.y + height,
			BottomTextureCoords.x,  BottomTextureCoords.y + height,
			BottomTextureCoords.x, BottomTextureCoords.y,
		};
		topFaceTexCoords = {
			TopTextureCoords.x, TopTextureCoords.y,
			TopTextureCoords.x + width, TopTextureCoords.y,
			TopTextureCoords.x + width, TopTextureCoords.y + height,
			TopTextureCoords.x + width,  TopTextureCoords.y + height,
			TopTextureCoords.x,  TopTextureCoords.y + height,
			TopTextureCoords.x, TopTextureCoords.y

		};
	}

};

