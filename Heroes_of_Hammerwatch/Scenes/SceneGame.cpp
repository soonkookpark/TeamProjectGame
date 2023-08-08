#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Framework.h"
#include "TileMap.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y/2 };

	player = (Player*)AddGo(new Player());
	player->sortLayer = 1;

	tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png", "graphics/mine/mine_tile.png"));
	tileMap->Load("graphics/mine/tilemap.csv");
	tileMap->sortLayer = 1;

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
	auto size = FRAMEWORK.GetWindowSize();
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

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
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - 1);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		worldView.setCenter(worldView.getCenter().x - 1, worldView.getCenter().y);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::S))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + 1);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		worldView.setCenter(worldView.getCenter().x + 1, worldView.getCenter().y);
	}

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}