#pragma once
#include "Scene.h"

class UIButton;
class TextGo;
class TileMap;
class GridMap;
class RectangleGo;

class SceneEdit : public Scene
{
protected:
	sf::Vector2f windowSize;
	UIButton* colUp;
	UIButton* colDown;
	UIButton* rowUp;
	UIButton* rowDown;
	UIButton* edit;

	UIButton* tileSelector[6];
	UIButton* uiBackground;

	TextGo* colNum;
	TextGo* rowNum;

	TileMap* tileMap = nullptr;
	GridMap* gridMap = nullptr;

	RectangleGo* tileOnMouse;

	int col = 1;
	int row = 1;
	int tileSize = 32;

public:
	SceneEdit();
	virtual ~SceneEdit() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};
