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
		bool hasThis = false;
		for (auto checker : buffedTarget)
		{
			if (target == checker)
			{
				hasThis = true;
			}
		}
		if (!hasThis)
		{
			target->GainBuff(MakeBuff(target));
			buffedTarget.push_back(target);
		}
	}
	for (auto target : buffedTarget)
	{
		bool hasThis = false;
		for (auto checker : targets)
		{
			if (target == checker)
			{
				hasThis = true;
			}
		}
		if (!hasThis)
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
