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
	button->SetPosition(windowSize.x,0.f);
	*/

	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
	tileMap->DrawTexture("graphics/mine/tilemap.csv");

	gridMap = (GridMap*)AddGo(new GridMap());
	gridMap->DrawGrid(tileMap);


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

	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	
	if (INPUT_MGR.GetKey(sf::Keyboard::W))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - 0.5);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		worldView.setCenter(worldView.getCenter().x - 0.5, worldView.getCenter().y);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::S))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + 0.5);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		worldView.setCenter(worldView.getCenter().x + 0.5, worldView.getCenter().y);
	}

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
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}