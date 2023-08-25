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

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y };

	/*tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	onTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));

	tileMap->SetOnTileMap(onTileMap);
	tileMap->LoadDrawTexture("graphics/mine/boss.csv");
	onTileMap->LoadDrawOnTile(tileMap);*/

	startBT = (UIButton*)AddGo(new UIButton("graphics/button/button_load.png", "graphics/button/button_load.png"));
	startBT->SetPosition(0.f, 0.f);
	startBT->OnClick = [this]()
	{
		checkClear = true;
	};

	/*player = (Paladin*)AddGo(new Paladin());
	player->SetPosition(600, 500);
	player->SetActive(true);
	player->SetTile(tileMap);*/

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
	uiView.setCenter(size * 0.5f);


	//Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", "mob", {100, 340})));
	//monster->SetTileMap(tileMap);
	//monster->ControlCreatureInfos()->speed /= 5.f;

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
	/*
	EliteTick* ET = dynamic_cast<EliteTick*>(AddGo(new EliteTick()));
	ET->SetPosition(400, 400);
	ET->SetTileMap(tileMap);

	/*
	BossGolem* BG = dynamic_cast<BossGolem*>(AddGo(new BossGolem()));
	BG->SetPosition(300, 100);

	FieldItem* item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Apple")));
	item->SetPosition(150, 100);

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

	Scene::Update(dt);

	


	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::X))
	{
		Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", "mob", { 100, 340 })));
		monster->SetTileMap(tileMap);
		monster->Reset();
	}
	

	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::Z))
	{
		int i = 1;
		Creature* player = (Creature*)FindGo("player");
		Creature* tick = (Creature*)FindGo("Tick");
		std::cout << "Player`s positoin = " << player->GetTileIndex().x << " , " << player->GetTileIndex().y << std::endl;
		std::cout << "Tick`s positoin = " << tick->GetTileIndex().x << " , " << tick->GetTileIndex().y << std::endl;
		std::stack<sf::Vector2i>path = *(finder->FindPath(player, tick));
		while (!path.empty()) {
			sf::Vector2i value = path.top(); // 스택의 맨 위 원소 가져오기
			std::cout <<i<<" : \t"<< value.x << " , " << value.y << std::endl; // 원소 출력
			path.pop();
			i++;
		}
	}
	//std::cout << tileMap->vertexArray.getBounds().left << tileMap->vertexArray.getBounds().top <<
	//	tileMap->vertexArray.getBounds().width << tileMap->vertexArray.getBounds().height << std::endl;
	
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
		player->SetTile(tileMap);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		gridMap->SetActive(!gridMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F3))
	{
		onTileMap->SetActive(!onTileMap->GetActive());
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	//std::cout << ScreenToWorldPos(INPUT_MGR.GetMousePos()).x << ", " << ScreenToWorldPos(INPUT_MGR.GetMousePos()).y << std::endl;
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::DieMonster(Monster* mob)
{
	RemoveGo(mob);
	//SummonedMonster.remove(mob); 

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
