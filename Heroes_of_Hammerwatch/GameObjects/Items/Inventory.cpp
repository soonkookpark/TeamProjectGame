#include "stdafx.h"
#include "Inventory.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "TextGo.h"

Inventory::Inventory(const std::string& n)
	:GameObject(n), inventoryMenu("graphics/Inventory/Inventory.png","InventoryMenuImage")
{
	AddInventory(&inventoryMenu);
	inventoryMenu.SetActive(false);
	//inventoryMenu.sprite.setScale(0.5f, 0.5f);
	//sortOrder = UI;
	
	sortLayer = UI;

}

Inventory::~Inventory()
{
	Release();
}

bool Inventory::ExistInventory(GameObject* go)
{
	return std::find(inventoryImageUI.begin(), inventoryImageUI.end(), go) != inventoryImageUI.end();
}

GameObject* Inventory::AddInventory(GameObject* go)
{
	if (!ExistInventory(go))
	{
		inventoryImageUI.push_back(go);
	}
	return go;
}

void Inventory::SetPlayer(Player* player1)
{
	this->player = player1;
}

void Inventory::InventoryDisplay()
{
	//inventoryMenu.SetPosition(player->GetPosition().x, player->GetPosition().y);
	inventoryMenu.SetActive(!inventoryMenu.GetActive());
	if (inventoryMenu.GetActive())
	{
		
		sf::Vector2f displayPosition(274, -194); // 
		//inventoryBox.
		inventoryBox.setOutlineThickness(0.f);
		inventoryBox.setOutlineColor(sf::Color::Red);
		inventoryBox.setPosition(displayPosition);
		inventoryBox.setFillColor(sf::Color::Transparent);
		//inventoryBox.setOrigin(displayPosition);
		inventoryBox.setSize({ 36.f, 36.f });
		float iconSize = 36.0f; // ������ �̹��� ũ��

		int itemsPerRow = 4; // �� �࿡ ǥ�õ� ������ ��
		int rowCount = 11;   // ��ü �� ��
		
		std::cout << equipItemImageInMyInventory.size() << std::endl;
		
		//1. ������ ���� �κ�
		{
			for (int row = 0; row < rowCount; ++row)
			{
				for (int col = 0; col < itemsPerRow; ++col)
				{
					int index = row * itemsPerRow + col;

					// ���� �迭�� �ε����� ��ȿ���� Ȯ��
					if (index < equipItemImageInMyInventory.size())
					{
						Inventory::MyItemInfo* item = equipItemImageInMyInventory[index];
						//std::cout << equipItemImageInMyInventory.size() << std::endl;
						//item->iconImage.
						// ������ ������ �̹����� Ư�� ��ġ�� �׸�
						item->iconImage.setScale(3.f, 3.f);
						//����ũ��
						//float iconXSize = item->iconImage.getGlobalBounds().width*0.5;
						//����ũ��
						//float iconYSize = item->iconImage.getGlobalBounds().height*0.5f;
						//std::cout << iconXSize << "," << iconYSize << std::endl;
						//item->iconImage.setOrigin(iconXSize, iconYSize);
						std::cout << "�̰��� ������" << std::endl;
						//std::cout << item->iconImage.getOrigin().x << ", " << item->iconImage.getOrigin().y << std::endl;
						item->iconImage.setPosition(displayPosition.x + col * (iconSize + 12.0f), displayPosition.y + row * (iconSize + 12.0f));
						std::cout << item->iconImage.getPosition().x << ", " << item->iconImage.getPosition().y << std::endl;
						//std::cout << item->itemDescription << std::endl;
						//item->iconImage.setScale(iconSize / item->iconImage.getLocalBounds().width, iconSize / item->iconImage.getLocalBounds().height);


					}
				}
			}
		}

		//2. �ɷ�ġ ���
		{
			Collocate(player);
			
		}
	}
	else 
	{
		inventoryBox.setOutlineColor({ 0,0,0,0 });
		TextGo* inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("JobName");
		inventoryText1->SetActive(false);
		//std::cout << inventoryText->GetActive() << std::endl;
		//player->SetActive(true);
	}
}

void Inventory::AddItem()
{

}

void Inventory::Init()
{
	for (auto i : inventoryImageUI)
	{
		i->Init();
	}
}

