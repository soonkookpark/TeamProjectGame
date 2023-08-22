#include "stdafx.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "AnimationController.h"
#include "DataTableMgr.h"
#include "MonsterTable.h"
#include "MeleeAttack.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "Tools/Astar.h"
#include "TileMap.h"
#include "SceneGame.h"

Monster::Monster(const std::string& type, const std::string& name, sf::Vector2f pos)
	:Creature("",name)
{
	SetOrigin(Origins::MC);
	SetData(type);
	SetPosition(pos);
	originalPos = pos;
	sortLayer = SortLayer::A_MONSTER;
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
	if (!monsterParameter.isFlying)
	{
		pathFinder = tileMap->GetAstar();
	}
}

void Monster::Update(float dt)
{
	Creature::Update(dt);
	creatureAnimation.Update(dt);

	findAngle = Utils::Angle(player->GetPosition()- GetPosition());

	if (findAngle < 0)
	{
		findAngle += 360;
	}

	MonsterSight(findAngle);
	//std::cout << lookat << std::endl;
	//std::cout << findAngle << std::endl;
	
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
	case Monster::State::KITING:
		Kiting(dt);
		break;
	}
}

void Monster::SetData(const std::string& name)
{	
	this->name = name;
	monsterParameter = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster)->Get(name).MI;
	creatureInfo = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster)->Get(name).CI;
	
	strArr = Utils::LoadAnimationString(name);
	for (const std::string& strArr : strArr) 
	{
		creatureAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip(strArr));
	}
	creatureAnimation.SetTarget(&sprite);
	//std::cout << "allbareuge choollyukdoem" << std::endl;
	//if (name == "Bat")
	//	std::cout << "Bat 积己" << std::endl;
	//else if (name == "Tick")
	//	std::cout << "Tick 积己" << std::endl;

	if (monsterParameter.isFlying)
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
	Move(dt, destination);
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
		AttackAnimationPrint(lookat);
	}
	if (!isAttacking)
	{
		state = State::KITING;
	}
}

void Monster::Chase(float dt)
{
	timer += dt;
	if (Utils::Distance(destination, position) < 0.1f || timer > 1.f)
	{
		FindDestination();
	}
	Move(dt, destination);	
	//std::cout << lookat << std::endl;
	if (!DetectTarget())
	{
		state = State::DEFAULT;
	}
	if (Utils::CircleToRect(position, convertRange, player->sprite.getGlobalBounds()))
	{
		state = State::KITING;
		surround = Utils::RandomOnCircle(monsterParameter.attackRange);
	}
}

void Monster::Kiting(float dt)
{
	timer += dt;
	if (Utils::Distance(destination, position) < 0.1f || timer > 1.f)
	{
		FindDestination();
	}
	Move(dt, destination + surround);
	if (monsterParameter.attackRange < Utils::Distance(position, player->GetPosition()))
	{
		state = State::CHASE;
	}
	if (Utils::CircleToRect(position, monsterParameter.attackRange, player->sprite.getGlobalBounds()))
	{
		timer = 0.f;
		skills["atk"]->Active();
		state = State::ATTACK;
	}
}

void Monster::Default(float dt)
{	
	IdleAnimationPrint(lookat);
	timer += dt;
	if (Utils::RandomRange(static_cast<float>(0), timer) > monsterParameter.moveFrequency)
	{
		timer = 0;
		destination = originalPos + Utils::RandomInCircle(monsterParameter.moveRange);
		//idle
		state = State::WANDER;
		//std::cout << "wander" << std::endl;
	}
	if (DetectTarget())
	{
		timer = 0;
		state = State::CHASE;
	}
}

void Monster::Die(float dt)
{
	//std::cout << "林芭结!" << std::endl;
	//磷绰 局聪皋捞记
	dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene())->DieMonster(this);
}

