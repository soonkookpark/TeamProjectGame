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


void Skill::SetData(const std::string& key)
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
}

void Skill::Active()
{
}

void Skill::Effect()
{
}
