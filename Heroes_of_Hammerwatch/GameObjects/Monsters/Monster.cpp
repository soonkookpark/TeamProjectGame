#include "stdafx.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "AnimationController.h"
#include "DataTableMgr.h"
#include "MonsterTable.h"

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
}

void Monster::Update(float dt)
{
	Creature::Update(dt);
	if (state == State::DIE)
	{
		Die(dt);
		return;
	}
	if (state != State::CHASE)
	{
		if (DetectTarget())
		{
			state = State::CHASE;
			//std::cout << "chase" << std::endl;
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
	param = DATATABLE_MGR.Get<MonsterTable>(DataTable::Ids::Monster)->Get(name);	

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
}

void Monster::Wander(float dt)
{
	dir = Utils::Normalize(destination - position);	
	SetPosition(position + (dir * dt * param.creatureInfo.speed));
	if (Utils::Distance(position, destination) < 0.1)
	{
		state = State::DEFAULT;
		//std::cout << "default" << std::endl;
	}
}

void Monster::Attack(float dt)
{
	if (param.isMelee)
	{
		//�ٰŸ� ���� player skill�� ���� �ϴ����� ���� ���߿� �߰� ����
	}
	else
	{
		//���Ÿ� ���� player skill�� ���� �ϴ����� ���� ���߿� �߰� ����
	}
}

void Monster::Chase(float dt)
{
	destination = player->GetPosition();	
	dir = Utils::Normalize(destination - position);
	SetPosition(position + (dir * dt * param.creatureInfo.speed));

	if (!DetectTarget())
	{
		state = State::DEFAULT;
	}
	if (Utils::Distance(player->GetPosition(), position) < param.attackRange)
	{
		state = State::ATTACK;
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
}

void Monster::Die(float dt)
{
	std::cout << "�ְŽ�!" << std::endl;
	//�״� �ִϸ��̼�
	SCENE_MGR.GetCurrScene()->RemoveGo(this);
}

void Monster::Damaged(float physicalDmg, float magicalDmg)
{
	std::cout << "damaged" << std::endl;
	physicalDmg = (1 - 1 / (1+ param.creatureInfo.armor/ 50)) * physicalDmg;
	magicalDmg = (1 - 1 / (1+ param.creatureInfo.resistance/ 50)) * magicalDmg;

	//���� ���� ���� ������ ���� ��ٴ� �� ��
	std::cout << physicalDmg + magicalDmg << "������ ����" << std::endl;
	std::cout << curHealth << "�ܿ� ��" << std::endl;
	curHealth -= (physicalDmg + magicalDmg);
	if (curHealth < 0)
	{
		std::cout << "����!" << std::endl;
		state = State::DIE;
	}
}

bool Monster::DetectTarget()
{
	if (player == nullptr)
		return false;
	return Utils::Distance(player->GetPosition(), position) < param.searchRange;
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