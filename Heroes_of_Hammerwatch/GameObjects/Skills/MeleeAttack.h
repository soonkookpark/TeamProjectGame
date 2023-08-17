#pragma once
#include "ActiveSkill.h"
class MeleeAttack :
    public ActiveSkill
{
protected:
    float attackAngle = 0;
public:
    MeleeAttack(const std::string& key, Creature* owner);
    virtual ~MeleeAttack() = default;

    virtual void Reset();
    //virtual void Update(float dt);
    //virtual void Draw(sf::RenderWindow& window);

    virtual void Effect() override;
    virtual void SetData(const std::string& key);

    
};
