#pragma once
#include "Projectile.h"
class DelayedProjectile :
    public Projectile
{
protected:
    float delayTime =0.f;
    sf::Sprite fallingObject;
    float fallDistance =  0.f;
    float animationTime = 0.f;

public:
    DelayedProjectile(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos);
    virtual ~DelayedProjectile() = default;

    virtual void SetData(const std::string& key);

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow window);

    // Projectile을(를) 통해 상속됨
    virtual bool CheckIsCollided(Creature* target) override;
    virtual void End() override;
};

