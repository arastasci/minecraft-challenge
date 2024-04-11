#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class Player {

public:
    ~Player() = default;

    static Player* getInstance();
    void operator=(const Player &) = delete;


    void tick();
    
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void rotate(float pitch, float yaw);
    
    private:
    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    static Player* instance;

    glm::vec3 position;
    glm::vec3 direction;
    float speed = 1.0f;
    float sensitivity = 0.9f;

    float yaw = -90.0f;
    float pitch = 0.0f;
};