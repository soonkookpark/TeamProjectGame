#pragma once
#include "Skill.h"

class Creature;
class AttackSkill :
    public Skill
{
protected:
    float phisicalDamage;
    float magicalDamage;

    std::vector<Creature*> targets;
public:
    AttackSkill(const std::string& key);
    virtual ~AttackSkill() = default;

    virtual void SetData(const std::string& key);
    virtual void Update(float dt);

    virtual bool CheckIntersected() = 0;

    virtual void Active() override;
};