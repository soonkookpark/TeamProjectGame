#pragma once
#include "Monster.h"
class BossGolem :
    public Monster
{
protected:
    float spawnRange = 750;
    int summonAmount = 8;
    float attackRange = 40;

    float attackDelay = 0.f;
    float summonDelay = 0.f;

    float AtkTimer = 0.f;
    float SmnTimer = 0.f;
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

