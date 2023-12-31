#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "TileMap.h"
#include "OnTileMap.h"
#include "RectangleGo.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "PlayerTable.h"
#include "DataTableMgr.h"
#include "AllSkills.hpp"
#include "Buffs/AllBuffs.hpp"
#include "Creature.h"
#include "EquipItem.h"
#include "SpriteGo.h"
#include "Inventory.h"

Player::Player(const std::string& textureId, const std::string& n)
	: Creature(textureId, n)
{
	SetOrigin(Origins::MC);
	sprite.setScale(1.0, 1.0);
	//tileSize = tileMap->tiles.size();
	//tileIntSize = tileMap->TileIntSize();
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Transparent);
	box.setOutlineThickness(1);

	for (auto& tile : testTiles)
	{
		tile.setFillColor(sf::Color::Transparent);
	}
	sortLayer = 5;

	creatureAnimation.Play("IdleD");
	SetOrigin(origin);
	SetFlipX(false);
	box.setSize({ 10,14 });
	box.setOrigin(box.getSize() * 0.5f);
}

void Player::Init()
{
	SetOrigin(Origins::MC);
	sprite.setScale(1.0, 1.0);
	//tileSize = tileMap->tiles.size();
	//tileIntSize = tileMap->TileIntSize();
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Transparent);
	box.setOutlineThickness(1);
	inventory = new Inventory();
	for (auto& tile : testTiles)
	{
		tile.setFillColor(sf::Color::Transparent);
	}
	//charInventory.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/ItemSlot.png"));
	//charInventory1 = (new SpriteGo("graphics/Player/ItemSlot.png", "inven"));
	//charInventory1->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/ItemSlot.png"));
}

void Player::SetData(const std::string& name)
{
	pTable = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).PI;	
	creatureInfo = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).CI;	


	buffs.push_back(new Shield("", this));
	skills.insert({ "heal", new ActiveBuff("test",this) });
	skills.insert({ "atk", new MeleeAttack("test",this) });
	skills.insert({ "buff", new PassiveToMe("test",this) });
	skills.insert({ "RA", new RangeAttack("Paladin",this)});
}

