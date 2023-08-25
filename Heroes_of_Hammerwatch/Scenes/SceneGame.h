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
	sf::Vector2i mapSize = { 120, 120 };

	std::list<Monster*> SummonedMonster;
	std::list<Monster*> mobsToRemove;

	bool checkClear = false;
	bool setting = false;
	int stage = 0;


public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;		

	void SettingStage();
	void Summon(Monster* monster);

	void DieMonster(Monster* mob);
	void CheckClearStage();
};
