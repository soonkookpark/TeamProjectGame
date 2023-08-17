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

		//대충 위에 받은 데미지 숫자 뜬다는 뜻 ㅎ
		std::cout << physicalDmg + magicalDmg << "데미지 받음" << std::endl;
		this->owner->curHealth -= (physicalDmg + magicalDmg);
		std::cout << this->owner->curHealth << "잔여 피" << std::endl;
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

		//대충 위에 받은 데미지 숫자 뜬다는 뜻 ㅎ
		std::cout << physicalDmg + magicalDmg << "데미지 받음" << std::endl;
		this->owner->curHealth -= (physicalDmg + magicalDmg);
		std::cout << this->owner->curHealth << "잔여 피" << std::endl;
		if (this->owner->curHealth < 0)
		{
			this->owner->SetDead();
		}
	};
}