void Inventory::Reset()
{
	inventoryMenu.Reset();
	inventoryMenu.SetOrigin(Origins::MC);
	//Player* player = (Player*)SCENE_MGR.GetCurrScene()->FindGo("")
	
}

void Inventory::Release()
{
	inventoryImageUI.clear();
}

void Inventory::Update(float dt)
{
}

void Inventory::Draw(sf::RenderWindow& window)
{
	
	for (auto m : inventoryImageUI)
	{
		if (m->GetActive())
		{
			m->Draw(window);
		}
	}
	window.draw(inventoryBox);
//	if(isActive)
	if(inventoryMenu.GetActive())
	for (auto icon : equipItemImageInMyInventory)
	{
		window.draw(icon->iconImage);

	}
}
void Inventory::AddItemToInventory(MyItemInfo* itemInfo)
{
	equipItemImageInMyInventory.push_back(itemInfo);
	//std::cout << equipItemImageInMyInventory.size() << std::endl;
}



const std::vector<Inventory::MyItemInfo*> Inventory::GetInventoryItems() const 
{
	return equipItemImageInMyInventory;
}

void Inventory::Collocate(Player* player)
{
	Player::CreatureInfo* creatureInfo = player->ControlCreatureInfos();
	Player::PlayerInfo* playerInfo = player->ControlPlayerInfos();
	//std::TestCode
	{
		std::cout << "maxHealth: " << creatureInfo->maxHealth << std::endl;
		std::cout << "armor:" << creatureInfo->armor << std::endl;
		std::cout << "exp: " << creatureInfo->exp << std::endl;
		std::cout << "speed: " << creatureInfo->speed << std::endl;
		std::cout << "ClassName: " << player->ControlPlayerInfos()->ClassName << std::endl;
	}
	//�Ѱܿ��� �κ��丮 ����
	{
		myInventoryStatusInfo.jobName = playerInfo->ClassName;
		myInventoryStatusInfo.playerMaxHp = creatureInfo->maxHealth;
		myInventoryStatusInfo.playerMaxMp = playerInfo->manaPoint;
		myInventoryStatusInfo.playerHealHp = playerInfo->HealthHeal;
		myInventoryStatusInfo.playerHealMp = playerInfo->ManaHeal;
		myInventoryStatusInfo.playerSpeed = creatureInfo->speed;
		myInventoryStatusInfo.playerExp = player->PlayerNowExp();
		myInventoryStatusInfo.playerAtkPower = playerInfo->AttackPower;
		myInventoryStatusInfo.skillPower = playerInfo->SkillPower;
		myInventoryStatusInfo.criticalChance = playerInfo->CriticalRate;
		myInventoryStatusInfo.armor = creatureInfo->armor;
		myInventoryStatusInfo.resistance = creatureInfo->resistance;
	}

	//��ġ
	//������ ��ġ
	FindGameText();
	inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("JobName");
	//inventoryText->SetActive(inventoryMenu.GetActive());
	if (inventoryMenu.GetActive())
	{
		inventoryText1->SetActive(true);
		inventoryText1->SetPosition(0, 0);
		inventoryText1->text.setFillColor(sf::Color::Red);
		inventoryText1->text.setString(myInventoryStatusInfo.jobName);
		//inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("");
		//inventoryText1 = (TextGo*)
		//inventoryText->SetPosition(100, 100);
		//inventoryText->text.setString("Bye");

		//inventoryText->sortLayer = 101;
		//Inventory* inventory = (Inventory*)SCENE_MGR.GetCurrScene()->FindGo("inventory");


		std::cout << std::endl;
		std::cout << std::endl;








	}
	//return myInventoryStatusInfo;
}
void Inventory::FindGameText()
{
	inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("JobName");
	inventoryText2 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("HP");
	inventoryText3 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("HealHP");
	inventoryText4 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("MP");
	inventoryText5 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("HealMP");
	inventoryText6 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Speed");
	inventoryText7 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Exp");
	inventoryText8 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("AtkPower");
	inventoryText9 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("SkillPower");
	inventoryText10 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("CritRate");
	inventoryText11 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("EvadeRate");
	inventoryText12 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Defense");
	inventoryText13 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Resistance");
	inventoryText14 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Luck");
	inventoryText15 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("Gold");
	inventoryText16 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("BronzeKey");
	inventoryText17 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("SilverKey");
	inventoryText18 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("GoldKey");
	inventoryText19 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("RedKey");
}