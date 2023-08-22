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

	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);*/
	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->LoadDrawTexture("graphics/mine/new.csv");

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

	finder = new Astar();

	auto size = FRAMEWORK.GetWindowSize();

	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	worldView.zoom(0.5f);

	uiView.setSize(size);
	uiView.setCenter(0.f, 0.f);
	finder->SetTileArray(tileMap->GetTileArray());


	Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick", "mob", {100, 340})));
	monster->SetTileMap(tileMap);
	monster->ControlCreatureInfos()->speed = 0.5f;

	/*
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
	delete(finder);
	Scene::Exit();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);

	if (InputMgr::Instance().GetKeyDown(sf::Keyboard::Z))
	{
		Creature* player = (Creature*)FindGo("player");
		Creature* tick = (Creature*)FindGo("Tick");
		std::cout << "Player`s positoin = " << player->GetTileIndex().x << " , " << player->GetTileIndex().y << std::endl;
		std::cout << "Tick`s positoin = " << tick->GetTileIndex().x << " , " << tick->GetTileIndex().y << std::endl;
		std::stack<sf::Vector2i>path = *(finder->FindPath(player, tick));
		while (!path.empty()) {
			sf::Vector2i value = path.top(); // 스택의 맨 위 원소 가져오기
			std::cout << value.x << " , "<< value.y << std::endl; // 원소 출력
			path.pop();
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