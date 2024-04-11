#include "Chunk.h"

Chunk::Chunk(glm::vec3 position) : position(position)
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_HEIGHT; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                blocks[i][j][k].setPosition(glm::vec3(i, j, k));
            }
        }
    }
}

void Chunk::draw(Shader &shader)
{
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_HEIGHT; j++)
        {
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                blocks[i][j][k].draw(shader);
            }
        }
    }
}