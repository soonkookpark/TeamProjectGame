#pragma once
#include "PassiveSkill.h"
class PassiveToMe :
    public PassiveSkill
{
public:
    PassiveToMe(const std::string& key, Creature* owner);
    virtual ~PassiveToMe() = default;
    
    virtual void SetData(const std::string& key) override;

    virtual void Effect() override;
};

