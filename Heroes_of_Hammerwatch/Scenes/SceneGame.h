#pragma once
#include "Scene.h"
#include "Creature.h"


class Player;
class Paladin;
class TileMap;
class GridMap;
class UIButton;
class Astar;
class OnTileMap;

class Monster;
class SceneGame : public Scene
{
protected:
	sf::FloatRect groundBounds;
	Player* player;
	TileMap* tileMap = nullptr;
	GridMap* gridMap = nullptr;
	Astar* finder = nullptr;

	UIButton* startBT;
	OnTileMap* onTileMap = nullptr;
	sf::Vector2i mapSize = { 90, 90 };

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
