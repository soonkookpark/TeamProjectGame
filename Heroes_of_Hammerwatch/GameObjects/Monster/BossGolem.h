#pragma once
#include "Monster.h"
class BossGolem :
    public Monster
{
protected:
    float spawnRange = 750;
    int summonAmount = 8;
    float rockRadius;
    float attackRange = 40;
public:
    BossGolem();
    virtual ~BossGolem() = default;

    virtual void Update(float dt);

    void SummonBats();
    void Lurker();
    void RockSpawn();
    void MeleeAttack();   
};

