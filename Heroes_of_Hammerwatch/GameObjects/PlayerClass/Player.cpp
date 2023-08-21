#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "TileMap.h"
#include "RectangleGo.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "PlayerTable.h"
#include "DataTableMgr.h"
#include "AllSkills.hpp"
#include "Buffs/AllBuffs.hpp"
#include "Creature.h"

void Player::Init()
{
	SetOrigin(Origins::MC);
	sprite.setScale(1.0, 1.0);
	tileSize = tileMap->tiles.size();
	tileIntSize = tileMap->TileIntSize();
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Transparent);
	box.setOutlineThickness(1);
	sortLayer = SortLayer::PLAYER;
	for (auto& tile : testTiles)
	{
		tile.setFillColor(sf::Color::Transparent);
	}
}

void Player::SetData(const std::string& name)
{
	pTable = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).PI;	
	creatureInfo = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).CI;	


	buffs.push_back(new Shield("", this));
	skills.insert({ "heal", new ActiveBuff("test",this) });
	skills.insert({ "atk", new MeleeAttack("test",this) });
	skills.insert({ "buff", new PassiveToMe("test",this) });
}

void Player::Reset()
{
	creatureAnimation.Play("IdleD");
	SetOrigin(origin);
	SetFlipX(false);
	box.setSize({8,16});
	box.setOrigin(box.getSize() * 0.5f);
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());
}

void Player::Update(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		std::cout << tileIndex.x << " , " << tileIndex.y << std::endl;
		std::cout << position.x << " , " << position.y << std::endl;
	}
	
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	creatureAnimation.Update(dt);
	look = Utils::Normalize(INPUT_MGR.GetMousePos() - SCENE_MGR.GetCurrScene()->WorldPosToScreen(position));
	angle = Utils::Angle(look);

	if (angle < 0)
	{
		angle += 360;
	}

	CharacterSight(angle);

	if (direction != sf::Vector2f{0, 0}&&lookat != pastAngle)
	{
		pastAngle = lookat;
	}

	if (direction == sf::Vector2f{0, 0}&& !attackNow)
	{
		IdleAnimationPrint(lookat);
	}
	else if ((((INPUT_MGR.GetKey(sf::Keyboard::S))
		|| (INPUT_MGR.GetKey(sf::Keyboard::W))
		|| (INPUT_MGR.GetKey(sf::Keyboard::D))
		|| (INPUT_MGR.GetKey(sf::Keyboard::A))) && !attackNow)
		) 
	{
		MoveAnimationPrint(lookat); 
	}
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && !attackNow)
	{
		attackNow = true;
		AttackAnimationPrint(lookat);
	}
	if(attackNow && creatureAnimation.GetCurrFrame() == 3)
	{
		attackNow = false;
	}
	//ekgnsdk dlrjf TJ
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };

	PlayerMove(dt);
	box.setPosition(sprite.getPosition());
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	
	Creature::Update(dt);

	if (InputMgr::Instance().GetMouseButton(sf::Mouse::Left))
	{
		if (clock1.getElapsedTime().asSeconds() > 0.3f)
		{
			std::cout << clock1.getElapsedTime().asSeconds()<<std::endl;
			skills["atk"]->Active();
			clock1.restart();
		}
	}

	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::Q))
	{
		skills["heal"]->Active();
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C)&&!inventoryUI)
	{
		//Inventory();
		inventoryUI = true;
	}






	TestCode();
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(box);

	for (auto& tile : testTiles)
	{
		window.draw(tile);
}
}

