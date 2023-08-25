#include "stdafx.h"
#include "BossGolem.h"
#include "SceneMgr.h"
#include "AllSkills.hpp"
#include "Projectiles/AllProjectiles.hpp"

BossGolem::BossGolem()
	:Monster("BossGolem", "BossGolem")
{
	SetData("BossGolem");
	textureId = "graphics/Test/testBoss.png";
}

void BossGolem::Update(float dt)
{
	Ltimer += dt;
	RStimer += dt;
	SBtimer += dt;
	if(Ltimer > lurkerDelay)

	if(Ltimer > lurkerDelay)
	if(Ltimer > lurkerDelay)
	Monster::Update(dt);
}

void BossGolem::SetData(const std::string& key)
{
	Monster::SetData(key);
	skills.insert({ "rockSpawn",new RangeAttack(key + "_RS",this)});
	skills.insert({ "lurker",new RangeAttack(key + "_L",this) });
}

void BossGolem::SummonBats()
{
	for(int i = 0 ; i < summonAmount; i++)
	{		
		Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Bat"));
		mob->SetPosition(Utils::RandomOnCircle(spawnRange)+position);
	}
}

void BossGolem::Lurker(float dt)
{	
	if (!dynamic_cast<ActiveSkill*>(skills["lurker"])->GetIsSkillActive())
	{
		skills["lurker"]->Active();
	}
	else
	{
		//animation gogo
		if (1)//애니메이션 끝나면
		{

		}
	}
}

void BossGolem::RockSpawn(float dt)
{
	if (!dynamic_cast<ActiveSkill*>(skills["rockSpawn"])->GetIsSkillActive())
	{
		skills["rockSpawn"]->Active();
	}
	else
	{
		//animation gogo
		if (1)//애니메이션 끝나면
		{
			
		}
	}
}

void BossGolem::MeleeAttack(float dt)
{
	if (Utils::CircleToRect(position, attackRange, player->sprite.getGlobalBounds()))
	{
		skills["atk"]->Active();
	}
}
