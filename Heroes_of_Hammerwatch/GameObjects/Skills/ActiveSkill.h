#pragma once
#include "Skill.h"

class Creature;
class ActiveSkill :
    public Skill
{
protected:
    float physicalDamage;
    float magicalDamage;

    float prevDelay = 0.f;
    float coolDown = 0.f;

    int repeat = 1;
    int rptCounter = 0;

    float timer = 0.f; 
    bool isSkillActive = false;
public:
    ActiveSkill(const std::string& key, Creature* owner);
    virtual ~ActiveSkill() = default;

    bool GetIsSkillActive() { return isSkillActive; }

    virtual void SetData(const std::string& key);
    virtual void Update(float dt);

    virtual void Active() override;
    virtual void Effect() = 0;

};