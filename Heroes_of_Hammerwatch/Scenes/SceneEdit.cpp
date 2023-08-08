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
	worldView.zoom(zoom);
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

		tileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
		tileMap->DrawTexture(col, row);

		gridMap = (GridMap*)AddGo(new GridMap());
		gridMap->DrawGrid(tileMap);
	};
	
	zoom = 1.f;
	row = 1;
	col = 1;

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
		zoom -= 0.01f;
		if (zoom <= 0.1f) zoom = 0.1f;
		worldView.zoom(zoom);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		zoom += 0.01f;
		if (zoom >= 2.0f) zoom = 2.f;
		worldView.zoom(zoom);
	}
}

void SceneEdit::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}