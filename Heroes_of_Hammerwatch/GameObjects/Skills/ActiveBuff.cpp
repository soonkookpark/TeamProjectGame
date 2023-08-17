#include "stdafx.h"
#include "ActiveBuff.h"
#include "Creature.h"
#include "Buffs/AllBuffs.hpp"

ActiveBuff::ActiveBuff(const std::string& key, Creature* owner)
	:ActiveSkill(key,owner)
{
	SetData(key);
}

void ActiveBuff::SetData(const std::string& key)
{
	targetType = TargetType::ALLY;
	MakeBuff = [](Creature* target) {return new LayOnHands(target, 10); };
}

void ActiveBuff::Effect()
{
	for (auto target : targets)
	{
		target->GainBuff(MakeBuff(target));
	}
}
