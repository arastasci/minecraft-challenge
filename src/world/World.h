#pragma once
#include <vector>
#include "Chunk.h"
#include "../Shader.h"
class World 
{
public:
	World() = default;
	~World() = default;
	void init();
	void render(Shader& shader);

	std::vector<Chunk*> chunks;
};

