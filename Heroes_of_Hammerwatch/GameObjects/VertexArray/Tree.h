#pragma once

class TileMap;

struct Tree
{
	sf::IntRect rect;
	int level = 0;
	sf::RectangleShape room;

	bool isActive = true;
	static bool entrance;
	static bool starting;

	Tree* parent;
	Tree* child_L;
	Tree* child_R;

	Tree(sf::IntRect rect = {0, 0, 0, 0});
	~Tree();

	void Divide(TileMap* tileMapPtr);
	void ConnectRoom(TileMap* tileMapPtr);
	void SettinRoom();

	sf::Vector2i GetCenter();
};