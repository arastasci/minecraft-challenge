#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Camera {
public:
    ~Camera();
    static Camera* getInstance();
    void operator=(const Camera &) = delete;

    void draw(Shader& shader);

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;

protected:
    Camera();
    static Camera* instance;

    float sensitivity = 0.9f;
private:
    glm::mat4 projection;
};