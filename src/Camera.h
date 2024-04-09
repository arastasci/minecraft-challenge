#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Camera {
public:
    ~Camera();

    void draw(Shader& shader);
    void translate(glm::vec3 position);

    static Camera* getInstance();

    void operator=(const Camera &) = delete;

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;

protected:
    Camera();

    static Camera* instance;

private:
    glm::mat4 projection;
};