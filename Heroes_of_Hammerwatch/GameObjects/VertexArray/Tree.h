#pragma once

class TileMap;

struct Tree
{
	sf::IntRect rect;
	int level = 0;
	sf::RectangleShape room;

	Tree* parent;
	Tree* child_L;
	Tree* child_R;

	Tree(sf::FloatRect rect = {}) : parent(nullptr), child_L(nullptr), child_R(nullptr), rect(rect) {}
	~Tree();

	void Divide(TileMap* tileMapPtr);
	void ConnectRoom(TileMap* tileMapPtr);
	void DrawRoom(sf::RenderWindow& window);

	sf::Vector2i GetCenter();
};