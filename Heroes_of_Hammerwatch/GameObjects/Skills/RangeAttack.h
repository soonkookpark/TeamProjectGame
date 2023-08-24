#pragma once
#include "ActiveSkill.h"
#include "Projectiles/Projectile.h"
class RangeAttack :
    public ActiveSkill
{
protected:
    Projectile::ProjetileType type;
    sf::Vector2f pos;
public:
    RangeAttack(const std::string& key, Creature* owner);
    virtual ~RangeAttack() = default;

    virtual void Update(float dt) override;

    virtual void SetData(const std::string& key);

    void Effect() override;
};

