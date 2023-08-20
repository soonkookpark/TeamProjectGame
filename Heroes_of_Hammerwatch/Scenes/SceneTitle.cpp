#include "stdafx.h"
#include "SceneTitle.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"
#include "RectangleGo.h"
#include "UIButton.h"
#include "DataTableMgr.h"
#include "SliceSpriteGo.h"

SceneTitle::SceneTitle() :Scene(SceneId ::Title)
{
	resourceListPath = "scripts/SceneTitleResourceList.csv";
}

void SceneTitle::Init()
{
	Release();
	
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	SpriteGo* backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/TitleScreen.png", "BackGround"));
	backGround->sortLayer = -1;
	SpriteGo* titleName = (SpriteGo*)AddGo(new SpriteGo("graphics/Title/TitleText.png", "TitleText"));
	titleName->sortLayer = 0;
	
	

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	RESOURCE_MGR.LoadFromCsv(resourceListPath, false);
	UIButtonMaker();
	Scene::Enter();
	SpriteGo* backGround = (SpriteGo*)FindGo("BackGround");
	backGround->SetOrigin(Origins::MC);
	backGround->SetPosition(windowSize * 0.5f);
	//backGround->sprite.setScale(2.f, 2.f);
	SpriteGo* titleName = (SpriteGo*)FindGo("TitleText");
	titleName->SetOrigin(Origins::MC);
	titleName->SetPosition(windowSize.x * 0.5f,windowSize.y*0.2);
	titleName->sprite.setScale(3.f, 3.f);
	
	SliceSpriteGo* startButton1 = (SliceSpriteGo*)FindGo("startButton1");
	startButton1->SetSize({ 66*2,36*2 });
	//startButton1->SetPosition(400, 810);
}


void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	
	//view 미루기
	// 
	//test
	SliceSpriteGo* startButton1 = (SliceSpriteGo*)AddGo(new SliceSpriteGo("graphics/Title/Button.png", { 4, 4,27,11 }, { 0,0, 33,18 }, "startButton1"));
	startButton1->SetPosition(400, 810);
	TestCode(dt);
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::TestCode(float dt)
{

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	SpriteGo* backGround = (SpriteGo*)FindGo("BackGround");
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mousePos.x << ", " << mousePos.y << std::endl;
		if(backGround->GetActive())
			std::cout << "잘 나오고 있음" << std::endl;
	}
	UIButton* startButton = (UIButton*)AddGo(new UIButton("graphics/Title/Button.png"));
	SliceSpriteGo* startButton1 = (SliceSpriteGo*)AddGo(new SliceSpriteGo("graphics/Title/Button.png", { 4, 4,27,11 }, { 0,0, 33,18 }, "startButton1"));
	startButton->OnEnter = [startButton1]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonOn.png");
		startButton1->SetTexture(*tex, { 4,4,27,11 }, { 0,0,33,18 });
		startButton1->SetSize({ 66 * 2,36 * 2 });
		//startButton1->SetPosition(startButton->GetPosition());
		startButton1->SetPosition(400, 810);
		std::cout << startButton1->GetPosition().x << startButton1->GetPosition().y << std::endl;

		std::cout << "Enter" << std::endl;
	};
}

