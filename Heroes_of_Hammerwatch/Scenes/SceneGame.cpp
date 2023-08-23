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

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y };

	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);*/
	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->LoadDrawTexture("graphics/mine/new.csv");

	startBT = (UIButton*)AddGo(new UIButton("graphics/button/button_load.png", "graphics/button/button_load.png"));
	startBT->SetPosition(0.f, 0.f);
	startBT->OnClick = [this]()
	{
		bool check = false;
		while (!check)
		{
			TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
			tempTileMap->DrawTexture(mapSize.x, mapSize.y);

			//GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
			//tempGridMap->DrawGrid(mapSize.x, mapSize.y, 16);

			//OnTileMap* tempOnTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));
			//tempOnTileMap->LoadDrawOnTile(tempTileMap);


			if (tileMap != nullptr)
			{
				RemoveGo(tileMap);
				delete tileMap;
				tileMap = nullptr;
			}
			if (gridMap != nullptr)
			{
				RemoveGo(gridMap);
				delete gridMap;
				gridMap = nullptr;
			}
			if (onTileMap != nullptr)
			{
				RemoveGo(onTileMap);
				delete onTileMap;
				onTileMap = nullptr;
			}

			tileMap = tempTileMap;
			//gridMap = tempGridMap;
			//onTileMap = tempOnTileMap;

			//tileMap->SetOnTileMap(onTileMap);

			/*for (int i = 0; i < 6; i++)
			{
				tileMap->Divide();
			}*/
			//tileMap->ConnectRoom();
			//check = tileMap->SelectDoor();
			check = true;
		}
		//player->SetPosition(onTileMap->GetStartPos().x+32, onTileMap->GetStartPos().y + 96);
		//tileMap->Summon();
		 
		
		//player->SetPosition(-100, -100);
		//player->SetTile(tileMap);
		player->SetTile(tileMap);
	};

	player = (Paladin*)AddGo(new Paladin());
	player->SetPosition(24, 24);
	player->SetActive(true);
	player->SetTile(tileMap);

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

	finder = tileMap->GetAstar();

	auto size = FRAMEWORK.GetWindowSize();

	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	worldView.zoom(0.5f);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	finder->SetTileArray(tileMap->GetTileArray());


	/*
	Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", "mob", {100, 340})));
	monster->SetTileMap(tileMap);
	//monster->ControlCreatureInfos()->speed /= 5.f;

	monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
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
	Scene::Exit();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);

	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::R))
	{
		std::list<Creature*> test;
		test.push_back(dynamic_cast<Creature*>(FindGo("player")));
		Lurker* arrowTest = dynamic_cast<Lurker*>(AddGo(new Lurker("test", dynamic_cast<Creature*>(FindGo("Tick")), test, ScreenToWorldPos(InputMgr::Instance().GetMousePos()),{1.f,0.f})));

	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::T))
	{
		std::list<Creature*> test;
		test.push_back(dynamic_cast<Creature*>(FindGo("player")));
		DelayedProjectile* arrowTest = dynamic_cast<DelayedProjectile*>(AddGo(new DelayedProjectile("test", dynamic_cast<Creature*>(FindGo("Tick")), test, ScreenToWorldPos(InputMgr::Instance().GetMousePos()))));
	}
	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::C))
	{
		std::list<Creature*> test;
		test.push_back(dynamic_cast<Creature*>(FindGo("player")));
		Arrow* arrowTest = dynamic_cast<Arrow*>(AddGo(new Arrow("test",dynamic_cast<Creature*>( FindGo("Tick")),test , {1,1},{1,1})));
	}
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
	
	worldView.setCenter(player->GetPosition());

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
	//std::cout << INPUT_MGR.GetMousePos().x << ", " << INPUT_MGR.GetMousePos().y << std::endl;
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::DieMonster(Monster* mob)
{
	RemoveGo(mob);
	
	if (mob != nullptr)
	{
		delete mob;
		mob = nullptr;
	}
}
