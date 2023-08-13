#include "stdafx.h"
#include "Skill.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Monster.h"

Skill::Skill(const std::string& name)
{
}

void Skill::Init()
{
}

void Skill::Reset()
{
}

void Skill::Update(float dt)
{
}


void Skill::SetTarget()
{
	targets.clear();
	if (targetType == Skill::TargetType::SELF)
	{
		targets.push_back(owner);
		return;
	}
	for (GameObject* finder : SCENE_MGR.GetCurrScene()->GetGos())
	{
		
		if (Utils::Distance(finder->GetPosition(), owner->GetPosition()) > range)
			continue;
		Creature* checker = dynamic_cast<Creature*>(finder);
		if (checker == nullptr)
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
	Effect();
}
