#pragma once

struct Tree
{
	sf::FloatRect rect;
	sf::Vector2f center;
	int level = 0;

	Tree* parent;
	Tree* child_L;
	Tree* child_R;

	Tree() : parent(nullptr), child_L(nullptr), child_R(nullptr) {}
	~Tree();

	sf::Vector2f Divide(sf::FloatRect rect);
};