void Monster::SetDead()
{
	state = State::DIE;
}
bool Monster::CheckStraight()
{ 	
	//auto tmpe = tileMap->GetTileArray();
	float inclination = tan(Utils::Angle(player->GetPosition() - position));
	std::vector<sf::Vector2i> listOfPoint;
	
	if (tileMap->GetTileArray()[j][i] == 0)
		return false;
	else
		std::cout << tileMap->GetTileArray()[j][i] << std::endl;

	return true;	
}

bool Monster::DetectTarget()
{
	if (player == nullptr)
		return false;
	return Utils::Distance(player->GetPosition(), position) < monsterParameter.searchRange;
	//return Utils::CircleToRect(position, monsterParameter.searchRange, player->sprite.getGlobalBounds());
}

void Monster::IdleAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0:
		creatureAnimation.Play("IdleR");
		break;
	case 1:
		creatureAnimation.Play("IdleDR");
		break;
	case 2:
		creatureAnimation.Play("IdleD");
		break;
	case 3:
		creatureAnimation.Play("IdleDL");
		break;
	case 4:
		creatureAnimation.Play("IdleL");
		break;
	case 5:
		creatureAnimation.Play("IdleUL");
		break;
	case 6:
		creatureAnimation.Play("IdleU");
		break;
	case 7:
		creatureAnimation.Play("IdleUR");
		break;
	}
}

void Monster::MoveAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0:
		//if (creatureAnimation.GetCurrentClipId() == "MoveR")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveR");
		break;
	case 1:
		//if (creatureAnimation.GetCurrentClipId() == "MoveDR")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveDR");
		break;
	case 2:
		//if (creatureAnimation.GetCurrentClipId() == "MoveD")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveD");
		break;
	case 3:
		//if (creatureAnimation.GetCurrentClipId() == "MoveDL")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveDL");
		break;
	case 4:
		//if (creatureAnimation.GetCurrentClipId() != "MoveL")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveL");
		break;
	case 5:
		//if (creatureAnimation.GetCurrentClipId() != "MoveUL")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveUL");
		break;
	case 6:
		//if (creatureAnimation.GetCurrentClipId() != "MoveU")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveU");
		break;
	case 7:
		//if (creatureAnimation.GetCurrentClipId() == "MoveUR")
		//if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveUR");
		break;
	}
}

void Monster::AttackAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0:
		if (creatureAnimation.GetCurrentClipId() == "AttackR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackR");
		break;
	case 1:
		if (creatureAnimation.GetCurrentClipId() == "AttackDR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackDR");
		break;
	case 2:
		if (creatureAnimation.GetCurrentClipId() == "AttackD")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackD");
		break;
	case 3:
		if (creatureAnimation.GetCurrentClipId() == "AttackDL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackDL");
		break;
	case 4:
		if (creatureAnimation.GetCurrentClipId() == "AttackL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackL");
		break;
	case 5:
		if (creatureAnimation.GetCurrentClipId() == "AttackUL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackUL");
		break;
	case 6:
		if (creatureAnimation.GetCurrentClipId() == "AttackU")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackU");
		break;
	case 7:
		if (creatureAnimation.GetCurrentClipId() == "AttackUR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("AttackUR");
		break;
	}
}

void Monster::FindDestination()
{
	if (monsterParameter.isFlying)
		destination = player->GetPosition();
	else
	{
		/*
		if (chasePath != nullptr)
			delete(chasePath);
		*/
		if (CheckStraight())
			destination = player->GetPosition();
		else
		{
			std::stack<sf::Vector2i>* temp = pathFinder->FindPath(this, player);
			if (temp != nullptr)
			{
				delete(chasePath);
				chasePath = temp;
			}
			if (chasePath->size() != 0 || Utils::Distance(destination, position) < 0.1f)
			{
				destination = tileMap->GetFloatPosition(chasePath->top());
				chasePath->pop();
			}
			else
				destination = position;
		}
	}
}

void Monster::Move(float dt, sf::Vector2f pos)
{
	dir = Utils::Normalize(destination - position);
	SetPosition(position + (dir * dt * creatureInfo.speed));
	if (position == destination)
		IdleAnimationPrint(lookat);
	else
		MoveAnimationPrint(lookat);
}
