#include "stdafx.h"
#include "AttackSkill.h"
#include "InputMgr.h"

AttackSkill::AttackSkill(const std::string& key, sf::Keyboard::Key pressed)
	:Skill(key),pressed(pressed)
{
	SetData(key);
}

void AttackSkill::SetData(const std::string& key)
{
}

void AttackSkill::Update(float dt)
{
	if (INPUT_MGR.GetKeyDown(pressed))
	{
		Active();
	}
}


void AttackSkill::Active()
{
}
