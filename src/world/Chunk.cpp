#include "Chunk.h"


float back_vertices[] = 
{
        0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
};


float front_vertices[] =
{
        -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};

float left_vertices[] =
{
		-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
};

float right_vertices[] =
{
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};

float bottom_vertices[]
=
{
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
};

float top_vertices[] =
{
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f
};


Chunk::Chunk(glm::vec2 indices, int height) : position( CHUNK_SIZE * indices.x, 0.0f, CHUNK_SIZE * indices.y), chunkIndices(indices)
    // boundingBox(glm::vec3(position.x, -100000, position.z), glm::vec3(CHUNK_SIZE, 10000000000, CHUNK_SIZE))
{
    BlockDatabase db;
    BlockData *grassData = db.blockDatabase[1];
    BlockData * stoneData = db.blockDatabase[3];
    BlockData * dirtData = db.blockDatabase[2];

    boundingBox = BoundingBox(glm::vec3(position.x, -100000, position.z), glm::vec3(CHUNK_SIZE, 10000000000, CHUNK_SIZE));
    
    std::cout << "Chunk created at: " << position.x << " " << position.z << std::endl;
    std::cout << "Bounding box of chunk" << chunkIndices.x << chunkIndices.y << ": " << boundingBox.x << " " << boundingBox.y << " " << boundingBox.z << std::endl;
    this->height = height;
    
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < height; j++)
        {
            BlockData *data = nullptr;

                if(j < 20)
                {
                    data = stoneData;
                }
                else if(j != height - 1)
                {
                    data = dirtData;
                }
                else
                {
                    data = grassData;
                }
            for (int k = 0; k < CHUNK_SIZE; k++)
            {
                if (i == 0)
                {
                    addLeftFace(i, j, k, data);
                }
                if (i == CHUNK_SIZE - 1)
				{
					addRightFace(i, j, k, data);
				}
                if (j == 0)
                {
					addBottomFace(i, j, k, data);
                }
                if (j == height - 1)
				{
                addTopFace(i, j, k, data);
				}
                if (k == 0)
				{
					addBackFace(i, j, k, data);
				}
                if (k == CHUNK_SIZE - 1)
				{
                    addFrontFace(i, j, k, data);
				}

                blocks[i][j][k] = data->id;

            }
        }
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); 

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO_tex);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_tex);
    glBufferData(GL_ARRAY_BUFFER, tex_coords.size() * sizeof(float), tex_coords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void Chunk::addVertices(int x, int y, int z, float faceVertices[])
{
    for (int i = 0; i < 18; i++)
    {
        if (i % 3 == 0)
        {
            this->vertices.push_back(faceVertices[i] + x + position.x);
        }
        else if (i % 3 == 1)
        {
            this->vertices.push_back(faceVertices[i] + y + position.y);
        }
        else 
        {
            this->vertices.push_back(faceVertices[i] + z + position.z);
        }
    }
}


void Chunk::addTopFace(int x, int y, int z, BlockData* data)
{
    addVertices(x, y, z, top_vertices);

    tex_coords.insert(tex_coords.end(), data->topFaceTexCoords.begin(), data->topFaceTexCoords.end());
}

void Chunk::addBottomFace(int x, int y, int z, BlockData* data)
{
    addVertices(x, y, z, bottom_vertices);
	tex_coords.insert(tex_coords.end(), data->bottomFaceTexCoords.begin(), data->bottomFaceTexCoords.end());
}

void Chunk::addFrontFace(int x, int y, int z, BlockData* data)
{
    addVertices(x, y, z, front_vertices);
    tex_coords.insert(tex_coords.end(), data->sideFaceTexCoords.begin(), data->sideFaceTexCoords.end());
}

void Chunk::addBackFace(int x, int y, int z, BlockData* data)
{
    addVertices(x, y, z, back_vertices);
    tex_coords.insert(tex_coords.end(), data->sideFaceTexCoords.begin(), data->sideFaceTexCoords.end());
}

void Chunk::addLeftFace(int x, int y, int z, BlockData* data)
{

    addVertices(x, y, z, left_vertices);
	tex_coords.insert(tex_coords.end(), data->sideFaceTexCoords.begin(), data->sideFaceTexCoords.end());
}

void Chunk::addRightFace(int x, int y, int z, BlockData* data)
{
    addVertices(x, y, z, right_vertices);
    tex_coords.insert(tex_coords.end(), data->sideFaceTexCoords.begin(), data->sideFaceTexCoords.end());
}

void Chunk::draw(Shader &shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 vertices (6 faces * 2 triangles per face * 3 vertices per triangle
    glDrawArrays(GL_TRIANGLES, 0, 36 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT); // 36 vertices (6 faces * 2 triangles per face * 3 vertices per triangle
    glBindVertexArray(0);
}

void::Chunk::handleCollisions(float deltaTime)
{
    Player *player = Player::getInstance();

    for(int i = 0; i < CHUNK_SIZE; i++)
    {
        for(int j = 0; j < height; j++)
        {
            for(int k = 0; k < CHUNK_SIZE; k++)
            {
                if(blocks[i][j][k] != BlockId::Air)
                {
                    BoundingBox block(glm::vec3(i + position.x, j + position.y, k + position.z), glm::vec3(1.0f, 1.0f, 1.0f));
                    
                    BoundingBox prediction = player->boundingBox;
                    prediction.x += player->speed.x * deltaTime;
                    prediction.y += player->speed.y * deltaTime;
                    prediction.z += player->speed.z * deltaTime;

                    if(prediction.intersects(block))
                    {
                        std::cout << "Collision detected" << i << j << k << std::endl;

                        BoundingBox predictionX = player->boundingBox;
                        predictionX.x += player->speed.x * deltaTime;
                        if(predictionX.intersects(block))
                        {
                            player->speed.x = 0.0f;
                        }

                        BoundingBox predictionY = player->boundingBox;
                        predictionY.y += player->speed.y * deltaTime;
                        if(predictionY.intersects(block))
                        {
                            if(player->speed.y <= 0.0f)
                            {
                                player->isOnGround = true;
                            }
                            player->speed.y = 0.0f;
                        }

                        BoundingBox predictionZ = player->boundingBox;
                        predictionZ.z += player->speed.z * deltaTime;
                        if(predictionZ.intersects(block))
                        {
                            player->speed.z = 0.0f;
                        }
                    }
                }
            }
        }
    }
}