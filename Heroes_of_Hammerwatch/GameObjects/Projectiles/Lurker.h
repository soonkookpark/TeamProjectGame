#pragma once
#include "Projectile.h"
#include "AnimationController.h"

class Lurker :
    public Projectile
{
protected:
    float speed;
    float animationTime;

    sf::Vector2f dir;
    std::vector<AnimationController> controllers;
    std::vector<sf::Sprite> followingSprite;
    float moveCounter = 0.f;
    float movedDistance = 0.f;
    int counter = 0;
    float spriteSize = 0;
public:
    Lurker(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos, sf::Vector2f dir = {999.f, 999.f});
    virtual ~Lurker() = default;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window)override;

    virtual void SetData(const std::string& key) override;

    // Projectile을(를) 통해 상속됨
    bool CheckIsCollided(Creature* target) override;
    void End() override;
};

