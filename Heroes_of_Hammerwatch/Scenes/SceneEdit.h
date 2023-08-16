#pragma once
#include "Scene.h"

class UIButton;
class TextGo;
class TileMap;
class GridMap;
class OnTileMap;
class RectangleGo;

struct TileOnMouse
{
	RectangleGo* tile;
	int tileIndex;
};

class SceneEdit : public Scene
{
protected:
	sf::Vector2f windowSize;
	UIButton* colUp;
	UIButton* colDown;
	UIButton* colUpUp;
	UIButton* colDownDown;
	UIButton* rowUp;
	UIButton* rowDown;
	UIButton* rowUpUp;
	UIButton* rowDownDown;
	UIButton* edit;
	UIButton* save;
	UIButton* load;

	UIButton* tileSelector[10];
	UIButton* uiBackground;

	TextGo* colNum;
	TextGo* rowNum;

	TileMap* tileMap = nullptr;
	GridMap* gridMap = nullptr;
	OnTileMap* onTileMap = nullptr;

	TileOnMouse tileOnMouse;


	int col = 1;
	int row = 1;
	int tileSize = 32;
	bool changeTile = true;

public:
	SceneEdit();
	virtual ~SceneEdit() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetTileSelector(const std::string& filePath, int idx);
	
	const std::string GetLoadPathWithWindow();
	const std::wstring GetSavePathWithWindow();
};
