#pragma once
#include "Skill.h"

class Creature;
class ActiveSkill :
    public Skill
{
protected:
    float physicalDamage;
    float magicalDamage;

    float timer = 0;
    float prevDelay = 0;

    bool isSkillActive = false;
public:
    ActiveSkill(const std::string& key);
    virtual ~ActiveSkill() = default;

    virtual void SetData(const std::string& key);
    virtual void Update(float dt);

    virtual bool CheckIntersected() = 0;

    virtual void Active() override;
    virtual void Effect() = 0;

};