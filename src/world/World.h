#pragma once
#include <vector>
#include "Chunk.h"
#include "../Shader.h"
#include "../Player.h"
#include <iostream>
#define CHUNK_COUNT 2


class World 
{
public:
	World() = default;
	~World() = default;
	void init();
	void render(Shader& shader);
	void handleCollisions(float deltaTime);

	std::vector<Chunk*> chunks;
	void tick(float deltaTime);
};

