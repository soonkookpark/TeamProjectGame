#pragma once
#include "PassiveSkill.h"

class Buff;
class BuffToOther :
    public PassiveSkill
{
protected:
    Buff* GiveThis;
    std::list<Creature*> buffedTarget;
public:
    BuffToOther(const std::string& key) : PassiveSkill(key) {};
    virtual ~BuffToOther() override = default;        

    void SetData(const std::string& key);

    void Update(float dt);

    void GiveBuff();
};