void SceneTitle::UIButtonMaker()
{

	sf::Vector2f centerPos = windowSize * 0.5f;







	// 버튼을 3개 만들고 버튼 이미지를 변경하는 식 일단 이건 버튼임.
	//맨 왼쪽 버튼
	SliceSpriteGo* startButton1 = (SliceSpriteGo*)AddGo(new SliceSpriteGo("graphics/Title/Button.png", { 4, 4,27,11 }, { 0,0, 33,18 },"startButton1"));
	//두번째 버튼
	SliceSpriteGo* startButton2 = (SliceSpriteGo*)AddGo(new SliceSpriteGo("graphics/Title/Button.png", { 4, 4,27,11 }, { 0,0, 33,18 }, "startButton2"));
	//세번째 버튼
	SliceSpriteGo* startButton3 = (SliceSpriteGo*)AddGo(new SliceSpriteGo("graphics/Title/Button.png", { 4, 4,27,11 }, { 0,0, 33,18 }, "startButton3"));
	UIButton* startButton = (UIButton*)AddGo(new UIButton("graphics/Title/Button.png"));
	UIButton* settingButton = (UIButton*)AddGo(new UIButton("graphics/Title/Button.png"));
	UIButton* exitButton = (UIButton*)AddGo(new UIButton("graphics/Title/Button.png"));
	

	//버튼에 올라갔을때
	//startButton1->OnEnter = startButton->OnEnter;
	//캐릭터 설정버튼
	startButton->SetOrigin(Origins::TC);
	startButton->sortLayer = 100;
	startButton->SetPosition(windowSize.x*0.25, windowSize.y * 0.9f);
	startButton->sprite.setScale(7.5f, 2.5f);
	startButton1->SetOrigin(Origins::TC);
	//startButton1->SetPosition(windowSize.x * 0.25, windowSize.y * 0.9f);
	startButton1->sortLayer = 101;
	std::cout << startButton1->GetPosition().x << startButton1->GetPosition().y << std::endl;
	//
	startButton->OnEnter = [startButton1]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonOn.png");
		startButton1->SetTexture(*tex, { 4,4,27,11 },{0,0,33,18});
		startButton1->SetSize({ 66 * 2,36 * 2 });
		//startButton1->SetPosition(startButton->GetPosition());
		startButton1->SetPosition(400,810);
		std::cout << startButton1->GetPosition().x << startButton1->GetPosition().y << std::endl;
		
		std::cout << "Enter" << std::endl;
	};

	
	
	startButton->OnExit = [startButton1]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/Button.png");
		startButton1->SetTexture(*tex, { 4,4,27,11 }, { 0,0,33,18 });
		startButton1->SetSize({ 66 * 2,36 * 2 });
		startButton1->SetPosition(400, 810);
		std::cout << startButton1->GetPosition().x << startButton1->GetPosition().y << std::endl;
		std::cout << "Exit" << std::endl;
	};
	startButton->OnClick = [startButton1]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonDown.png");
		startButton1->SetTexture(*tex, { 4,4,27,11 }, { 0,0,33,18 });
		startButton1->SetSize({ 66 * 2,36 * 2 });
		startButton1->SetPosition(400, 810);
		std::cout << startButton1->GetPosition().x << startButton1->GetPosition().y << std::endl;
		std::cout << "Click" << std::endl;
	};
	settingButton->SetOrigin(Origins::TC);
	settingButton->sortLayer = 100;
	settingButton->SetPosition(windowSize.x*0.5f, windowSize.y * 0.9f);
	settingButton->sprite.setScale(7.5f, 2.5f);
	settingButton->OnEnter = [settingButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonOn.png");
		settingButton->sprite.setTexture(*tex);
		std::cout << "Enter" << std::endl;
	};
	settingButton->OnExit = [settingButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture(settingButton->textureId);
		settingButton->sprite.setTexture(*tex);
		std::cout << "Exit" << std::endl;
	};
	settingButton->OnClick = [settingButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonDown.png");
		settingButton->sprite.setTexture(*tex);
		std::cout << "Click" << std::endl;
	};
	exitButton->SetOrigin(Origins::TC);
	exitButton->sortLayer = 100;
	exitButton->SetPosition(windowSize.x * 0.75f, windowSize.y * 0.9f);
	exitButton->sprite.setScale(7.5f, 2.5f);
	exitButton->OnEnter = [exitButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonOn.png");
		exitButton->sprite.setTexture(*tex);
		std::cout << "Enter" << std::endl;
	};
	exitButton->OnExit = [exitButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture(exitButton->textureId);
		exitButton->sprite.setTexture(*tex);
		std::cout << "Exit" << std::endl;
	};
	exitButton->OnClick = [exitButton]() {
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Title/ButtonDown.png");
		exitButton->sprite.setTexture(*tex);
		std::cout << "Click" << std::endl;
	};
}
