#pragma once
#include "Monster.h"
class EliteTick :
    public Monster
{
protected:
    sf::Vector2f spawnRange;
    float skillFrequency = 0;    
    float buffRange = 0;
public:
    EliteTick();
    virtual ~EliteTick() = default;

    void Chase(float dt);

    void SpawnTicks();
    void Buff();
};
