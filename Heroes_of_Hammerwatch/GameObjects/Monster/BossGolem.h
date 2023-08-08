#pragma once
#include "Monster.h"
class BossGolem :
    public Monster
{
protected:
    float spawnRange;
    int summonAmount;
    float rockRadius;
public:
    BossGolem();
    virtual ~BossGolem() = default;

    virtual void Update(float dt);

    void SummonBats();
    void Lurker();
    void RockSpawn();

    
};

