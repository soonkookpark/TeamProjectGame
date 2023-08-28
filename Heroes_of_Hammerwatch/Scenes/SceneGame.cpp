#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Framework.h"
#include "TileMap.h"
#include "GridMap.h"
#include "OnTileMap.h"
#include "RectangleGo.h"
#include "UIButton.h"
#include "Monster.h"
#include "EliteTick.h"
#include "Paladin.h"
#include "BossGolem.h"
#include "Items/FieldItem.h"
#include "DataTableMgr.h"
#include "Tools/Astar.h"
#include "Projectiles/AllProjectiles.hpp"
#include "Inventory.h"
#include "TextGo.h"
#include "Utils.h"
#include "SaveLoadLogic.h"



SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y };

	inventory = (Inventory*)AddGo(new Inventory("inventory"));
	inventory->SetPlayer(player);
	//inventory->InventoryDisplay();

	/*tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->LoadDrawTexture("graphics/mine/tilemap.csv");

	tileMap->SetOnTileMap(onTileMap);
	tileMap->LoadDrawTexture("graphics/mine/boss.csv");
	onTileMap->LoadDrawOnTile(tileMap);*/
	

	//inventoryText->sortLayer = UI_TEXT;
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf","JobName"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "HP"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "HealHP"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "MP"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "HealMP"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Speed"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Exp"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "AtkPower"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "SkillPower"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "CritRate"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "EvadeRate"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Defense"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Resistance"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Luck"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "Gold"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "BronzeKey"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "SilverKey"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "GoldKey"));
	inventoryText = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf", "RedKey"));
	
	checkClear = true;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter() //엔터를 누르면 바뀌는건 여기
{

	RESOURCE_MGR.LoadFromCsv(resourceListPath, false);
	auto size = FRAMEWORK.GetWindowSize();

	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	worldView.zoom(0.5f);

	uiView.setSize(size);
	uiView.setCenter(0.f, 0.f);


	/*Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", "mob", {100, 340})));
	monster->SetTileMap(tileMap);
	monster->ControlCreatureInfos()->speed /= 5.f;
	EliteTick* ET = dynamic_cast<EliteTick*>(AddGo(new EliteTick()));
	ET->SetPosition(400, 400);
	ET->SetTileMap(tileMap);*/
	/*
	//monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
	monster->SetPosition(200,200);
	monster->SetTileMap(tileMap);

	monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
	monster->SetPosition(220, 200);
	monster->SetTileMap(tileMap);

	monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
	monster->SetPosition(200, 220);
	monster->SetTileMap(tileMap);

	monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
	monster->SetPosition(220, 220);
	monster->SetTileMap(tileMap);
	


	
	BossGolem* BG = dynamic_cast<BossGolem*>(AddGo(new BossGolem()));
	BG->SetPosition(300, 100);


	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("GoldKey")));
	item->SetPosition(100, 150);

	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("SmallManaStone")));
	item->SetPosition(150, 150);
	*/
	
	Scene::Enter();
}

void SceneGame::Exit()
{
	for (auto GO : gameObjects)
	{
		if (GO->GetName() == "mob" || GO->GetName() == "EliteTick" || GO->GetName() == "BossGolem" || GO->GetName() == "FieldItem")
		{
			RemoveGo(GO);
		}
	}
	//delete(finder);

	

	

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	CheckClearStage();
	if (setting)
	{
		player->SetTile(tileMap);
		player->SetOnTileMap(onTileMap);
		setting = false;
	}
	SettingStage();

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseUiPos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mouseUiPos.x << "," << mouseUiPos.y << std::endl;
	}
	Scene::Update(dt);

	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::X))
	{
		Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", { 100, 340 })));
		monster->SetTileMap(tileMap);
		monster->Reset();
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::T))
	{
		std::list<Creature*> test;
		test.push_back(dynamic_cast<Creature*>(FindGo("player")));
		for (int i = 0; i < 8; i++)
		{
			DelayedProjectile* arrowTest = dynamic_cast<DelayedProjectile*>(AddGo(new DelayedProjectile("test", dynamic_cast<Creature*>(FindGo("Tick")), test, (sf::Vector2f(600.f, 400.f) + Utils::RandomInCircle(200.f)))));
		}
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::Z))
	{
		Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Maggot", { 600, 600 })));
		monster->SetTileMap(tileMap);
		monster->Reset();
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::F10))
	{
		EliteTick* ET = dynamic_cast<EliteTick*>(AddGo(new EliteTick()));
		ET->SetPosition(400, 400);
		ET->SetTileMap(tileMap);
		ET->Reset();
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::F9))
	{
		Monster* monster = dynamic_cast<Monster*>(AddGo(new BossGolem()));
		monster->SetTileMap(tileMap);
		monster->SetPosition(600, 400);
		monster->Reset();
	}
	
	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(0.9f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(1.1f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		tileMap->SetActive(!tileMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		gridMap->SetActive(!gridMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F3))
	{
		onTileMap->SetActive(!onTileMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F8))
	{
		std::cout << ScreenToWorldPos(mousePos).x << " , " << ScreenToWorldPos(mousePos).y << std::endl;	
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::End))
	{
		checkClear = true;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Home))
	{
		player->ChangeLayer();
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	//std::cout << ScreenToWorldPos(INPUT_MGR.GetMousePos()).x << ", " << ScreenToWorldPos(INPUT_MGR.GetMousePos()).y << std::endl;
	inventory = (Inventory*)FindGo("inventory");
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Insert))
	{
		//SaveLoadLogic::GetData(this->player, this->inventory);
	}


}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::DieMonster(Monster* mob)
{
	RemoveGo(mob);
	//SummonedMonster.remove(mob); 
	int randNum;
	randNum = Utils::RandomRange(1, 14);
	std::string randNumStr = std::to_string(randNum);
	std::string itemName = "Item";
	std::string RandomItemName = itemName + randNumStr;
	FieldItem* item = dynamic_cast<FieldItem*>(AddGo(new FieldItem(RandomItemName)));
	item->SetPosition(mob->GetPosition());
	
	item->Reset();



	/*auto it = std::find(SummonedMonster.begin(), SummonedMonster.end(), mob);
	if (it != SummonedMonster.end())
		SummonedMonster.erase(it);*/
}

