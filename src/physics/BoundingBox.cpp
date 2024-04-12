#include "BoundingBox.h"

BoundingBox::BoundingBox(float x, float y, float z, float width, float height, float depth) 
: x(x), y(y), z(z), width(width), height(height), depth(depth) {}

BoundingBox::BoundingBox(glm::vec3 position, glm::vec3 size) :
     x(position.x), y(position.y), z(position.z), width(size.x), height(size.y), depth(size.z) {}
    
 bool BoundingBox::intersects(BoundingBox& other) {
        return (x < other.x + other.width &&
                x + width > other.x &&
                y < other.y + other.height &&
                y + height > other.y &&
                z < other.z + other.depth &&
                z + depth > other.z);
}