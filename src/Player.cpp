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
    // Gravity
    //position -= glm::vec3(0.0f, GRAVITY_SPEED * deltaTime, 0.0f);

    // Update player position
    speed = glm::vec3(0.0f);

    if(movingForward) {
        speed += glm::normalize(direction);
    }
    if(movingBackward) {
        speed -= glm::normalize(direction);
    }
    if(movingLeft) {
        speed -= glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)))  ;
    }
    if(movingRight) {
        speed += glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) ;
    }

    if(speed != glm::vec3(0.0f))
        speed = glm::normalize(speed) * PLAYER_SPEED;

    //speed.y -= GRAVITY_SPEED;

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