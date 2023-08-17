#include "stdafx.h"
#include "BuffToOther.h"
#include "Buffs/AllBuffs.hpp"
#include "Utils.h"
#include "SceneMgr.h"
#include "AllCreutures.hpp"

BuffToOther::BuffToOther(const std::string& key, Creature* owner)
	: PassiveSkill(key, owner)
{
	SetData("test");
}

void BuffToOther::SetData(const std::string& key)
{	
	range = 200;
	targetType = TargetType::ALLY;
	MakeBuff = [this](Creature* target) {return new BloodLust(target, owner, range); };
}

void BuffToOther::Update(float dt)
{
	Skill::Update(dt);
	Effect();
}

void BuffToOther::Effect()
{
	for (auto target : targets)
	{
		if (std::find(buffedTarget.begin(), buffedTarget.end(), target) == buffedTarget.end())
		{
			target->GainBuff(MakeBuff(target));
			buffedTarget.push_back(target);
		}
	}
	for (auto target : buffedTarget)
	{
		if (std::find(targets.begin(), targets.end(), target) == targets.end())
		{
			hadBuffedTarget.push_back(target);
		}
	}
	for (auto obj : hadBuffedTarget)
	{
		buffedTarget.remove(obj);
	}
	hadBuffedTarget.clear();
}
