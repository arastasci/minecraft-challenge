#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "texture/Texture.h"
#include <vector>
class Block {
public:
    
    ~Block() = default;
    Block( BlockData* data, glm::vec3 position = glm::vec3(0.0f));
    
    void draw(Shader& shader);

private:
    GLuint VAO, VBO, EBO, VBO_tex;
    Texture texture;
    std::vector<float> texCoords;
    glm::mat4 model;    
};