void SceneGame::SettingStage()
{
	if (!checkClear) return;

	if (player == nullptr)
	{
		player = (Paladin*)AddGo(new Paladin());
		inventory->SetPlayer(player);
		
	}
	
	if (!SummonedMonster.empty())
	{
		for (Monster* mob : SummonedMonster)
		{
			gameObjects.remove(mob);

			if (mob != nullptr)
			{
				delete mob;
				mob = nullptr;
			}
		}
		SummonedMonster.clear();
	}


	stage++;

	if (stage < 3)
	{
		player->SetTile(nullptr);
		bool check = false;
		while (!check)
		{
			TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
			GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
			OnTileMap* tempOnTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));

			tempTileMap->SetOnTileMap(tempOnTileMap);
			tempTileMap->DrawTexture(mapSize.x, mapSize.y);
			tempGridMap->DrawGrid(mapSize.x, mapSize.y, 16);
			tempOnTileMap->LoadDrawOnTile(tempTileMap);

			finder = tempTileMap->GetAstar();
			finder->SetTileArray(tempTileMap->GetTileArray());

			if (tileMap != nullptr)
			{
				gameObjects.remove(tileMap);
				delete tileMap;
				tileMap = nullptr;
			}
			if (gridMap != nullptr)
			{
				gameObjects.remove(gridMap);
				delete gridMap;
				gridMap = nullptr;
			}
			if (onTileMap != nullptr)
			{
				gameObjects.remove(onTileMap);
				delete onTileMap;
				onTileMap = nullptr;
			}

			tileMap = tempTileMap;
			gridMap = tempGridMap;
			onTileMap = tempOnTileMap;

			for (int i = 0; i < 6; i++)
			{
				tileMap->Divide();
			}
			tileMap->ConnectRoom();
			check = tileMap->SelectDoor();
		}
	
		
		player->SetPosition((onTileMap->GetStartIndex().x) * 16 + 32, (onTileMap->GetStartIndex().y * 16) + 96);
		//player->SetTile(tileMap);
		tileMap->Summon();
		checkClear = false;
		setting = true;
		return;
	}
	else if (stage == 3)
	{
		player->SetTile(nullptr);

		TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
		GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
		OnTileMap* tempOnTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));

		tempTileMap->SetOnTileMap(tempOnTileMap);
		tempTileMap->LoadDrawTexture("graphics/mine/boss.csv");
		tempGridMap->DrawGrid(tempTileMap->TileIntSize().x, tempTileMap->TileIntSize().y, 16);
		tempOnTileMap->LoadDrawOnTile(tempTileMap);

		tempOnTileMap->ChangeDoor(tempOnTileMap->GetStartIndex() - sf::Vector2i{ 0, 4 }, tempOnTileMap->GetEntIndex() + sf::Vector2i{ 1, 0 }, tempTileMap);

		if (tileMap != nullptr)
		{
			gameObjects.remove(tileMap);
			delete tileMap;
			tileMap = nullptr;
		}
		if (gridMap != nullptr)
		{
			gameObjects.remove(gridMap);
			delete gridMap;
			gridMap = nullptr;
		}
		if (onTileMap != nullptr)
		{
			gameObjects.remove(onTileMap);
			delete onTileMap;
			onTileMap = nullptr;
		}

		tileMap = tempTileMap;
		gridMap = tempGridMap;
		onTileMap = tempOnTileMap;

		//포지션 바꿔야됨
		//player->SetPosition(onTileMap->GetStartIndex().x + 32, onTileMap->GetStartIndex().y + 96);
		
		player->SetPosition((onTileMap->GetStartIndex().x) * 16 + 32, (onTileMap->GetStartIndex().y * 16) + 96);
		//player->SetTile(tileMap);
		checkClear = false;
		setting = true;
		return;
	}
	else
	{
		stage = 0;
		checkClear = true;
	}
}

void SceneGame::Summon(Monster* monster)
{
	SummonedMonster.push_back(monster);
}

void SceneGame::CheckClearStage()
{
	if (tileMap != nullptr)
	{
		if (tileMap->CheckEnt(player->GetPlayerBox().getGlobalBounds()))
		{
			checkClear = true;
		}
	}
}