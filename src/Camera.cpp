#include "Camera.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
    projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.f);

    position = glm::vec3(0.0f, 10.0f, 3.0f);
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::draw(Shader& shader)
{
    glm::mat4 view = glm::lookAt(position, position + direction, up);
    view = glm::scale(view, glm::vec3(1.0f));

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

Camera* Camera::getInstance(){
    if(instance == nullptr)
        instance = new Camera();
    
    return instance;
}

Camera* Camera::instance = nullptr;