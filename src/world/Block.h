#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "texture/Texture.h"
class Block {
public:
    
    Block() = default;
    ~Block() = default;
    Block(glm::vec3 position);
    
    void draw(Shader& shader);

private:
    GLuint VAO, VBO, EBO;
    Texture texture;
    glm::mat4 model;    
};