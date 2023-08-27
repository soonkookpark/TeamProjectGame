#include "stdafx.h"
#include "Inventory.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "TextGo.h"
#include <cmath>
#include <iomanip>
#include <sstream>

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
		float iconSize = 36.0f; // 아이콘 이미지 크기

		int itemsPerRow = 4; // 한 행에 표시될 아이템 수
		int rowCount = 11;   // 전체 행 수
		
		std::cout << equipItemImageInMyInventory.size() << std::endl;
		
		//1. 아이템 먹은 부분
		{
			for (int row = 0; row < rowCount; ++row)
			{
				for (int col = 0; col < itemsPerRow; ++col)
				{
					int index = row * itemsPerRow + col;

					// 벡터 배열의 인덱스가 유효한지 확인
					if (index < equipItemImageInMyInventory.size())
					{
						Inventory::MyItemInfo* item = equipItemImageInMyInventory[index];
						//std::cout << equipItemImageInMyInventory.size() << std::endl;
						//item->iconImage.
						// 아이템 아이콘 이미지를 특정 위치에 그림
						item->iconImage.setScale(3.f, 3.f);
						//가로크기
						//float iconXSize = item->iconImage.getGlobalBounds().width*0.5;
						//세로크기
						//float iconYSize = item->iconImage.getGlobalBounds().height*0.5f;
						//std::cout << iconXSize << "," << iconYSize << std::endl;
						//item->iconImage.setOrigin(iconXSize, iconYSize);
						std::cout << "이것은 오리진" << std::endl;
						//std::cout << item->iconImage.getOrigin().x << ", " << item->iconImage.getOrigin().y << std::endl;
						item->iconImage.setPosition(displayPosition.x + col * (iconSize + 12.0f), displayPosition.y + row * (iconSize + 12.0f));
						std::cout << item->iconImage.getPosition().x << ", " << item->iconImage.getPosition().y << std::endl;
						//std::cout << item->itemDescription << std::endl;
						//item->iconImage.setScale(iconSize / item->iconImage.getLocalBounds().width, iconSize / item->iconImage.getLocalBounds().height);


					}
				}
			}
		}

		//2. 능력치 출력
		{
			Collocate(player);
			
		}
	}
	else 
	{
		inventoryBox.setOutlineColor({ 0,0,0,0 });
		Collocate(player);
		//TextGo* inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("JobName");
		//inventoryText1->SetActive(false);
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
	//inventoryMenu.SetPosition(500.f, 500.f)
	//Player* player = (Player*)SCENE_MGR.GetCurrScene()->FindGo("")
}

void Inventory::Release()
{
	inventoryImageUI.clear();
}

