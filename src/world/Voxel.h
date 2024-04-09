#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"

class Voxel {
public:
    
    Voxel() = default;
    ~Voxel() = default;
    Voxel(glm::vec3 position);
    
    void draw(Shader& shader);

private:
    GLuint VAO, VBO;
    glm::mat4 model;    
};