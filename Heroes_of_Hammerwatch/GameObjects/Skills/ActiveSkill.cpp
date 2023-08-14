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
	if (repeat == rptCounter)
	{
		if (timer > coolDown)
			isSkillActive = false;
	}
	if (timer > prevDelay)
	{
		Effect();
		rptCounter++;
		timer = 0.f ;
	}	
}


void ActiveSkill::Active()
{
	Skill::Active();
	timer = 0;
	rptCounter = 0;
	isSkillActive = true;
}
