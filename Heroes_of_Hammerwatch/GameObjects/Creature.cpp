#include "stdafx.h"
#include "Creature.h"
#include "Skill.h"
#include "Buffs/Buff.h"

void Creature::Update(float dt)
{
	for (auto skill : skills)
	{
		skill.second->Update(dt);
	}
	for (auto buff : buffs)
	{
		buff->Update(dt);
	}
}

void Creature::GainBuff(Buff* buff)
{
	buffs.push_back(buff);
}

void Creature::LoseBuff(Buff* buff)
{
	buffs.remove(buff);
}
