#include "stdafx.h"
#include "Lurker.h"
#include "Creature.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "Monster.h"

Lurker::Lurker(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos, sf::Vector2f dir)
    :Projectile(key, owner,targets,pos), dir(dir)
{
    if (dir == sf::Vector2f(999.f, 999.f))
        dir = Utils::Normalize(owner->GetPosition() - InputMgr::Instance().GetMousePos());
    dir = Utils::Normalize(dir);
    SetData(key);
}

void Lurker::Update(float dt)
{
    Projectile::Update(dt);
    for (auto& ctrl : controllers)
        ctrl.Update(dt);
    sf::Vector2f movement = dir * speed * dt;
    moveCounter += Utils::Distance(movement, {0.f,0.f});
    movedDistance += Utils::Distance(movement, {0.f,0.f});
    SetPosition(position + movement);
    if (moveCounter > spriteSize)
    {
        moveCounter = 0;
        followingSprite[counter % followingSprite.size()].setPosition(position);
        controllers[counter % followingSprite.size()].Play("Lurker");
        counter++;
    }
    if (attackRange < movedDistance)
        End();
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
    //if (key == "BossGolem")
    //{
    animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/BossGolem/LurckerProjectile.csv"));
    spriteSize = 14.f;
    speed = 200.f;
    animationTime = animation.GetTotalPlayTime("Lurker");
    physicalDamage = 25;
    magicalDamage = 0;
    attackRange = 500.f;
    if (key == "player")
    {
        std::list<Monster*>temp = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene())->GetAllMonster();
        for (auto obj : temp)
        {
            targets.push_back(dynamic_cast<Creature*>(obj));
    
        }
    }
    
    int size = static_cast<int>(Utils::Distance(dir * speed) / spriteSize * animationTime);
    followingSprite.resize(size);
    controllers.resize(size);
    for (int i = 0; i < followingSprite.size(); i++)
    {
        controllers[i].AddClip(*RESOURCE_MGR.GetAnimationClip("animations/BossGolem/LurckerProjectile.csv"));
        controllers[i].SetTarget(&followingSprite[i]);
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
    SceneMgr::Instance().GetCurrScene()->RemoveGo(this);
}
