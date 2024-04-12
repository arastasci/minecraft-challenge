#include "World.h"

void World::init()
{
	for (int i = -CHUNK_COUNT / 2; i < CHUNK_COUNT / 2; i++)
	{
		for (int j = - CHUNK_COUNT / 2; j < CHUNK_COUNT / 2; j++)
		{
			chunks.push_back(new Chunk(glm::vec2(i, j), CHUNK_HEIGHT + ( i + j)));
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

void World::handleCollisions(float deltaTime){
	Player *player = Player::getInstance();

	for (Chunk* chunk : chunks)
	{
		BoundingBox prediction = player->boundingBox;
		prediction.x += player->speed.x * deltaTime;
		prediction.y += player->speed.y * deltaTime;
		prediction.z += player->speed.z * deltaTime;

		if(chunk->boundingBox.intersects(prediction))
		{
			std::cout << "Collision detected" << chunk->chunkIndices.x <<  chunk->chunkIndices.y << std::endl;
			chunk->handleCollisions(deltaTime);
		}
	}
}

void World::tick(float deltaTime)
{
	handleCollisions(deltaTime);
}