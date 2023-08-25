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
    float summonBatsDelay = 0.f;
    float lurkerDelay = 0.f;
    float rockSpawnDelay = 0.f;

    float SBtimer = 0.f;
    float Ltimer = 0.f;
    float RStimer = 0.f;
public:
    BossGolem();
    virtual ~BossGolem() = default;

    virtual void Update(float dt)override;

    virtual void SetData(const std::string& key) override;

    void SummonBats();
    void Lurker(float dt);
    void RockSpawn(float dt);
    void MeleeAttack(float dt);
};

