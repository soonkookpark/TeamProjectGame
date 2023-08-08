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

void SceneGame::Init() // �ȹٲ�Ÿ� ����
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y };
	
	player = (Player*)AddGo(new Player());
	player->sortLayer = 1;
	player->SetPosition(1, 1);
	player->SetActive(true);
	
	//TestCode
	std::cout << "��������" << std::endl;
	RectangleGo* Baggounrd = (RectangleGo*)AddGo(new RectangleGo(groundSize, "Hi"));
	Baggounrd->SetOrigin(Origins::ML);
	Baggounrd->SetPosition(0, 0);
	Baggounrd->rectangle.setFillColor(sf::Color::Blue);
	RectangleGo* leftGround = (RectangleGo*)AddGo(new RectangleGo(groundSize, "Bye"));
	leftGround->SetOrigin(Origins::MR);
	leftGround->SetPosition(0, 0);
	leftGround->rectangle.setFillColor(sf::Color::Magenta);

	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);

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

void SceneGame::Enter() //���͸� ������ �ٲ�°� ����
{
	Scene::Enter();

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
	worldView.setCenter(player->GetPosition());
	//ĳ���� ��ġ �׽�Ʈ�ڵ�
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}