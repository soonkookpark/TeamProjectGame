#pragma once
#include "Skill.h"

class Buff;
class PassiveSkill :
    public Skill
{
protected:
    std::function<Buff* (Creature*)> MakeBuff;
public:
    PassiveSkill(const std::string& key, Creature* owner);
    virtual ~PassiveSkill() = default;

    virtual void SetData(const std::string& key) override;
};