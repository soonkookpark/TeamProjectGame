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
    for (int i = 1; i < numOfFollower; i++)
    {

    }
}

void Lurker::Draw(sf::RenderWindow window)
{
    SpriteGo::Draw(window);
    for (auto obj : followingSprite)
    {
        window.draw(*obj);
    }
}

void Lurker::SetData(const std::string& key)
{

}

bool Lurker::CheckIsCollided(Creature* target)
{
    return false;
}

void Lurker::End()
{
}
