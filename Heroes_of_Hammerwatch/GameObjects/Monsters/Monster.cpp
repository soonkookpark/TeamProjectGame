#include "stdafx.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "AnimationController.h"
#include "DataTableMgr.h"
#include "MonsterTable.h"
#include "MeleeAttack.h"

Monster::Monster(const std::string& type, const std::string& name)
	:Creature("",name)
{
	origin = Origins::MC;
	SetData(type);

	
}

void Monster::Init()
{
	
}

void Monster::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrScene()->FindGo("player"));
	state = Monster::State::DEFAULT;
	//std::cout << "default" << std::endl;
	timer = 0;
	curHealth = creatureInfo.maxHealth;
}

void Monster::Update(float dt)
{
	Creature::Update(dt);
	look = dir;

	if (state == State::DIE)
	{
		Die(dt);
		return;
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
		Chase(dt);
		break;
	case Monster::State::ATTACK:
		Attack(dt);
		break;
	}
}

void Monster::SetData(const std::string& name)
{	
	this->name = name;
	param = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster)->Get(name).MI;
	creatureInfo = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster)->Get(name).CI;

	if(name == "Bat")
		textureId = "graphics/Test/testBat.png";
	else if (name == "Tick")
		textureId = "graphics/Test/testTick.png";

	if (param.isFlying)
	{
		sortLayer = SortLayer::A_MONSTER;
	}
	else
	{
		sortLayer = SortLayer::G_MONSTER;
	}
	skills.insert({ "atk", new MeleeAttack("test",this) });
}

void Monster::Wander(float dt)
{
	dir = Utils::Normalize(destination - position);	
	SetPosition(position + (dir * dt * creatureInfo.speed));
	if (Utils::Distance(position, destination) < 0.1)
	{
		state = State::DEFAULT;
		//std::cout << "default" << std::endl;
	}
}

void Monster::Attack(float dt)
{
	bool isAttacking = false;
	for (auto skill : skills)
	{
		ActiveSkill* activeSkill = dynamic_cast<ActiveSkill*>(skill.second);
		if (activeSkill == nullptr)
			continue;
		isAttacking = isAttacking || activeSkill->GetIsSkillActive();		
	}
	if(!isAttacking)
		state = State::CHASE;
}

void Monster::Chase(float dt)
{
	destination = player->GetPosition();	
	dir = Utils::Normalize(destination - position);
	SetPosition(position + (dir * dt * creatureInfo.speed));

	if (!DetectTarget())
	{
		state = State::DEFAULT;
	}
	//if (Utils::Distance(player->GetPosition(), position) < param.attackRange)
	if (Utils::CircleToRect(position, param.attackRange, player->sprite.getGlobalBounds()))
	{
		state = State::ATTACK;
		skills["atk"]->Active();
		//std::cout << "atk" << std::endl;
	}
}

void Monster::Default(float dt)
{	
	timer += dt;
	if (Utils::RandomRange(static_cast<float>(0), timer) > param.moveFrequency)
	{
		timer = 0;
		destination = originalPos + Utils::RandomInCircle(param.moveRange);
		state = State::WANDER;
		//std::cout << "wander" << std::endl;
	}
	if (DetectTarget())
	{
		state = State::CHASE;
	}
}

void Monster::Die(float dt)
{
	//std::cout << "주거써!" << std::endl;
	//죽는 애니메이션
	SCENE_MGR.GetCurrScene()->RemoveGo(this);
}

void Monster::SetDead()
{
	state = State::DIE;
}
/*
void Monster::Damaged(float physicalDmg, float magicalDmg, Creature* attacker)
{
	//std::cout << "damaged" << std::endl;
	physicalDmg = 1 / (1+ creatureInfo.armor/ 50) * physicalDmg;
	magicalDmg = 1 / (1+ creatureInfo.resistance/ 50) * magicalDmg;

	//대충 위에 받은 데미지 숫자 뜬다는 뜻 ㅎ
	std::cout << physicalDmg + magicalDmg << "데미지 받음" << std::endl;
	curHealth -= (physicalDmg + magicalDmg);
	std::cout << curHealth << "잔여 피" << std::endl;
	if (curHealth < 0)
	{
		//std::cout << "죽음!" << std::endl;
		state = State::DIE;
	}
}
*/
bool Monster::DetectTarget()
{
	if (player == nullptr)
		return false;
	return Utils::Distance(player->GetPosition(), position) < param.searchRange;
	//return Utils::CircleToRect(position, param.searchRange, player->sprite.getGlobalBounds());
}
/*
void Monster::GetBuff()
{
	param.damage *= 1.5f;
	param.speed *= 1.2f;
	sprite.setColor({255,125,125,255});
	isBuffed = true;
}

void Monster::LoseBuff()
{
	param.damage /= 1.5f;
	param.speed /= 1.2f;
	sprite.setColor({ 255,255,255,255 });
	isBuffed = false;
}

bool Monster::meleeAttack()
{
	Utils::CircleToRect(position, param.attackRange, player->sprite.getGlobalBounds(), attackAngle, static_cast<float>(param.attackArc));
	return false;
}
*/