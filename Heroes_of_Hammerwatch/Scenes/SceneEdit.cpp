#include "stdafx.h"
#include "SceneEdit.h"
#include "GameObject.h"
#include "TextGo.h"
#include "UIButton.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "Framework.h"
#include "TileMap.h"
#include "GridMap.h"
#include "RectangleGo.h"

/*
Down 아이콘 214, 0, 9, 11
Up 아이콘 223, 0, 9, 11
Save 아이콘 205, 27, 11, 12
Load 아이콘 78, 91, 12, 11

graphics/miscellaneous/icons.png

*/

SceneEdit::SceneEdit() : Scene(SceneId::Title)
{
	resourceListPath = "scripts/SceneEditResourceList.csv";
}

void SceneEdit::Init()
{
	Release();
	windowSize = FRAMEWORK.GetWindowSize();

	rowUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	rowDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	edit = (UIButton*)AddGo(new UIButton("graphics/button/button_edit.png"));
	rowNum = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf"));
	colNum = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf"));

	for (int i = 0; i < sizeof(tileSelector) / sizeof(UIButton*); i++)
	{
		tileSelector[i] = (UIButton*)AddGo(new UIButton("graphics/mine/mine_tile.png"));
		tileSelector[i]->sprite.setTextureRect({ tileSize * (i % 4), tileSize * (i / 4), tileSize, tileSize });
		tileSelector[i]->sprite.setScale(2.0, 2.0);
		tileSelector[i]->SetPosition(20 + 120.f * (i % 2), 400 + 100.f * (i / 2));
		tileSelector[i]->OnClick = [this, i]() {
			this->tileOnMouse->rectangle.setTexture(RESOURCE_MGR.GetTexture("graphics/mine/mine_tile.png"));
			this->tileOnMouse->rectangle.setTextureRect({ tileSize * (i % 4), tileSize * (i / 4), tileSize, tileSize });
			this->tileOnMouse->rectangle.setFillColor(sf::Color::Color(255, 255, 255, 255));
		};
	}

	uiBackground = (UIButton*)AddGo(new UIButton("graphics/button/UIBG.png"));
	uiBackground->sprite.setColor(sf::Color::Color(255, 255, 255, 100));
	uiBackground->sprite.setTextureRect({ 0, 0, 300, (int)windowSize.y });
	uiBackground->sortOrder = -1;
	uiBackground->OnEnter = [this]() {
		this->tileOnMouse->SetActive(false);
	};
	uiBackground->OnExit = [this]() {
		this->tileOnMouse->SetActive(true);
	};

	sf::Vector2f size = { 16.f , 16.f };
	tileOnMouse = (RectangleGo*)AddGo(new RectangleGo(size));
	tileOnMouse->rectangle.setFillColor(sf::Color::Color(255, 255, 255, 100));
	tileOnMouse->SetOrigin(Origins::MC);
	tileOnMouse->sortLayer = SortLayer::TILE + 1;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneEdit::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneEdit::Enter()
{
	RESOURCE_MGR.LoadFromCsv(resourceListPath, false);

	auto size = FRAMEWORK.GetWindowSize();

	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	worldView.zoom(0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	rowUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	rowUp->sprite.setScale(3.0, 3.0);
	rowUp->OnClick = [this]()
	{
		this->row++;
		rowNum->text.setString("Row : " + std::to_string(row));
	};
	
	rowDown->sprite.setTextureRect({214, 0, 9, 11});
	rowDown->sprite.setScale(3.0, 3.0);
	rowDown->OnClick = [this]()
	{
		this->row--;
		if (row <= 0) this->row = 1;
		rowNum->text.setString("Row : " + std::to_string(row));
	};
	
	colUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	colUp->sprite.setScale(3.0, 3.0);
	colUp->OnClick = [this]()
	{
		this->col++;
		colNum->text.setString("Col : " + std::to_string(col));
	};
	
	colDown->sprite.setTextureRect({ 214, 0, 9, 11 });
	colDown->sprite.setScale(3.0, 3.0);
	colDown->OnClick = [this]()
	{
		this->col--;
		if (col <= 1) this->col = 1;
		colNum->text.setString("Col : " + std::to_string(col));
	};
	
	rowNum->sortLayer = SortLayer::UI;
	rowNum->text.setString("Row : " + std::to_string(row));
	rowNum->SetPosition(50.f, 50.f);
	rowUp->SetPosition(190.f, 20.f);
	rowDown->SetPosition(190.f, 80.f);

	colNum->sortLayer = SortLayer::UI;
	colNum->text.setString("Col : " + std::to_string(row));
	colNum->SetPosition(50.f, 170.f);
	colUp->SetPosition(190.f, 140.f);
	colDown->SetPosition(190.f, 200.f);

	edit->sortLayer = SortLayer::UI;
	edit->SetPosition(120.f, 270.f);
	edit->OnClick = [this]()
	{
		TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
		tempTileMap->DrawTexture(col, row);

		GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
		tempGridMap->DrawGrid(col, row, 16);


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

		tileMap = tempTileMap;
		gridMap = tempGridMap;
	};
	
	row = 1;
	col = 1;

	rowNum->text.setString("Row : " + std::to_string(row));
	colNum->text.setString("Col : " + std::to_string(col));

	Scene::Enter();
}

void SceneEdit::Exit()
{
	RemoveGo(tileMap);
	RemoveGo(gridMap);

	if (tileMap != nullptr)
	{
		delete tileMap;
		tileMap = nullptr;
	}
	if (gridMap != nullptr)
	{
		delete gridMap;
		gridMap = nullptr;
	}

	Scene::Exit();
}

void SceneEdit::Update(float dt)
{
	Scene::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f worldPos = ScreenToWorldPos(mousePos);
	sf::Vector2i tileIndex = { (int)worldPos.x / 16, (int)worldPos.y / 16 };
	tileIndex.x = worldPos.x > 0 ? (int)worldPos.x / 16 : (int)worldPos.x / 16 - 1;
	tileIndex.y = worldPos.y > 0 ? (int)worldPos.y / 16 : (int)worldPos.y / 16 - 1;
	sf::Vector2i tileSnap = { tileIndex.x * 16 + 8 , tileIndex.y * 16 + 8 };

	tileOnMouse->SetPosition((sf::Vector2f)tileSnap);

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		sf::IntRect rect = tileOnMouse->rectangle.getTextureRect();
		tileMap->ChangeTile(tileIndex.x, tileIndex.y, rect);
	}
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
	{

	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
	
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

	


}

void SceneEdit::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}