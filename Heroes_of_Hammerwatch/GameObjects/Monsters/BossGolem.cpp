#include "stdafx.h"
#include "BossGolem.h"
#include "SceneMgr.h"
#include "AllSkills.hpp"
#include "Projectiles/AllProjectiles.hpp"
#include "ResourceMgr.h"
#include "InputMgr.h"

BossGolem::BossGolem()
	:Monster("BossGolem")
{
	SetData("BossGolem");
}

void BossGolem::Update(float dt)
{
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::R))
	{
		skills["lurker"]->Effect();
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::T))
	{
		skills["rockSpawn"]->Effect();
	}
	Monster::Update(dt);
}

void BossGolem::SetData(const std::string& key)
{
	Monster::SetData(key);
	skills.insert({ "rockSpawn",new RangeAttack(key + "_RS",this)});
	skills.insert({ "lurker",new RangeAttack(key + "_L",this) });	
	creatureAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/BossGolem/Special.csv"));
	spawnRange = 500;
}

void BossGolem::SummonBats()
{
	for(int i = 0 ; i < summonAmount; i++)
	{		
		Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Bat"));
		mob->SetPosition(Utils::RandomOnCircle(spawnRange)+position);
	}
	SmnTimer = 0;
}

void BossGolem::Lurker(float dt)
{	
	if (!dynamic_cast<ActiveSkill*>(skills["lurker"])->GetIsSkillActive())
	{		
		AttackAnimationPrint(lookat);
		skills["lurker"]->Active();
	}		
	if (creatureAnimation.GetTotalPlayTime("AttackR")  + attackDelay > AtkTimer)
	{
		AtkTimer = 0;
	}
}

void BossGolem::RockSpawn(float dt)
{
	if (!dynamic_cast<ActiveSkill*>(skills["rockSpawn"])->GetIsSkillActive())
	{
		creatureAnimation.Play("special");
		skills["rockSpawn"]->Active();
	}
	if (creatureAnimation.GetTotalPlayTime("special") + attackDelay > AtkTimer)
	{
		AtkTimer = 0;
	}
}

void BossGolem::MeleeAttack(float dt)
{
	if (Utils::CircleToRect(position, attackRange, player->sprite.getGlobalBounds()))
	{
		skills["atk"]->Active();
		AttackAnimationPrint(lookat);
	}
	if (creatureAnimation.GetTotalPlayTime("AttackR") + attackDelay > AtkTimer)
	{
		AtkTimer = 0;
	}
}
