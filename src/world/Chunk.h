#pragma once

#include <vector>   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "Block.h"
#include "../Player.h"
#include "BlockData.h"
#include "BlockDatabase.h"
#include "../physics/BoundingBox.h"
#include <iostream>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 50

class Chunk {
public:
    Chunk(glm::vec2 position = glm::vec2(0.0f), int height = 46);
    ~Chunk() = default;

    void draw(Shader& shader);
    void handleCollisions(float deltaTime);
    
    BoundingBox boundingBox;
        
    glm::vec3 position;
    glm::vec2 chunkIndices;
private:
    int height;
    void addTopFace(int x, int y, int z,  BlockData* blockId);
    void addBottomFace(int x, int y, int z, BlockData* blockId);
    void addFrontFace(int x, int y, int z, BlockData* blockId);
    void addBackFace(int x, int y, int z, BlockData* blockId);
    void addLeftFace(int x, int y, int z, BlockData* blockId);
    void addRightFace(int x, int y, int z, BlockData* blockId);

    void addVertices(int x, int y, int z, float faceVertices[] );
    
    std::vector<float> vertices;
    std::vector<float> tex_coords;
    
    BlockId blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    GLuint VAO, VBO, EBO, VBO_tex;
};