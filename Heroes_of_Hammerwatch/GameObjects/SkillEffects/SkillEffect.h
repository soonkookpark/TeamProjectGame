#pragma once
#include "Skill.h"

class Creature;
class SkillEffect :
    public Skill
{
protected:
    float phisicalDamage;
    float magicalDamage;

    std::vector<Creature*> targets;
public:
    SkillEffect(const std::string& key);
    virtual ~SkillEffect() = default;

    void SetDatas(const std::string& key);

    //virtual void Update(float dt);

    virtual bool CheckIntersected() = 0;
};