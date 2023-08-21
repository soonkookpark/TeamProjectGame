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
#include "OnTileMap.h"
#include "RectangleGo.h"
#include <string>

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
	/*{
		std::string abc = GetLoadPathWithWindow();
		std::cout << abc << std::endl;
	}*/

	Release();
	windowSize = FRAMEWORK.GetWindowSize();

	rowUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	rowUpUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	rowDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	rowDownDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colUpUp = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	colDownDown = (UIButton*)AddGo(new UIButton("graphics/miscellaneous/icons.png"));
	edit = (UIButton*)AddGo(new UIButton("graphics/button/button_edit.png"));
	save = (UIButton*)AddGo(new UIButton("graphics/button/button_save.png"));
	load = (UIButton*)AddGo(new UIButton("graphics/button/button_load.png"));
	rowNum = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf"));
	colNum = (TextGo*)AddGo(new TextGo("fonts/arialuni.ttf"));
	
	//Tile 초기화
	SetTileSelector("graphics/mine/mine_tile.csv", sizeof(tileSelector) / sizeof(UIButton*));

	uiBackground = (UIButton*)AddGo(new UIButton("graphics/button/UIBG.png"));
	uiBackground->sprite.setColor(sf::Color::Color(255, 255, 255, 100));
	uiBackground->sprite.setTextureRect({ 0, 0, 300, (int)windowSize.y });
	uiBackground->sortOrder = -1;
	uiBackground->OnEnter = [this]() {
		this->tileOnMouse.tile->SetActive(false);
		changeTile = false;
	};
	uiBackground->OnExit = [this]() {
		this->tileOnMouse.tile->SetActive(true);
		changeTile = true;
	};

	sf::Vector2f size = { 16.f , 16.f };
	tileOnMouse.tile = (RectangleGo*)AddGo(new RectangleGo(size));
	tileOnMouse.tile->rectangle.setFillColor(sf::Color::Color(255, 255, 255, 100));
	tileOnMouse.tile->SetOrigin(Origins::MC);
	tileOnMouse.tile->sortLayer = SortLayer::TILE + 1;


	//초기화
	rowUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	rowUp->sprite.setScale(3.0, 3.0);
	rowUp->OnClick = [this]()
	{
		this->row++;
		rowNum->text.setString("Row : " + std::to_string(row));
	};
	rowUpUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	rowUpUp->sprite.setScale(3.0, 3.0);
	rowUpUp->OnClick = [this]()
	{
		this->row += 10;
		rowNum->text.setString("Row : " + std::to_string(row));
	};

	rowDown->sprite.setTextureRect({ 214, 0, 9, 11 });
	rowDown->sprite.setScale(3.0, 3.0);
	rowDown->OnClick = [this]()
	{
		this->row--;
		if (row <= 0) this->row = 1;
		rowNum->text.setString("Row : " + std::to_string(row));
	};
	rowDownDown->sprite.setTextureRect({ 214, 0, 9, 11 });
	rowDownDown->sprite.setScale(3.0, 3.0);
	rowDownDown->OnClick = [this]()
	{
		this->row -= 10;
		if (row <= 0) this->row = 1;
		rowNum->text.setString("Row : " + std::to_string(row));
	};

	colUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	colUp->sprite.setScale(3.0, 3.0);
	colUp->OnClick = [this]()
	{
		this->col += 10;
		colNum->text.setString("Col : " + std::to_string(col));
	};
	colUpUp->sprite.setTextureRect({ 223, 0, 9, 11 });
	colUpUp->sprite.setScale(3.0, 3.0);
	colUpUp->OnClick = [this]()
	{
		this->col += 10;
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
	colDownDown->sprite.setTextureRect({ 214, 0, 9, 11 });
	colDownDown->sprite.setScale(3.0, 3.0);
	colDownDown->OnClick = [this]()
	{
		this->col -= 10;
		if (col <= 1) this->col = 1;
		colNum->text.setString("Col : " + std::to_string(col));
	};

	rowNum->sortLayer = SortLayer::UI;
	rowNum->text.setString("Row : " + std::to_string(row));
	rowNum->SetPosition(50.f, 50.f);
	rowUp->SetPosition(190.f, 20.f);
	rowUpUp->SetPosition(230.f, 20.f);
	rowDown->SetPosition(190.f, 80.f);
	rowDownDown->SetPosition(230.f, 80.f);

	colNum->sortLayer = SortLayer::UI;
	colNum->text.setString("Col : " + std::to_string(col));
	colNum->SetPosition(50.f, 170.f);
	colUp->SetPosition(190.f, 140.f);
	colDown->SetPosition(190.f, 200.f);
	colUpUp->SetPosition(230.f, 140.f);
	colDownDown->SetPosition(230.f, 200.f);

	edit->sortLayer = SortLayer::UI;
	edit->SetPosition(30.f, 270.f);
	edit->OnClick = [this]()
	{
		TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
		tempTileMap->DrawTexture(col, row);

		GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
		tempGridMap->DrawGrid(col, row, 16);

		OnTileMap* tempOnTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));
		tempOnTileMap->LoadDrawOnTile(tempTileMap);


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
		if (onTileMap != nullptr)
		{
			RemoveGo(onTileMap);
			delete onTileMap;
			onTileMap = nullptr;
		}


		tileMap = tempTileMap;
		gridMap = tempGridMap;
		onTileMap = tempOnTileMap;

		tileMap->SetOnTileMap(onTileMap);
	};

	save->sortLayer = SortLayer::UI;
	save->SetPosition(windowSize.x - 240, 20);
	save->OnClick = [this]()
	{
		//std::string path = Utils::WstringToString(GetSavePathWithWindow());
		tileMap->SaveTexture("save/new.csv");
	};

	load->sortLayer = SortLayer::UI;
	load->SetPosition(windowSize.x - 120, 20);
	load->OnClick = [this]()
	{

		TileMap* tempTileMap = (TileMap*)AddGo(new TileMap("graphics/mine/mine_tile.png"));
		tempTileMap->LoadDrawTexture("save/new.csv");

		GridMap* tempGridMap = (GridMap*)AddGo(new GridMap());
		tempGridMap->DrawGrid(tempTileMap);

		OnTileMap* tempOnTileMap = (OnTileMap*)AddGo(new OnTileMap("graphics/mine/mine_wall.png"));
		tempOnTileMap->LoadDrawOnTile(tempTileMap);

		col = tempTileMap->TileIntSize().y;
		colNum->text.setString("Col : " + std::to_string(col));

		row = tempTileMap->TileIntSize().x;
		rowNum->text.setString("Row : " + std::to_string(row));

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
		if (onTileMap != nullptr)
		{
			RemoveGo(onTileMap);
			delete onTileMap;
			onTileMap = nullptr;
		}

		tileMap = tempTileMap;
		gridMap = tempGridMap;
		onTileMap = tempOnTileMap;
		tileMap->SetOnTileMap(onTileMap);
	};

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
	RemoveGo(onTileMap);

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
	if (onTileMap != nullptr)
	{
		delete onTileMap;
		onTileMap = nullptr;
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

	tileOnMouse.tile->SetPosition((sf::Vector2f)tileSnap);

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && changeTile)
	{
		int idx = tileOnMouse.tileIndex;
		tileMap->ChangeTile(tileIndex.x, tileIndex.y, idx);
	}
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
	{

	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
	
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y - 0.5);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.setCenter(worldView.getCenter().x - 0.5, worldView.getCenter().y);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.setCenter(worldView.getCenter().x, worldView.getCenter().y + 0.5);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
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
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		tileMap->SetActive(!tileMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		gridMap->SetActive(!gridMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F3))
	{
		onTileMap->SetActive(!onTileMap->GetActive());
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F4))
	{
		tileMap->Divide();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F5))
	{
		tileMap->ConnectRoom();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F6))
	{
		for (int i = 0; i < 6; i++)
		{
			tileMap->Divide();
		}
		tileMap->ConnectRoom();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F7))
	{
		tileMap->SelectDoor();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F8))	
	{
		tileMap->Debug();
	}
}

