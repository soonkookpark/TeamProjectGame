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
	for (auto buff : hadBuffs)
	{
		buffs.remove(buff);
		delete(buff);
	}
	hadBuffs.clear();
}

void Creature::GainBuff(Buff* buff)
{
	buffs.push_back(buff);
	buff->GetBuff();
}

void Creature::LoseBuff(Buff* buff)
{
	/*
	for (auto it = buffs.begin(); it != buffs.end(); ) {
		if (*it == buff) {
			it = buffs.erase(it); // 삭제 후 다음 원소로 이동
		}
		else {
			++it;
		}
	}
	*/
	
	hadBuffs.push_back(buff);
}
