#include "stdafx.h"
#include "DelayedProjectile.h"
#include "Creature.h"
#include "ResourceMgr.h"

DelayedProjectile::DelayedProjectile(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos)
    :Projectile(key,owner,targets, pos)
{
    SetPosition(pos);
    SetData(key);
}

void DelayedProjectile::SetData(const std::string& key)
{
    fallingObject.setTexture(*ResourceMgr::Instance().GetTexture("graphics/Test/testProjectile.png"));
    Utils::SetOrigin(fallingObject, Origins::BC);
    fallDistance = 20.f;
    delayTime = 2.f;
    animationTime = 1.f;

    if (Utils::Distance(owner->GetPosition(), position) > attackRange)
        SetPosition(owner->GetPosition() + Utils::Normalize(owner->GetPosition() - position) * attackRange);
}

void DelayedProjectile::Update(float dt)
{
    Projectile::Update(dt);
    timer += dt;
    if (timer > delayTime - animationTime)
    {
        fallingObject.setPosition(Utils::Lerp({ position.x , position.y - fallDistance }, position, timer - (delayTime - animationTime)));
    }
    if (timer > delayTime)
    {
        for (auto target : targets)
        {
            if (CheckIsCollided(target))
            {
                auto it = std::find(EffectedCreature.begin(), EffectedCreature.end(), target);
                if (it == EffectedCreature.end())
                {
                    EffectedCreature.push_back(target);
                    Effect(target);
                }
            }
        }
        End();
    }
}

void DelayedProjectile::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
    if (timer > delayTime - animationTime)
    {
        window.draw(fallingObject);
    }
}

bool DelayedProjectile::CheckIsCollided(Creature* target)
{
    return Utils::CircleToRect(position,radius,target->sprite.getGlobalBounds());
}

void DelayedProjectile::End()
{
    //사라지는 애니메이션 ㄱㄱ
    
}
