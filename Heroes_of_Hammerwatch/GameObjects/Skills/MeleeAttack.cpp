#include "stdafx.h"
#include "MeleeAttack.h"
#include "Creature.h"

MeleeAttack::MeleeAttack(const std::string& key, Creature* owner)
	:ActiveSkill(key, owner)
{
	SetData(key);
}

void MeleeAttack::Reset()
{
}


void MeleeAttack::Effect()
{
	//std::cout << "attacked" << std::endl;
	for (auto target : targets)
	{
		if (Utils::CircleToRect(owner->GetPosition(), range, target->sprite.getGlobalBounds(), owner->look, attackAngle))
		{
			target->Damaged(physicalDamage, magicalDamage,owner);
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
	repeat = 1;

	coolDown = 2.f;
	prevDelay = 0.5f;

	attackAngle = 180;
}