void Inventory::Update(float dt)
{
	(player->GetPosition());
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
	//넘겨오는 인벤토리 정보
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

	//배치
	//아이템 배치
	FindGameText();
	//inventoryText1 = (TextGo*)SCENE_MGR.GetCurrScene()->FindGo("JobName");
	//inventoryText->SetActive(inventoryMenu.GetActive());
	TextOnOff(inventoryMenu.GetActive());
	if (inventoryMenu.GetActive())
	{
		TextSetting();
		









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
	inventoryText1->sortLayer = UI_TEXT;
	inventoryText2->sortLayer = UI_TEXT;
	inventoryText3->sortLayer = UI_TEXT;
	inventoryText4->sortLayer = UI_TEXT;
	inventoryText5->sortLayer = UI_TEXT;
	inventoryText6->sortLayer = UI_TEXT;
	inventoryText7->sortLayer = UI_TEXT;
	inventoryText8->sortLayer = UI_TEXT;
	inventoryText9->sortLayer = UI_TEXT;
	inventoryText10->sortLayer = UI_TEXT;
	inventoryText11->sortLayer = UI_TEXT;
	inventoryText12->sortLayer = UI_TEXT;
	inventoryText13->sortLayer = UI_TEXT;
	inventoryText14->sortLayer = UI_TEXT;
	inventoryText15->sortLayer = UI_TEXT;
	inventoryText16->sortLayer = UI_TEXT;
	inventoryText17->sortLayer = UI_TEXT;
	inventoryText18->sortLayer = UI_TEXT;
	inventoryText19->sortLayer = UI_TEXT;
}

void Inventory::TextSetting()
{
	//직업이름
	{
		inventoryText1->SetPosition(53, -311);
		inventoryText1->text.setFillColor(sf::Color::Magenta);
		inventoryText1->text.setString(myInventoryStatusInfo.jobName);
		inventoryText1->SetOrigin(Origins::MC);
		inventoryText1->text.setScale(2.f, 2.f);
	}
	//최대체력
	{
		inventoryText2->SetPosition(-413, -195);
		inventoryText2->text.setFillColor(sf::Color::White);
		inventoryText2->text.setString(std::to_string(myInventoryStatusInfo.playerMaxHp));
	}
	//최대마나
	{
		inventoryText3->SetPosition(-241, -195);
		inventoryText3->text.setFillColor(sf::Color::White);
		inventoryText3->text.setString(std::to_string(myInventoryStatusInfo.playerMaxMp));
	}
	//스피드
	{
		inventoryText4->SetPosition(-31, -170);
		inventoryText4->text.setFillColor(sf::Color::White);
		inventoryText4->text.setString(std::to_string(myInventoryStatusInfo.playerSpeed));
	}
	//플레이어 경험치
	{
		inventoryText5->SetPosition(117, -170);
		inventoryText5->text.setFillColor(sf::Color::White);
		inventoryText5->text.setString(std::to_string(myInventoryStatusInfo.playerExp));
	}
	//공격력
	{
		inventoryText6->SetPosition(-407, -36);
		inventoryText6->text.setFillColor(sf::Color::White);
		inventoryText6->text.setString(std::to_string(myInventoryStatusInfo.playerAtkPower));
	}
	//스킬공격력
	{
		inventoryText7->SetPosition(-231, -36);
		inventoryText7->text.setFillColor(sf::Color::White);
		inventoryText7->text.setString(std::to_string(myInventoryStatusInfo.skillPower));
	}
	//크리티컬 확률
	{
		inventoryText8->SetPosition(-52, -36);
		inventoryText8->text.setFillColor(sf::Color::White);
		inventoryText8->text.setString(std::to_string(myInventoryStatusInfo.criticalChance));
	}
	//방어력
	{
		inventoryText9->SetPosition(-419, 10);
		inventoryText9->text.setFillColor(sf::Color::White);
		inventoryText9->text.setString(std::to_string(myInventoryStatusInfo.armor));
	}
	//마저
	{
		inventoryText10->SetPosition(-239, 10);
		inventoryText10->text.setFillColor(sf::Color::White);
		inventoryText10->text.setString(std::to_string(myInventoryStatusInfo.resistance));
	}
	//체력회복량
	{
		inventoryText11->SetPosition(-414, -150);
		inventoryText11->text.setFillColor(sf::Color::White);
		//소수점 출력방식
		std::ostringstream healHp;
		healHp << std::fixed << std::setprecision(2) << myInventoryStatusInfo.playerHealHp;
		inventoryText11->text.setString(healHp.str());
	}
	//마나회복량
	{
		inventoryText12->SetPosition(-241, -150);
		inventoryText12->text.setFillColor(sf::Color::White);

		std::ostringstream healMp;
		healMp << std::fixed << std::setprecision(2) << myInventoryStatusInfo.playerHealMp;
		inventoryText12->text.setString(healMp.str());
	}
	//행운
	{
		int luckySeven = 7;
		inventoryText13->SetPosition(129, 10);
		inventoryText13->text.setFillColor(sf::Color::White);
		inventoryText13->text.setString(std::to_string(luckySeven));
	}
	//플레이어 골드
	{
		int playerGold = 1004;
		inventoryText14->SetPosition(-441,121);
		inventoryText14->text.setFillColor(sf::Color::White);
		inventoryText14->text.setString(std::to_string(playerGold));
	}
	//회피율
	{
		int evadeRate = 0;
		inventoryText15->SetPosition(132, -36);
		inventoryText15->text.setFillColor(sf::Color::White);
		inventoryText15->text.setString(std::to_string(evadeRate));
	}
	//브론즈 키
	{
		int bronzeKey = 0;
		inventoryText16->SetPosition(-80, 160);
		inventoryText16->text.setFillColor(sf::Color::White);
		inventoryText16->text.setString(std::to_string(bronzeKey));
	}
	//실버 키
	{
		int silverKey = 0;
		inventoryText17->SetPosition(13, 160);
		inventoryText17->text.setFillColor(sf::Color::White);
		inventoryText17->text.setString(std::to_string(silverKey));
	}
	//골드키
	{
		int goldKey = 0;
		inventoryText18->SetPosition(106, 160);
		inventoryText18->text.setFillColor(sf::Color::White);
		inventoryText18->text.setString(std::to_string(goldKey));
	}
	//빨간키
	{
		int redKey = 0;
		inventoryText19->SetPosition(189, 160);
		inventoryText19->text.setFillColor(sf::Color::White);
		inventoryText19->text.setString(std::to_string(redKey));
	}
}

void Inventory::TextOnOff(bool tf)
{
	inventoryText1->SetActive(tf);
	inventoryText2->SetActive(tf);
	inventoryText3->SetActive(tf);
	inventoryText4->SetActive(tf);
	inventoryText5->SetActive(tf);
	inventoryText6->SetActive(tf);
	inventoryText7->SetActive(tf);
	inventoryText8->SetActive(tf);
	inventoryText9->SetActive(tf);
	inventoryText10->SetActive(tf);
	inventoryText11->SetActive(tf);
	inventoryText12->SetActive(tf);
	inventoryText13->SetActive(tf);
	inventoryText14->SetActive(tf);
	inventoryText15->SetActive(tf);
	inventoryText16->SetActive(tf);
	inventoryText17->SetActive(tf);
	inventoryText18->SetActive(tf);
	inventoryText19->SetActive(tf);
}

