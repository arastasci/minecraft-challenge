#pragma once

#include <vector>   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "Block.h"
#include "BlockData.h"
#include "BlockDatabase.h"

#define CHUNK_SIZE 1
#define CHUNK_HEIGHT 1

class Chunk {
public:
    Chunk(glm::vec3 position = glm::vec3(0.0f));
    ~Chunk() = default;

    void draw(Shader& shader);
private:

    void addFace(glm::vec3 chunkPosition, glm::vec3 blockPosition, BlockData* data);
    void addTopFace(int x, int y, int z, glm::vec3 chunkPosition,  BlockData* blockId);
    void addBottomFace(int x, int y, int z, glm::vec3 chunkPosition, BlockData* blockId);
    void addFrontFace(int x, int y, int z, glm::vec3 chunkPosition, BlockData* blockId);
    void addBackFace(int x, int y, int z, glm::vec3 chunkPosition, BlockData* blockId);
    void addLeftFace(int x, int y, int z, glm::vec3 chunkPosition, BlockData* blockId);
    void addRightFace(int x, int y, int z, glm::vec3 chunkPosition, BlockData* blockId);

    void addVertices(int x, int y, int z, float faceVertices[], glm::vec3 chunkPosition );

    glm::vec3 position;
    std::vector<float> vertices;
    std::vector<float> tex_coords;
    BlockId blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    GLuint VAO, VBO, EBO, VBO_tex;
};