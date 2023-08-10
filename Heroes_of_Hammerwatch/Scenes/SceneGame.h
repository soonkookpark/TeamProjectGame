#pragma once
#include "Scene.h"

class Player;
class Paladin;
class TileMap;
class GridMap;
class UIButton;

class Monster;
class SceneGame : public Scene
{
protected:
	sf::FloatRect groundBounds;
	Player* player;
	TileMap* tileMap = nullptr;
	GridMap* gridMap = nullptr;

	Monster* monster = nullptr;
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

