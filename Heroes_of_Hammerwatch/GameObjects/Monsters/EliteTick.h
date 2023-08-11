#pragma once
#include "Monster.h"
class EliteTick :
    public Monster
{
protected:
    float spawnRange = 30;
    float skillFrequency = 0;    
    float buffRange = 0;
public:
    EliteTick();
    virtual ~EliteTick() = default;

    virtual void Update(float dt);

    virtual void SetData(const std::string& name);
    void Chase(float dt);

    void SummonTicks();
    //void Buff();
};
