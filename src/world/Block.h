#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "texture/Texture.h"

class Block {
public:
    glm::vec3 position;

    Block(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    ~Block() = default;
};