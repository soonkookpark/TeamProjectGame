#include "stdafx.h"
#include "PassiveSkill.h"

PassiveSkill::PassiveSkill(const std::string& key)
	:Skill(key)
{
	SetData(key);
}

void PassiveSkill::SetData(const std::string& key)
{
}