bool Player::GetFlipX() const
{
	return filpX;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Player::PlayerMove(float dt)
{
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	
	position += direction * creatureInfo.speed * dt;
	SetPosition(position);

	//std::cout << box.getGlobalBounds().left << ", " << box.getGlobalBounds().top << std::endl;


	Collider(tileIndex.x, tileIndex.y);
	
}

int Player::CharacterSight(float angle)
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

//void Player::IdleAnimationPrint(SightDegree lookat)
//{
//	switch (lookat)
//	{
//	case 0 :
//		animation.Play("IdleR");
//		break;
//	case 1:
//		animation.Play("IdleDR");
//		break;
//	case 2:
//		animation.Play("IdleD");
//		break;
//	case 3:
//		animation.Play("IdleDL");
//		break;
//	case 4 :
//		animation.Play("IdleL");
//		break;
//	case 5 :
//		animation.Play("IdleUL");
//		break;
//	case 6 :
//		animation.Play("IdleU");
//		break;
//	case 7:
//		animation.Play("IdleUR");
//		break;
//	}
//}
//
//void Player::MoveAnimationPrint(SightDegree lookat)
//{
//	switch (lookat)
//	{
//	case 0:
//		if (animation.GetCurrentClipId() == "MoveR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveR");
//		break;
//	case 1:
//		if (animation.GetCurrentClipId() == "MoveDR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveDR");
//		break;
//	case 2:
//		if (animation.GetCurrentClipId() == "MoveD")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveD");
//		break;
//	case 3:
//		if (animation.GetCurrentClipId() == "MoveDL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveDL");
//		break;
//	case 4:
//		if (animation.GetCurrentClipId() == "MoveL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveL");
//		break;
//	case 5:
//		if (animation.GetCurrentClipId() == "MoveUL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveUL");
//		break;
//	case 6:
//		if (animation.GetCurrentClipId() == "MoveU")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveU");
//		break;
//	case 7:
//		if (animation.GetCurrentClipId() == "MoveUR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("MoveUR");
//		break;
//	}
//}
//
//void Player::AttackAnimationPrint(SightDegree lookat)
//{
//
//	switch (lookat)
//	{
//	case 0:
//		if (animation.GetCurrentClipId() == "AttackR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackR");
//		break;
//	case 1:
//		if (animation.GetCurrentClipId() == "AttackDR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackDR");
//		break;
//	case 2:
//		if (animation.GetCurrentClipId() == "AttackD")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackD");
//		break;
//	case 3:
//		if (animation.GetCurrentClipId() == "AttackDL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackDL");
//		break;
//	case 4:
//		if (animation.GetCurrentClipId() == "AttackL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackL");
//		break;
//	case 5:
//		if (animation.GetCurrentClipId() == "AttackUL")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackUL");
//		break;
//	case 6:
//		if (animation.GetCurrentClipId() == "AttackU")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackU");
//		break;
//	case 7:
//		if (animation.GetCurrentClipId() == "AttackUR")
//			if (animation.GetCurrFrame() <= 1) break;
//		animation.Play("AttackUR");
//		break;
//	}
//}

void Player::SetTile(TileMap* tile)
{
	this->tileMap = tile;
}

void Player::SetDead()
{
}

void Player::HealMP(int value)
{
	curMana += value;
	if (curMana > pTable.manaPoint)
		curMana = pTable.manaPoint;
}

void Player::AcquireItem(int key)
{
	switch (key)
	{
	case 1:
		creatureInfo.speed += 5;
		break;
	case 2:
		creatureInfo.speed += 15;
		break;
	case 3:
		creatureInfo.armor += 3;
		break;
	case 4:
		creatureInfo.resistance += 3;
		break;
	case 5:
		creatureInfo.armor += 1;
		creatureInfo.resistance += 1;
		break;
	case 6:
		creatureInfo.maxHealth += 10;
		break;
	case 7:
		creatureInfo.resistance += 15;
		break;
	case 8:
		pTable.AttackPower += 10;
		break;
	case 9:
		pTable.AttackPower += 15;
		break;
	case 10:
		pTable.AttackPower += 13;
		break;
	case 11:
		creatureInfo.maxHealth += 5;
		break;
	case 12:
		creatureInfo.maxHealth += 10;
		break;
	case 13:
		creatureInfo.maxHealth += 20;
		break;

	}
	Inventory(key);
}

void Player::Collider(int x, int y)
{
	/*for (auto& tile : testTiles)
	{
		tile.setFillColor(sf::Color::Transparent);
	}*/
	sf::Vector2i LRTP[8] =
	{
		{x - 1, y} ,
		{ x + 1, y },
		{ x, y - 1 },
		{ x, y + 1},
		{x - 1, y - 1},
		{x + 1, y - 1},
		{x - 1, y + 1},
		{x + 1, y + 1}
	};
	// L, R, T, P, LT, RT, LB, RB

	std::vector<std::vector<int>> tileArr = tileMap->GetTileArray();

	for (int i = 0; i < 8; i++)
	{
		sf::Vector2i arrSize = tileMap->TileIntSize();
		//ÀÌ°Ô ¸ÂÀ½ ¹ö±× ¼öÁ¤ÇÑ°ÅÀÓ
		if (LRTP[i].y < 0 || LRTP[i].x < 0 || LRTP[i].y >= arrSize.y || LRTP[i].x >= arrSize.x)
		{
			continue;
		}

		//testTiles[i].setFillColor({ 255, 255, 255, 128 });
		testTiles[i].setPosition((float)LRTP[i].x * tilePixelSize, (float)LRTP[i].y * tilePixelSize);
		testTiles[i].setSize({ (float)tilePixelSize, (float)tilePixelSize });

		if (tileArr[LRTP[i].y][LRTP[i].x] != 0) 
			continue;

		sf::FloatRect tileRect = { (float)LRTP[i].x * tilePixelSize, (float)LRTP[i].y * tilePixelSize, (float)tilePixelSize, (float)tilePixelSize};
		sf::FloatRect intersector;



		if (tileRect.intersects(box.getGlobalBounds(), intersector))
		{
			float width = box.getGlobalBounds().width * 0.5f;
			float height = box.getGlobalBounds().height * 0.5f;
			
			if (intersector.width > intersector.height) //À§ ¾Æ·¡ ¿¡¼­ ºÎµúÈû
			{
				if (box.getGlobalBounds().top == intersector.top) //À­ º®¿¡ ºÎµúÈû
				{
					SetPosition(position.x, tileRect.top + tileRect.height + height);
				}
				else if (box.getGlobalBounds().top < intersector.top) //¾Æ·¡ º®¿¡ ºÎµúÈû
				{
					SetPosition(position.x, tileRect.top - height);
				}
			}
			else if(intersector.width < intersector.height)//ÁÂ¿ì¿¡¼­ ºÎµúÈû
			{
				if (box.getGlobalBounds().left == intersector.left) //¿ÞÂÊ º®¿¡ ºÎµúÈû
				{
					SetPosition(tileRect.left + tileRect.width + width, position.y);
				}
				else if (box.getGlobalBounds().left < intersector.left) //¿À¸¥ÂÊ º®¿¡ ºÎµúÈû
				{
					SetPosition(tileRect.left - width, position.y);
				}
			}
		}
	}
}

void Player::TestCode()
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Hyphen))
	{
		box.setOutlineColor(sf::Color::Transparent);

		for (int i = 0 ; i<8;i++)
		{
			testTiles[i].setFillColor(sf::Color::Transparent);
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Equal))
	{
		box.setOutlineColor(sf::Color::Red);

		for (int i = 0; i < 8; i++)
		{
			testTiles[i].setFillColor({255, 255, 255, 128});
		}
	}
}

void Player::Inventory(int itemNum)
{
	
}
