#pragma once
#include "SpriteGo.h"

class Creature;
class Projectile :
    public SpriteGo
{
public:
    enum class ProjetileType
    {
        ARROW,
        DELAYED,
        LURKER,
    };
protected:
    std::list<Creature*> targets;
    float physicalDamage = 0.f;
    float magicalDamage = 0.f;
    Creature* owner;
    float radius;

    std::list<Creature*> EffectedCreature;
    float timer = 0.f;
public:
    Projectile(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos);
    virtual ~Projectile() = default;

    virtual void SetData(const std::string& key);

    virtual void Update(float dt);
    virtual bool CheckIsCollided(Creature* target) = 0;
    virtual void Effect(Creature* target);
    virtual void End() = 0;
};

