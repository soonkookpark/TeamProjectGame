#include "stdafx.h"
#include "RangeAttack.h"
#include "Projectiles/AllProjectiles.hpp"
#include "SceneMgr.h"
#include "AllCreutures.hpp"
#include "InputMgr.h"

RangeAttack::RangeAttack(const std::string& key, Creature* owner)
	:ActiveSkill(key, owner)
{
	SetData(key);
}

void RangeAttack::Update(float dt)
{
	ActiveSkill::Update(dt);
	if (dynamic_cast<Monster*>(owner) == nullptr)
		pos = owner->look;
	else
		pos = dynamic_cast<Monster*>(owner)->GetPlayer()->GetPosition() - owner->GetPosition();
		
}

void RangeAttack::SetData(const std::string& key)
{
	if (key == "Maggot")
	{
		type = Projectile::ProjetileType::ARROW;
		coolDown = 1.f;
		prevDelay = 0.3f;
		physicalDamage = 12.f;
		magicalDamage = 0.f;
		targetType = Skill::TargetType::ENEMY;
		range = 100.f;		
	}
}

void RangeAttack::Effect()
{
	switch (type)
	{
	case Projectile::ProjetileType::ARROW:
			SceneMgr::Instance().GetCurrScene()->AddGo(new Arrow(owner->GetName(),owner,targets,owner->GetPosition(),pos));		
		break;
	case Projectile::ProjetileType::DELAYED:
			SceneMgr::Instance().GetCurrScene()->AddGo(new DelayedProjectile(owner->GetName(),owner,targets,pos));
		break;
	case Projectile::ProjetileType::LURKER:
			SceneMgr::Instance().GetCurrScene()->AddGo(new Lurker(owner->GetName(),owner,targets,owner->GetPosition(),pos));
		break;
	}
}
