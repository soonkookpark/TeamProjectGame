#include "stdafx.h"
#include "PassiveToMe.h"
#include "Buffs/AllBuffs.hpp"
#include "Creature.h"

PassiveToMe::PassiveToMe(const std::string& key, Creature* owner)
	:PassiveSkill(key,owner)
{
	SetData(key);
	Effect();
}

void PassiveToMe::SetData(const std::string& key)
{
	MakeBuff = [this, key](Creature* owner) {return new Shield(key, owner); };
}

void PassiveToMe::Effect()
{
	owner->GainBuff(MakeBuff(owner));
}
