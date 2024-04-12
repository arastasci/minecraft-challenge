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


Chunk::Chunk(glm::vec3 position) : position(position)
{

    BlockDatabase db;
    BlockData *data = db.blockDatabase[1];

    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_HEIGHT; j++)
        {
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
                if (j == CHUNK_HEIGHT - 1)
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