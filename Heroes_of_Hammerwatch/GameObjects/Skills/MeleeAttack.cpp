#include "stdafx.h"
#include "MeleeAttack.h"
#include "Creature.h"

MeleeAttack::MeleeAttack(const std::string& key)
	:AttackSkill(key)
{
}

void MeleeAttack::Reset()
{
}

void MeleeAttack::Draw(sf::RenderWindow& window)
{
	if (sprite != nullptr)
		window.draw(*sprite);
}

void MeleeAttack::Active()
{
	for (auto target : targets)
	{
		if (Utils::CircleToRect(position, attackRange, target->sprite.getGlobalBounds(), target->look, attackAngle))
		{
			target->Damaged(phisicalDamage, magicalDamage);
		}
	}
}

bool MeleeAttack::CheckIntersected()
{
	return false;
}
