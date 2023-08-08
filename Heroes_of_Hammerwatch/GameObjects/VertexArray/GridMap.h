#pragma once
#include "VertexArrayGo.h"

class TileMap;

class GridMap : public VertexArrayGo
{
protected:
	sf::Vector2i size;

public:
	GridMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~GridMap() override;

	bool DrawGrid(TileMap* tileMap);

	sf::Vector2f TileSize();
	float TileXSize();
};

