#include "World.h"

void World::init()
{
	for (int i = -4; i < CHUNK_COUNT; i++)
	{
		for (int j = -4; j < CHUNK_COUNT; j++)
		{
			chunks.push_back(new Chunk(glm::vec3(i * 16.0f, -50.0f, j * 16.0f)));
		}
	}
}

void World::render(Shader& shader)
{
	for (Chunk* chunk : chunks)
	{
		chunk->draw(shader);
	}
}