void Player::Reset()
{
	creatureAnimation.Play("IdleD");
	SetOrigin(origin);
	SetFlipX(false);
	box.setSize({10,14});
	box.setOrigin(box.getSize() * 0.5f);
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
	SetOrigin(origin);
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

	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	
	PlayerMove(dt);
	
	
	Creature::Update(dt);

	if (InputMgr::Instance().GetMouseButton(sf::Mouse::Right))
	{
		if (clock1.getElapsedTime().asSeconds() > 0.3f)
		{
			std::cout << clock1.getElapsedTime().asSeconds() << std::endl;
			skills["RA"]->Effect();
			clock1.restart();
		}
	}
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C))
	{
		InventoryOnOff();
		
	}
	else if (INPUT_MGR.GetKeyDown(sf::Keyboard::C) && inventoryUI)
	{
		inventoryUI = false;
		std::cout << "인벤토리 꺼짐." << std::endl;
	}

	TestCode();


	if (sortLayer == SortLayer::A_MONSTER)
	{
		TransParent(tileIndex.x, tileIndex.y, box.getGlobalBounds());
	}
	else
	{
		TransParent(tileIndex.x, tileIndex.y, {0, 0, 0, 0});
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	Creature::Draw(window);
	window.draw(box);
	window.draw(charInventory);

	for (const auto& item : inventoryInfo)
	{
		//itemSprite.setPosition(0,0);
		window.draw(item.ItemImage);
	}
	
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
	box.setPosition(position);

	//std::cout << box.getGlobalBounds().left << ", " << box.getGlobalBounds().top << std::endl;


	Collider(tileIndex.x, tileIndex.y);
	box.setPosition(position);
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

void Player::SetTile(TileMap* tile)
{
	this->tileMap = tile;
}

void Player::SetDead()
{
	//exit(3);
}

void Player::HealMP(int value)
{
	curMana += value;
	if (curMana > pTable.manaPoint)
		curMana = pTable.manaPoint;
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

	if (tileMap == nullptr) return;
	std::vector<std::vector<int>> tileArr = tileMap->GetTileArray();

	for (int i = 0; i < 8; i++)
	{
		sf::Vector2i arrSize = tileMap->TileIntSize();
		//이게 맞음 버그 수정한거임
		if (LRTP[i].y < 0 || LRTP[i].x < 0 || LRTP[i].y >= arrSize.y || LRTP[i].x >= arrSize.x)
		{
			continue;
		}

		//testTiles[i].setFillColor({ 255, 255, 255, 128 });
		testTiles[i].setPosition((float)LRTP[i].x * tilePixelSize, (float)LRTP[i].y * tilePixelSize);
		testTiles[i].setSize({ (float)tilePixelSize, (float)tilePixelSize });

		if (tileArr[LRTP[i].y][LRTP[i].x] != 0 && tileArr[LRTP[i].y][LRTP[i].x] != 10)
			continue;

		sf::FloatRect tileRect = { (float)LRTP[i].x * tilePixelSize, (float)LRTP[i].y * tilePixelSize, (float)tilePixelSize, (float)tilePixelSize };
		sf::FloatRect intersector;



		if (tileRect.intersects(box.getGlobalBounds(), intersector))
		{
			float width = box.getGlobalBounds().width * 0.5f;
			float height = box.getGlobalBounds().height * 0.5f;

			if (intersector.width > intersector.height) //위 아래 에서 부딪힘
			{
				if (box.getGlobalBounds().top == intersector.top) //윗 벽에 부딪힘
				{
					SetPosition(position.x, tileRect.top + tileRect.height + height);
				}
				else if (box.getGlobalBounds().top < intersector.top) //아래 벽에 부딪힘
				{
					SetPosition(position.x, tileRect.top - height);
				}
			}
			else if (intersector.width < intersector.height)//좌우에서 부딪힘
			{
				if (box.getGlobalBounds().left == intersector.left) //왼쪽 벽에 부딪힘
				{
					SetPosition(tileRect.left + tileRect.width + width, position.y);
				}
				else if (box.getGlobalBounds().left < intersector.left) //오른쪽 벽에 부딪힘
				{
					SetPosition(tileRect.left - width, position.y);
				}
			}
		}
	}
}

void Player::TestCode()
{
	//GetInventoryInfo();
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



void Player::AcquireItem(int key)
{
	EquipItem* equipment = new EquipItem(key);
	
	if (equipment != nullptr)
	{
		//InventoryItem* tempItem = new InventoryItem();
		EquipItem::ItemInfo equipInfo = equipment->PullEquipInfo();

		//테스트코드 캐릭터의 기존 스텟
		/* {
			std::cout << creatureInfo.maxHealth << std::endl;
			std::cout << pTable.AttackPower << std::endl;
			std::cout << creatureInfo.speed << std::endl;
			std::cout << creatureInfo.armor << std::endl;
			std::cout << creatureInfo.resistance << std::endl;
		}*/

		creatureInfo.maxHealth += equipInfo.hp;
		pTable.AttackPower += equipInfo.attackPower;
		creatureInfo.speed += equipInfo.speed;
		creatureInfo.armor += equipInfo.defense;
		creatureInfo.resistance += equipInfo.resistance;
		
		//item 이미지가 스프라이트일경우
		//tempItem->ItemImage.setTexture(*RESOURCE_MGR.GetTexture(equipInfo.itemName));
		//tempItem->itemName = equipInfo.itemName;
		//tempItem->itemDescription = equipInfo.description;
	
		Inventory::MyItemInfo* sendItemInfo = new Inventory::MyItemInfo;
		sendItemInfo->iconImage.setTexture(*RESOURCE_MGR.GetTexture(equipInfo.itemName));
		sendItemInfo->itemName = equipInfo.itemName;
		sendItemInfo->itemDescription = equipInfo.description;
		Inventory* inventory = (Inventory*)SCENE_MGR.GetCurrScene()->FindGo("inventory");
		inventory->AddItemToInventory(sendItemInfo);
		//inventoryInfo.push_back(*tempItem);

		//테스트코드 캐릭터의 변화된 스텟
		/* {
			std::cout << creatureInfo.maxHealth << std::endl;
			std::cout << pTable.AttackPower << std::endl;
			std::cout << creatureInfo.speed << std::endl;
			std::cout << creatureInfo.armor << std::endl;
			std::cout << creatureInfo.resistance << std::endl;
		} */
		//InventoryItemImageSet();
		/*if(equipment!=nullptr)
			delete equipment;
		if (sendItemInfo != nullptr)
			delete sendItemInfo;*/
		//delete tempItem;
	}
}




	/*EquipItem::ItemInfo equipInfo = equipItem.SetData(key);
	InventoryItem inventoryItem;
	inventoryItem.ItemImage = RESOURCE_MGR.GetTexture(equipInfo.itemName);
	inventoryItem.itemInfo = equipInfo;
	inventoryItem.itemName = equipInfo.itemName;
	inventoryItem.itemDescription = equipInfo.description;

	inventoryInfo.push_back(inventoryItem);*/

	//인벤토리 내용물을 만들었고
	// 내용이 잘 나오는지 파악할 필 요가 있다.
	//이젠 인벤토리 실물을 만들고

	


void Player::InventoryOnOff()
{

	std::cout << "inventory 켜짐" << std::endl;

	Inventory* inventory = (Inventory*)SCENE_MGR.GetCurrScene()->FindGo("inventory");
	inventory->InventoryDisplay();
	//inventory->SetPosition(GetPosition().x, GetPosition().y);
	//inventoryUI = true;


}

void Player::ChangeLayer()
{
	if (sortLayer == SortLayer::PLAYER)
	{
		sortLayer = SortLayer::A_MONSTER;
	}
	else if (sortLayer == SortLayer::A_MONSTER)
	{
		sortLayer = SortLayer::PLAYER;
	}
}
