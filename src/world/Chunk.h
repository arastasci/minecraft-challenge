#pragma once

#include <vector>   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "Block.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 50

class Chunk {
public:
    Chunk(glm::vec3 position = glm::vec3(0.0f));
    ~Chunk() = default;

    void draw(Shader& shader);
private:
    glm::vec3 position;
    std::vector<float> vertices;

    GLuint VAO, VBO, EBO;
    Texture texture;
};