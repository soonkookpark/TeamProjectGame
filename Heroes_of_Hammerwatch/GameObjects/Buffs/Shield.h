#pragma once
#include "Buff.h"

class Shield :
    public Buff
{
protected:
    float rate = 1;
    float blockMagicDmg = 10;
    float blockPhysicDmg = 10;
    float angle = 0;

public:
    Shield(const std::string& key, Creature* owner);
    virtual ~Shield() = default;

    virtual void Update(float dt) {};

    virtual void SetData(const std::string& key);

    virtual void GetBuff();
    virtual void LoseBuff();
};

