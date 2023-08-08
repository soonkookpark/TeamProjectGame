#pragma once
#include "Scene.h"

class UIButton;
class TextGo;
class TileMap;
class GridMap;

class SceneEdit : public Scene
{
protected:
	sf::Vector2f windowSize;
	UIButton* colUp;
	UIButton* colDown;
	UIButton* rowUp;
	UIButton* rowDown;
	UIButton* edit;

	TextGo* colNum;
	TextGo* rowNum;

	TileMap* tileMap = nullptr;
	GridMap* gridMap = nullptr;

	int zoom = 1.f;

	int col = 1;
	int row = 1;

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
