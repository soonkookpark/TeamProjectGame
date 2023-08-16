#include "stdafx.h"
#include "Creature.h"
#include "Skill.h"
#include "Buffs/Buff.h"

Creature::Creature(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
	SetData();
}

void Creature::Update(float dt)
{
	for (auto buff : buffs)
	{
		buff->Update(dt);
	}
	for (auto skill : skills)
	{
		skill.second->Update(dt);
	}
	for (auto buff : hadBuffs)
	{
		buffs.remove(buff);
		delete(buff);
	}
	hadBuffs.clear();
}

void Creature::SetData()
{
	Damaged = [this](float physicalDmg, float magicalDmg, Creature* attacker)
	{
		physicalDmg = 1 / (1 + creatureInfo.armor / 50) * physicalDmg;
		magicalDmg = 1 / (1 + creatureInfo.resistance / 50) * magicalDmg;

		//대충 위에 받은 데미지 숫자 뜬다는 뜻 ㅎ
		std::cout << physicalDmg + magicalDmg << "데미지 받음" << std::endl;
		curHealth -= (physicalDmg + magicalDmg);
		std::cout << curHealth << "잔여 피" << std::endl;
		if (curHealth < 0)
		{
			SetDead();
		}
	};

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
