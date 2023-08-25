#include "stdafx.h"
#include "Projectile.h"
#include "Creature.h"
#include "SceneMgr.h"

Projectile::Projectile(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos)
	:SpriteGo("","projectile"), owner(owner), targets(targets)
{
	SetPosition(pos);
	SetData(key);
}

void Projectile::SetData(const std::string& key)
{

}


void Projectile::Update(float dt)
{
	for (auto& target : targets)
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
}

void Projectile::Effect(Creature* target)
{
	target->Damaged(physicalDamage, magicalDamage, this);
}