void SceneEdit::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

const std::string SceneEdit::GetLoadPathWithWindow()
{
	OPENFILENAME OFN;
	TCHAR filePathName[100] = L"";
	TCHAR lpstrFile[100] = L"";
	static TCHAR filter[] = L"모든 파일\0*.*\0텍스트 파일\0*.txt\0csv 파일\0*.csv";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = FRAMEWORK.GetHWnd();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";

	if (GetOpenFileName(&OFN) != 0) {
		wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
		MessageBox(FRAMEWORK.GetHWnd() , filePathName, L"열기 선택", MB_OK);

		std::string t = Utils::WstringToString(OFN.lpstrFile);
		
		int a = 0;
		return t;
	}
	return "";


	//OPENFILENAME OFN;
	//TCHAR filePathName[100] = L"";
	//TCHAR lpstrFile[100] = L"";
	////static TCHAR filter[] = L"모든 파일\0*.*\0JSON 파일\0*.json";
	//static TCHAR filter[] = L"CSV 파일\0*.csv";

	//memset(&OFN, 0, sizeof(OPENFILENAME));
	//OFN.lStructSize = sizeof(OPENFILENAME);
	//OFN.hwndOwner = FRAMEWORK.GetHWnd();
	//OFN.lpstrFilter = filter;
	//OFN.lpstrFile = lpstrFile;
	//OFN.nMaxFile = 100;
	//OFN.lpstrInitialDir = L".";

	//if (GetOpenFileName(&OFN) != 0)
	//{
	//	//wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
	//	//MessageBox(FRAMEWORK.GetHWnd(), filePathName, L"열기 선택", MB_OK);
	//	
	//	return OFN.lpstrFile;
	//}

	//return L"";
}

