#include "stdafx.h"
#include "Lurker.h"
#include "Creature.h"
#include "InputMgr.h"
#include "ResourceMgr.h"

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
        followingSprite[counter % followingSprite.size()].setPosition(position);
        //애니메이션 플레이 부분
        counter++;
    }
}

void Lurker::Draw(sf::RenderWindow& window)
{
    for (auto obj : followingSprite)
    {
        window.draw(obj);
    }
}

void Lurker::SetData(const std::string& key)
{
    speed = 100.f;
    animationTime = 1.f;

    sprite.setTexture(*ResourceMgr::Instance().GetTexture("graphics/Test/testProjectile.png"));
    const sf::Texture tex = *(sprite.getTexture());
    
    //사이즈 정하는거 괜찮은거 있는지 사람들에게 물어보기
    int size = static_cast<int>(Utils::Distance(dir * speed, { 0.f,0.f }) / sprite.getLocalBounds().width * animationTime + 1);
    followingSprite.resize(size);
    for (int i = 0; i < followingSprite.size(); i++)
    {
        followingSprite[i].setTexture(tex);
        Utils::SetOrigin(followingSprite[i], origin);
        followingSprite[i].setPosition(position);
    }
}

bool Lurker::CheckIsCollided(Creature* target)
{
    bool rtn = false;
    for (auto obj : followingSprite)
    {
        rtn = rtn || target->sprite.getGlobalBounds().intersects(obj.getGlobalBounds());
    }
    return rtn;
}

void Lurker::End()
{
}
