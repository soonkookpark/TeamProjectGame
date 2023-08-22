#pragma once
#include "SpriteGo.h"

class Creature;
class Projectile :
    public SpriteGo
{
protected:
    std::list<Creature*> EffectedCreature;
    float speed;
    sf::Vector2f dir;
    
public:
    Projectile(const std::string key);
    virtual ~Projectile() = default;

    virtual void SetData(const std::string key);

    virtual void Update(float dt);

    virtual bool CheckIsCollied(Creature* target) = 0;
    virtual void Effect(Creature* target) = 0;
};

