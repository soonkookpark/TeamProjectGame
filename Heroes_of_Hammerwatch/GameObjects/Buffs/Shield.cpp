#include "stdafx.h"
#include "Shield.h"
#include "AllCreutures.hpp"

Shield::Shield(const std::string& key, Creature* owner)
	:Buff(key,owner, 0)
{
	SetData(key);
}

void Shield::SetData(const std::string& key)
{
	
}

void Shield::GetBuff()
{
	owner->Damaged = [this](float physicalDmg, float magicalDmg, Creature* attacker)
	{
		bool isBlocked = false;
		if (rate > Utils::RandomRange(0.f, 1.f))
		{
			if (angle != 360)
			{
				angle /= 2;				
				float testAngle = Utils::Angle(owner->GetPosition() - attacker->GetPosition());
				if (-angle < testAngle && angle > testAngle)
				{
					isBlocked = true;
				}
			}
		}
			
					std::cout << "blocked" << std::endl;
		physicalDmg = 1 / (1 + this->owner->creatureInfo.armor / 50) * physicalDmg;
		magicalDmg = 1 / (1 + this->owner->creatureInfo.resistance / 50) * magicalDmg;

		magicalDmg -= blockMagicDmg;
		physicalDmg -= blockPhysicDmg;

		if (attacker == nullptr)
			physicalDmg = 0;

		//���� ���� ���� ������ ���� ��ٴ� �� ��
		std::cout << physicalDmg + magicalDmg << "������ ����" << std::endl;
		this->owner->curHealth -= (physicalDmg + magicalDmg);
		std::cout << this->owner->curHealth << "�ܿ� ��" << std::endl;
		if (this->owner->curHealth < 0)
		{
			this->owner->SetDead();
		}
	};
}

void Shield::LoseBuff()
{
	owner->Damaged = [this](float physicalDmg, float magicalDmg, Creature* attacker)
	{
		physicalDmg = 1 / (1 + this->owner->creatureInfo.armor / 50) * physicalDmg;
		magicalDmg = 1 / (1 + this->owner->creatureInfo.resistance / 50) * magicalDmg;

		//���� ���� ���� ������ ���� ��ٴ� �� ��
		std::cout << physicalDmg + magicalDmg << "������ ����" << std::endl;
		this->owner->curHealth -= (physicalDmg + magicalDmg);
		std::cout << this->owner->curHealth << "�ܿ� ��" << std::endl;
		if (this->owner->curHealth < 0)
		{
			this->owner->SetDead();
		}
	};
}
