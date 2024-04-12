#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Constants.h"
#include "physics/BoundingBox.h"
#include <iostream>

class Player {

public:
    ~Player() = default;

    static Player* getInstance();
    void operator=(const Player &) = delete;


    void tick(float deltaTime);

    void stop();

    void rotate(float pitch, float yaw);
    
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 speed;

    BoundingBox boundingBox;

    bool movingForward = false;
    bool movingBackward = false;
    bool movingLeft = false;
    bool movingRight = false;
    
    private:
    Player(glm::vec3 position = glm::vec3(0.0f, 60.0f, 0.0f), glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f));
    static Player* instance;
    
    //float speed = 5.0f;
    float sensitivity = 0.9f;

    float yaw = -90.0f;
    float pitch = 0.0f;

};