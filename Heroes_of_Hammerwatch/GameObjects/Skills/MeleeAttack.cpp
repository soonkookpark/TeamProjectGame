#include "stdafx.h"
#include "MeleeAttack.h"
#include "Creature.h"

MeleeAttack::MeleeAttack(const std::string& key)
	:ActiveSkill(key)
{
	SetData(key);
}

void MeleeAttack::Reset()
{
}


void MeleeAttack::Effect()
{
	std::cout << "attacked" << std::endl;
	for (auto target : targets)
	{
		if (Utils::CircleToRect(owner->GetPosition(), range, target->sprite.getGlobalBounds(), owner->look, attackAngle))
		{
			target->Damaged(physicalDamage, magicalDamage);
		}
	}
}

void MeleeAttack::SetData(const std::string& key)
{
	//testCode
	range = 30.f;
	targetType = TargetType::ENEMY;
	physicalDamage = 30;
	magicalDamage = 0;

	prevDelay = 0.f;
	attackAngle = 180;
}

bool MeleeAttack::CheckIntersected()
{
	return false;
}
