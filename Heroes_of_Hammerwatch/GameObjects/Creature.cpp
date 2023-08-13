#include "stdafx.h"
#include "Creature.h"
#include "Skill.h"

void Creature::Update(float dt)
{
	for (auto skill : skills)
	{
		skill.second->Update(dt);
	}
}