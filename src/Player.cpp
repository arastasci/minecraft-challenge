#include "Player.h"

Player::Player(glm::vec3 position) : position(position) {}

Player* Player::getInstance() {
    if(instance == nullptr) {
        instance = new Player();
    }
    return instance;
} 

Player* Player::instance = nullptr;

void Player::tick(float deltaTime) {
    // Gravity
    position -= glm::vec3(0.0f, GRAVITY_SPEED * deltaTime, 0.0f);

    // Update player position
    Camera *camera = Camera::getInstance();

    camera->position = position;
    camera->direction = direction;
}

void Player::moveForward(float deltaTime) {
    position += direction * speed * deltaTime;    
}

void Player::moveBackward(float deltaTime) {
    position -= direction * speed * deltaTime;
}

void Player::moveLeft(float deltaTime) {
    position -= glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
}

void Player::moveRight(float deltaTime ) {
    position += glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * speed * deltaTime;
}

void Player::rotate(float xoffset, float yoffset) {
    // Update player rotation
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    direction = glm::normalize(direction);
}