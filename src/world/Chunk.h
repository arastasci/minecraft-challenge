#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "Block.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 1

class Chunk {
public:
    Chunk(glm::vec3 position = glm::vec3(0.0f));
    ~Chunk()=default;
    void draw(Shader& shader);

private:
    glm::vec3 position;
    Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
};