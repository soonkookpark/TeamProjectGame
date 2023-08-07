#include "stdafx.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "AnimationController.h"
#include "DataTableMgr.h"
#include "MonsterTable.h"

Monster::Monster(const std::string& name)
	:SpriteGo("",name)
{
	origin = Origins::MC;
}

void Monster::Init()
{
	
}

void Monster::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrScene()->FindGo("player"));
}

void Monster::Update(float dt)
{
	if(!SCENE_MGR.GetCurrScene()->GetWorldView().getViewport().intersects(sprite.getGlobalBounds()))
		return;
	if (state != State::CHASE)
	{
		if (DetectTarget())
		{
			state = State::CHASE;
		}
	}
	switch (state)
	{
	case Monster::State::DEFAULT:
		Default(dt);
		break;
	case Monster::State::WANDER:
		Wander(dt);
		break;
	case Monster::State::CHASE:
		Chase();
		break;
	case Monster::State::ATTACK:
		Attack(dt);
		break;
	}
}

void Monster::SetDatas(const std::string& name)
{	
	MonsterTable* table = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster);
	MonsterTable::MonsterParameters param = table->GetMonsterTable(name);
	this->name = name;
	this->monsterType = param.monsterType;
	this-> exp = param.exp;
	this-> moveRange = param.moveRange;
	this->moveFrequency = param.moveFrequency;
	this->maxHealth = param.maxHealth;
	this->armor = param.armor;
	this->resistance = param.resistance;
	this->attackType = param.attackType;
	this->damage = param.damage;
	this->physicalEvade = param.physicalEvade;
	this->MagicalEvade = param.MagicalEvade;
	this->searchRange = param.searchRange;
	this->speed = param.speed;
	this->isFlying = param.isFlying;
	this->isMelee = param.isMelee;
	this->attackArc = param.attackArc;
	this->attackRange = param.searchRange;
}

void Monster::Wander(float dt)
{
	timer += dt;
	SetPosition(position + (dir * dt * speed));
	if (position == destination)
		state = State::DEFAULT;
}

void Monster::Attack(float dt)
{
	if (isMelee)
	{
		//근거리 공격 player skill과 공유 하는점이 많아 나중에 추가 예정
	}
	else
	{
		//원거리 공격 player skill과 공유 하는점이 많아 나중에 추가 예정
	}
}

void Monster::Chase()
{
	destination = player->GetPosition();
	dir = destination - position;

	if (Utils::Distance(player->GetPosition(), position) < attackRange)
	{
		state = State::ATTACK;
	}
}

void Monster::Default(float dt)
{	
	timer += dt;
	if (Utils::RandomRange(static_cast<float>(0), timer) > moveFrequency)
	{
		timer = 0;
		destination = originalPos + Utils::RandomInCircle(moveRange);
		dir = destination - position;
		state = State::WANDER;
	}
}

bool Monster::DetectTarget()
{
	return Utils::Distance(player->GetPosition(), position) < searchRange;
}
