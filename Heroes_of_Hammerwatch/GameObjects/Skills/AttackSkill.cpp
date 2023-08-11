#include "stdafx.h"
#include "AttackSkill.h"
#include "InputMgr.h"

AttackSkill::AttackSkill(const std::string& key)
	:Skill(key)
{
	SetData(key);
}

void AttackSkill::SetData(const std::string& key)
{
}

void AttackSkill::Update(float dt)
{

}


void AttackSkill::Active()
{
}
