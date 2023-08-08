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
	Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Bat"));

}

void BossGolem::Lurker()
{
}

void BossGolem::RockSpawn()
{
}
