#include "Player.h"

Player::Player(glm::vec3 position, glm::vec3 direction) : position(position), direction(direction),
                                    boundingBox(position, PLAYER_SIZE)
{}

Player* Player::getInstance() {
    if(instance == nullptr) {
        instance = new Player();
    }
    return instance;
} 

Player* Player::instance = nullptr;

void Player::tick(float deltaTime) {

    // Update player position
    acceleration = glm::vec3(0.0f);

    if(movingForward) {
        acceleration += glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
    }
    if(movingBackward) {
        acceleration -= glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
    }
    if(movingLeft) {
        acceleration -= glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)))  ;
    }
    if(movingRight) {
        acceleration += glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) ;
    }
    if(acceleration != glm::vec3(0.0f))
        acceleration = glm::normalize(acceleration) * PLAYER_SPEED;

    if(isOnGround && jumping){
        isOnGround = false;
        acceleration.y += JUMP_SPEED;
    }

    acceleration.y -= GRAVITY_SPEED;

    speed.x = speed.x * 0.9f + (acceleration.x * deltaTime);
    speed.y = speed.y * 0.9f + (acceleration.y * deltaTime);
    speed.z = speed.z * 0.9f + (acceleration.z * deltaTime);

    if(speed.y > 100.0f)
        speed.y = 100.0f;
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

    std::cout << direction.x << direction.y << direction.z << std::endl;
}