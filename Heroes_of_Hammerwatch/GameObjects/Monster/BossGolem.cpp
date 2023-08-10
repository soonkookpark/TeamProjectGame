#include "stdafx.h"
#include "BossGolem.h"
#include "SceneMgr.h"

BossGolem::BossGolem()
	:Monster("BossGolem", "BossGolem")
{
}

void BossGolem::Update(float dt)
{
}

void BossGolem::SummonBats()
{
	for(int i = 0 ; i < summonAmount; i++)
	{		
		Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Bat"));
		mob->SetPosition(Utils::RandomOnCircle(spawnRange)+position);
	}
}

void BossGolem::Lurker()
{

}

void BossGolem::RockSpawn()
{

}

void BossGolem::MeleeAttack()
{
	if (Utils::CircleToRect(position, attackRange, player->sprite.getGlobalBounds()))
	{
		//플레이어 피격 함수
	}
}