const std::wstring SceneEdit::GetSavePathWithWindow()
{
	OPENFILENAME OFN;
	TCHAR filePathName[100] = L"";
	TCHAR lpstrFile[100] = L"";
	//static TCHAR filter[] = L"모든 파일\0*.*\0JSON 파일\0*.json";
	static TCHAR filter[] = L"CSV 파일\0 * .csv";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = FRAMEWORK.GetHWnd();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";
	OFN.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&OFN) != 0)
	{
		//wsprintf(filePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
		//MessageBox(FRAMEWORK.GetHWnd(), filePathName, L"열기 선택", MB_OK); 

		std::wstring path = OFN.lpstrFile;
		if (!Utils::Contains(path, '.'))
		{
			path += L".csv";
		}
		return path;
	}

	return L"";
}

void SceneEdit::SetTileSelector(const std::string& filePath, int idx)
{
	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	sf::Vector2i size = { (int)doc.GetColumnCount(), (int)doc.GetRowCount() };

	for (int col = 0; col < idx; ++col)
	{
		TileInfo tile;
		for (int row = 0; row < size.x - 1; ++row)
		{
			//std::cout << col << ", " << row << std::endl;
			switch (row)
			{
			case 0:
				tile.texture_ID = doc.GetCell<std::string>(row, col);
				break;
			case 1:
				tile.bound.left = doc.GetCell<int>(row, col);
				break;
			case 2:
				tile.bound.top = doc.GetCell<int>(row, col);
				break;
			case 3:
				tile.bound.width = doc.GetCell<int>(row, col);
				break;
			case 4:
				tile.bound.height = doc.GetCell<int>(row, col);
				break;
			case 5:
				tile.name = doc.GetCell<std::string>(row, col);
				break;
			case 6:
				tile.index = doc.GetCell<int>(row, col);
			default:
				std::cout << col << ", " << row << std::endl;
				break;
			}
		}
		
		tileSelector[col] = (UIButton*)AddGo(new UIButton("graphics/mine/mine_tile.png"));
		tileSelector[col]->sprite.setTextureRect((sf::IntRect)tile.bound);
		tileSelector[col]->sprite.setScale(2.0, 2.0);
		tileSelector[col]->SetPosition(20 + 18 * (col % 2)*4, 450 + 18 * (col / 2)*4);
		tileSelector[col]->OnClick = [this, col]() {
			this->tileOnMouse.tile->rectangle.setTexture(RESOURCE_MGR.GetTexture("graphics/mine/mine_tile.png"));
			this->tileOnMouse.tile->rectangle.setTextureRect(tileSelector[col]->GetTextureRect());
			this->tileOnMouse.tile->rectangle.setFillColor(sf::Color::Color(255, 255, 255, 255));
			this->tileOnMouse.tileIndex = col;
		};
	}
}
