#include "stdafx.h"
#include "Creature.h"
#include "Skill.h"
#include "Buffs/Buff.h"
#include "TileMap.h"
#include "OnTileMap.h"

Creature::Creature(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
	SetData();
}

void Creature::Update(float dt)
{
	tileIndex = { static_cast<int>(position.x / 16), static_cast<int>(position.y / 16) };
	for (auto buff : buffs)
	{
		buff->Update(dt);
	}
	for (auto skill : skills)
	{
		skill.second->Update(dt);
	}
	for (auto buff : hadBuffs)
	{
		buffs.remove(buff);
		delete(buff);
	}
	hadBuffs.clear();
}

void Creature::SetData()
{
	Damaged = [this](float physicalDmg, float magicalDmg, Creature* attacker)
	{
		physicalDmg = 1 / (1 + creatureInfo.armor / 50) * physicalDmg;
		magicalDmg = 1 / (1 + creatureInfo.resistance / 50) * magicalDmg;

		//대충 위에 받은 데미지 숫자 뜬다는 뜻 ㅎ
		std::cout << physicalDmg + magicalDmg << "데미지 받음" << std::endl;
		curHealth -= (physicalDmg + magicalDmg);
		std::cout << curHealth << "잔여 피" << std::endl;
		if (curHealth < 0)
		{
			SetDead();
		}
	};

}

void Creature::GainBuff(Buff* buff)
{
	buffs.push_back(buff);
	buff->GetBuff();
}

void Creature::LoseBuff(Buff* buff)
{
	/*
	for (auto it = buffs.begin(); it != buffs.end(); ) {
		if (*it == buff) {
			it = buffs.erase(it); // 삭제 후 다음 원소로 이동
		}
		else {
			++it;
		}
	}
	*/
	
	hadBuffs.push_back(buff);
}

void Creature::IdleAnimationPrint(SightDegree lookat)
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

void Creature::MoveAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0:
		if (creatureAnimation.GetCurrentClipId() == "MoveR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveR");
		break;
	case 1:
		if (creatureAnimation.GetCurrentClipId() == "MoveDR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveDR");
		break;
	case 2:
		if (creatureAnimation.GetCurrentClipId() == "MoveD")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveD");
		break;
	case 3:
		if (creatureAnimation.GetCurrentClipId() == "MoveDL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveDL");
		break;
	case 4:
		if (creatureAnimation.GetCurrentClipId() == "MoveL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveL");
		break;
	case 5:
		if (creatureAnimation.GetCurrentClipId() == "MoveUL")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveUL");
		break;
	case 6:
		if (creatureAnimation.GetCurrentClipId() == "MoveU")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveU");
		break;
	case 7:
		if (creatureAnimation.GetCurrentClipId() == "MoveUR")
			if (creatureAnimation.GetCurrFrame() <= 1) break;
		creatureAnimation.Play("MoveUR");
		break;
	}
}

void Creature::AttackAnimationPrint(SightDegree lookat)
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

int Creature::MonsterSight(float angle)
{
	if (angle > 22.5 && angle <= 67.5)
	{
		lookat = DR;
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		lookat = D;
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		lookat = DL;
	}
	else if (angle > 157.5 && angle <= 202.5)
	{
		lookat = L;
	}
	else if (angle > 202.5 && angle <= 247.5)
	{
		lookat = UL;
	}
	else if (angle > 247.5 && angle <= 292.5)
	{
		lookat = U;
	}
	else if (angle > 292.5 && angle <= 337.5)
	{
		lookat = UR;
	}
	else
	{
		lookat = R;
	}
	return lookat;
}

void Creature::HealHP(int value)
{
	std::cout << value << "만큼 힐됨" << std::endl;
	curHealth += value;
	if (curHealth > creatureInfo.maxHealth)
		curHealth = creatureInfo.maxHealth;
}

void Creature::TransParent(int x, int y)
{
	sf::Vector2i LRTP[9] =
	{
		{x - 1, y + 1},
		{x, y + 1},
		{x + 1, y + 1}, //y+1
		{x - 1, y + 2},
		{x, y + 2},
		{x + 1, y + 2},	//y+2
		{x - 1, y + 3},
		{x, y + 3},
		{x + 1, y + 3},	//y+3
	};

	if (onTileMap == nullptr) return;
	std::vector<std::vector<int>> tileArr = onTileMap->GetTileArray();

	for (int i = 0; i < 5; i++)
	{
		sf::Vector2i arrSize = onTileMap->TileIntSize();

		if (LRTP[i].y < 0 || LRTP[i].x < 0 || LRTP[i].y >= arrSize.y || LRTP[i].x >= arrSize.x)
		{
			continue;
		}

		//벽이 None이면 Continue로 수정
		//
		if (tileArr[LRTP[i].y][LRTP[i].x] != Wall::None || tileArr[LRTP[i].y][LRTP[i].x] != 25)
			continue;
		//###########################

		float tilePixelSize = 1;

		//타일 인덱스 확인 후 타일 rect 세팅
		sf::FloatRect tileRect = { (float)LRTP[i].x * tilePixelSize, (float)LRTP[i].y * tilePixelSize, (float)tilePixelSize, (float)tilePixelSize };

		sf::FloatRect wallRect = {};
		//##############################


		sf::FloatRect intersector;



		if (tileRect.intersects(sprite.getGlobalBounds(), intersector))
		{
			//겹치면 투명하게
		}
	}
	
}


