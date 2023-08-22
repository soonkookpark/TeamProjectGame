#include "stdafx.h"
#include "Projectile.h"
#include "Creature.h"

Projectile::Projectile(const std::string key)
	:SpriteGo("","projectile")
{
	SetData(key);
}

void Projectile::SetData(const std::string key)
{

}

void Projectile::Update(float dt)
{
	Creature* target = nullptr;
	if (CheckIsCollied(target))
	{
		DamagedCreature.push_back(target);
		Effect(target);
	}
	SetPosition(position + (dir * speed * dt));
}

