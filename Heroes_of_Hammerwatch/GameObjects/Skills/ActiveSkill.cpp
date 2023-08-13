#include "stdafx.h"
#include "ActiveSkill.h"
#include "InputMgr.h"

ActiveSkill::ActiveSkill(const std::string& key)
	:Skill(key)
{
	SetData(key);
}

void ActiveSkill::SetData(const std::string& key)
{
}

void ActiveSkill::Update(float dt)
{
	if (!isSkillActive)
		return;
	timer += dt;
	if (timer > prevDelay)
	{
		if(CheckIntersected())
		Effect();
		isSkillActive = false;
	}
}


void ActiveSkill::Active()
{
	Skill::Active();
	isSkillActive = true;
}
