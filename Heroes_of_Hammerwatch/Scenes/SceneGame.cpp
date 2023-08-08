#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Framework.h"
#include "RectangleGo.h"
#include "UIButton.h"
#include "Monster.h"
#include "EliteTick.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";

	/*resources.push_back(std::make_tuple(ResourceTypes::Texture,"graphics/sprite_sheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/button.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/clickButton.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/park.png"));*/
}

void SceneGame::Init() // 안바뀔거면 여기
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f groundSize = { windowSize.x,windowSize.y/2 };

	player = (Player*)AddGo(new Player());
	player->sortLayer = 1;

	/*UIButton* button = (UIButton*)AddGo(new UIButton("graphics/button.png"));
	button->SetOrigin(Origins::TR);
	button->sortLayer = 100;
	button->SetPosition(windowSize.x,0.f);

	button->OnEnter = [button]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/clickButton.png");
		button->sprite.setTexture(*tex);
		std::cout << "Enter" << std::endl;
	};
	button->OnExit = [button]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture(button->textureId);
		button->sprite.setTexture(*tex);
		std::cout << "Exit" << std::endl;
	};
	button->OnClick = []() {
		std::cout << "Click" << std::endl;
	};
	
	SpriteGo* BG = (SpriteGo*)AddGo(new SpriteGo("graphics/park.png","Park"));
	BG->sprite.setScale(10.f, 10.f);
	BG->sortLayer = 0;
	BG->SetOrigin(Origins::MC);*/
	
	
	//RectangleGo* ground = (RectangleGo*)AddGo(new RectangleGo(groundSize, "Ground"));
	//ground->SetPosition(0, 0);
	//ground->rectangle.setFillColor(sf::Color::Cyan);
	//ground->SetOrigin(Origins::TC);
	//groundBounds = ground->rectangle.getGlobalBounds();//
	//groundBounds.height -= groundSize.y;

	//layer->SetGroundBounds(groundBounds);
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
	//auto centerPos = size / 2.f;
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	Player* palyer = (Player*)AddGo(new Player("","player"));
	palyer->SetPosition(-600, -600);

	Monster* monster = (Monster*)AddGo(new Monster("Bat"));
	monster->SetPosition(20, 20);
	//monster->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/testSprite.png"));

	EliteTick* ET = (EliteTick*)AddGo(new EliteTick());
	ET->SetPosition(300, 300);

	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	//worldView.setCenter(this->player->GetPosition());
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
