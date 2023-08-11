#pragma once
#include "AttackSkill.h"
class MeleeAttack :
    public AttackSkill
{
protected:
    float attackAngle = 0;
    float attackRange = 0;

    sf::Sprite* sprite;
public:
    MeleeAttack(const std::string& key);
    virtual ~MeleeAttack() = default;

    virtual void Reset();
    //virtual void Update(float dt);
    virtual void Draw(sf::RenderWindow& window);

    virtual void Active() override;

    // AttackSkill을(를) 통해 상속됨
    virtual bool CheckIntersected() override;
};
