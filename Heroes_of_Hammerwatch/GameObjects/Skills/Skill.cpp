#include "stdafx.h"
#include "Skill.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Monster.h"

Skill::Skill(const std::string& name, Creature* owner)
	:owner(owner)
{
}

void Skill::Init()
{
}

void Skill::Reset()
{
	if (targetType == TargetType::SELF)
		targets.push_back(owner);
}

void Skill::Update(float dt)
{
	if (targetType != TargetType::SELF)
		SetTarget();
}

void Skill::SetTarget()
{
	targets.clear();	
	for (GameObject* finder : SCENE_MGR.GetCurrScene()->GetGos())
	{
		
		Creature* checker = dynamic_cast<Creature*>(finder);
		if (checker == nullptr)
			continue;
		if (!Utils::CircleToRect(owner->GetPosition(), range, checker->sprite.getGlobalBounds(), owner->look))
			continue;
		if (dynamic_cast<Player*>(owner) != nullptr)
		{
			switch (targetType)
			{
			case Skill::TargetType::ALLY:
				if (dynamic_cast<Player*>(finder) != nullptr)
					targets.push_back(checker);
				break;
			case Skill::TargetType::ENEMY:
				if (dynamic_cast<Monster*>(finder) != nullptr)
					targets.push_back(checker);
				break;
			}
		}

		if (dynamic_cast<Monster*>(owner) != nullptr)
		{
			switch (targetType)
			{
			case Skill::TargetType::ALLY:
				if (dynamic_cast<Monster*>(finder) != nullptr)
					targets.push_back(checker);
				break;
			case Skill::TargetType::ENEMY:
				if (dynamic_cast<Player*>(finder) != nullptr)
					targets.push_back(checker);
				break;
			}
		}
	}
}

void Skill::Active()
{
	SetTarget();
	//Effect();
}
