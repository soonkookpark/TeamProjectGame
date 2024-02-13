#pragma once
#include "VertexArrayGo.h"

class TileMap;
class Astar;

struct Tree
{
	sf::IntRect rect;
	VertexArrayGo rectangle;

	int level = 0;

	bool isActive = true;
	static bool entrance;
	static bool starting;

	Tree* parent;
	Tree* child_L;
	Tree* child_R;
	
	Tree(sf::IntRect rect = {0, 0, 0, 0});
	~Tree();

	void Divide(TileMap* tileMapPtr);
	void Divide(TileMap* tileMapPtr, int level);
	void ConnectRoom(TileMap* tileMapPtr);

	bool Room(TileMap* tileMapPtr, Astar* finder);
	bool SettingRoom(TileMap* tileMapPtr, std::vector<Tree*>& room, Astar* finder);
	void Debug();
	void Draw(sf::RenderWindow& window);
	void SummonMonster(sf::Vector2f start, TileMap* tileMap);

	sf::Vector2i GetCenter();
};