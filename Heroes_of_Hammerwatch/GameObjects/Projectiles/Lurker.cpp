#include "stdafx.h"
#include "Lurker.h"
#include "Creature.h"
#include "InputMgr.h"

Lurker::Lurker(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos, sf::Vector2f dir)
    :Projectile(key, owner,targets,pos), dir(dir)
{
    if (dir == sf::Vector2f(999.f, 999.f))
        dir = Utils::Normalize(owner->GetPosition() - InputMgr::Instance().GetMousePos());
    SetData(key);
}

void Lurker::Update(float dt)
{
    Projectile::Update(dt);
    sf::Vector2f movement = dir * speed * dt;
    movedDistance += Utils::Distance(movement, {0.f,0.f});
    SetPosition(position + movement);
    if (movedDistance > sprite.getLocalBounds().width)
    {
        movedDistance = 0;
        followingSprite[counter % followingSprite.size()]->setPosition(position);
        counter++;
    }
}

void Lurker::Draw(sf::RenderWindow& window)
{
    for (auto obj : followingSprite)
    {
        window.draw(*obj);
    }
}

void Lurker::SetData(const std::string& key)
{
    Utils::Distance(dir * speed, { 0.f,0.f });// 그 갯수 설정 하는거 함수 만들엉야함 집이라서 딴짓할거 너무 많음
}

bool Lurker::CheckIsCollided(Creature* target)
{
    bool rtn = false;
    for (auto obj : followingSprite)
    {
        rtn = rtn || target->sprite.getGlobalBounds().intersects(obj->getGlobalBounds());
    }
    return rtn;
}

void Lurker::End()
{
}
