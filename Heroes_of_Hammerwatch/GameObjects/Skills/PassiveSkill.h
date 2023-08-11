#pragma once
#include "Skill.h"
class PassiveSkill :
    public Skill
{
protected:
public:
    PassiveSkill(const std::string& key);
    virtual ~PassiveSkill() = default;

    void SetData(const std::string& key);
};