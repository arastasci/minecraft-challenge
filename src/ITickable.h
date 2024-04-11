#pragma once

class ITickable
{
public:
    virtual void tick(float deltaTime) = 0;
};