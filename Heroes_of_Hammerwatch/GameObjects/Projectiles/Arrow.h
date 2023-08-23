#pragma once
#include "Projectile.h"

class TileMap;
class Arrow :
    public Projectile
{
protected:
    TileMap* tileMap;
    int penetrateNum = 1;
    float speed;

    sf::Vector2f dir;

    sf::Vector2f hitPos;
    SightDegree forwardAt;
public:
    Arrow(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos, sf::Vector2f dir = { 999.f,999.f });
    virtual ~Arrow() = default;

    virtual void Update(float dt) override;

    virtual void SetData(const std::string& key) override;

    virtual bool CheckIsCollided(Creature* target) override;
    virtual bool CollidedWithWall();
    virtual void End() override;
    virtual void SetForwardAt();
};

