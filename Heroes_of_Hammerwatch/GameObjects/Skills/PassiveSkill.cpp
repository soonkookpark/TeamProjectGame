#include "stdafx.h"
#include "PassiveSkill.h"

PassiveSkill::PassiveSkill(const std::string& key, Creature* owner)
	:Skill(key, owner)
{
	SetData(key);
}

void PassiveSkill::SetData(const std::string& key)
{
	
}
