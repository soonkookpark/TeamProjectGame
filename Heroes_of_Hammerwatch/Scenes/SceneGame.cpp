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
#include "Inventory.h"
#include"TextGo.h"

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
	Inventory* inventory = (Inventory*)AddGo(new Inventory("inventory"));
	//inventory->InventoryDisplay();
	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->LoadDrawTexture("graphics/mine/tilemap.csv");

	player = (Paladin*)AddGo(new Paladin());
	player->SetPosition(100, 100);
	player->SetActive(true);
	player->SetTile(tileMap);
	inventory->SetPlayer(player);

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
	/*Monster* monster = dynamic_cast<Monster*>(AddGo(new Monster("Tick")));
	monster->SetPosition(300,300);
	
	monster = dynamic_cast<Monster*>((AddGo(new Monster("Bat"))));
	monster->SetPosition(200,200);

	EliteTick* ET = dynamic_cast<EliteTick*>(AddGo(new EliteTick()));
	ET->SetPosition(400, 400);*/
	/*
	BossGolem* BG = dynamic_cast<BossGolem*>(AddGo(new BossGolem()));
	BG->SetPosition(300, 100);


	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("GoldKey")));
	item->SetPosition(100, 150);

	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("SmallManaStone")));
	item->SetPosition(150, 150);
	*/
	
	FieldItem* item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item1")));
	item->SetPosition(150, 100);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item2")));
	item->SetPosition(250, 100);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item3")));
	item->SetPosition(350, 100);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item4")));
	item->SetPosition(150, 400);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item5")));
	item->SetPosition(250, 400);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item6")));
	item->SetPosition(350, 400);
	item = dynamic_cast<FieldItem*>(AddGo(new FieldItem("Item7")));
	item->SetPosition(150, 400);
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

	worldView.setCenter(player->GetPosition());

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos(); //마우스 위치
	sf::Vector2f mouseUiPos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mouseUiPos.x << "," << mouseUiPos.y << std::endl;
	}
	Scene::Update(dt);

	//std::cout << tileMap->vertexArray.getBounds().left << tileMap->vertexArray.getBounds().top <<
	//	tileMap->vertexArray.getBounds().width << tileMap->vertexArray.getBounds().height << std::endl;
	

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
	//window.draw(sprite)
}