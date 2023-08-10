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
#include "SpriteGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y };
	Hi = (SpriteGo*)AddGo(new SpriteGo("", "Hi"));

	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);*/
	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->DrawTexture("graphics/mine/tilemap.csv");

	player = (Paladin*)AddGo(new Paladin());
	player->SetPosition(100, 100);
	player->SetActive(true);
	player->SetTile(tileMap);
	//testcode
	animation1.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/MonsterTables/EliteTick/AttackD.csv"));
	animation1.SetTarget(&Hi->sprite);
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
	Monster* monster = (Monster*)AddGo(new Monster("Tick"));
	monster->SetPosition(300,300);

	monster = (Monster*)AddGo(new Monster("Bat"));
	monster->SetPosition(200,200);

	EliteTick* ET = (EliteTick*)AddGo(new EliteTick());
	ET->SetPosition(400, 400);

	//test
	Hi->SetPosition(player->GetPosition());
	Hi->sortLayer = 205;
	Scene::Enter();
}

void SceneGame::Exit()
{
	for (auto GO : gameObjects)
	{
		if (GO->GetName() == "mob" || GO->GetName() == "EliteTick")
		{
			RemoveGo(GO);
		}
	}
	Scene::Exit();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);
	
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F11))
	{
		animation1.Play("AttackD");
	
	}
	animation1.Update(dt);

	//std::cout << INPUT_MGR.GetMousePos().x << ", " << INPUT_MGR.GetMousePos().y << std::endl;
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}