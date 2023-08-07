#include "stdafx.h"
#include "EliteTick.h"
#include "SceneMgr.h"

EliteTick::EliteTick()
	:Monster("EliteTick")
{
}

void EliteTick::Chase(float dt)
{
	Monster::Chase(dt);
	
	Buff();
	timer += dt;
	if (timer > skillFrequency)
	{
		timer = 0;

	}
}

void EliteTick::SpawnTicks()
{
	Monster* mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x + spawnRange.x, position.y + spawnRange.y);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x - spawnRange.x, position.y + spawnRange.y);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x + spawnRange.x, position.y - spawnRange.y);

	mob = (Monster*)SCENE_MGR.GetCurrScene()->AddGo(new Monster("Tick"));
	mob->SetPosition(position.x - spawnRange.x, position.y - spawnRange.y);
}

void EliteTick::Buff()
{
	std::list<GameObject*> mobs;
	SCENE_MGR.GetCurrScene()->FindGos(mobs, "mob");
	for (auto mob : mobs)
	{

		if (Utils::Distance(mob->GetPosition(), position) > buffRange)
		{
			if (!dynamic_cast<Monster*>(mob)->GetIsBuffed())
			{
				dynamic_cast<Monster*>(mob)->GetBuff();
			}
		}
		else
		{
			if (dynamic_cast<Monster*>(mob)->GetIsBuffed())
			{
				dynamic_cast<Monster*>(mob)->LoseBuff();
			}
		}
	}
}
