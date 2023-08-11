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
    sf::Keyboard::Key pressed;
public:
    AttackSkill(const std::string& key, sf::Keyboard::Key pressed);
    virtual ~AttackSkill() = default;

    virtual void SetData(const std::string& key);
    virtual void Update(float dt);

    virtual bool CheckIntersected() = 0;

    virtual void Active() override;
};