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

		//���� ���� ���� ������ ���� ��ٴ� �� ��
		std::cout << physicalDmg + magicalDmg << "������ ����" << std::endl;
		curHealth -= (physicalDmg + magicalDmg);
		std::cout << curHealth << "�ܿ� ��" << std::endl;
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
			it = buffs.erase(it); // ���� �� ���� ���ҷ� �̵�
		}
		else {
			++it;
		}
	}
	*/
	
	hadBuffs.push_back(buff);
}
