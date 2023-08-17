#include "stdafx.h"
#include "ActiveSkill.h"
#include "InputMgr.h"

ActiveSkill::ActiveSkill(const std::string& key, Creature* owner)
	:Skill(key,owner)
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
		{
			isSkillActive = false;
			rptCounter = 0;
		}
	}
	else if (timer > prevDelay)
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
