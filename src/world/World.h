#pragma once
#include <vector>
#include "Chunk.h"
#include "../Shader.h"

#define CHUNK_COUNT 4


class World 
{
public:
	World() = default;
	~World() = default;
	void init();
	void render(Shader& shader);

	std::vector<Chunk*> chunks;
};

