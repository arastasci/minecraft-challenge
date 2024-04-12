#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct BoundingBox {
    float x, y, z;
    float width, height, depth;

    BoundingBox() = default;
    BoundingBox(float x, float y, float z, float width, float height, float depth);
    BoundingBox(glm::vec3 position, glm::vec3 size);
    bool intersects(BoundingBox& other);
};