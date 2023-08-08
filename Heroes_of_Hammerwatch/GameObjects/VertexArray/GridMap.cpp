#include "stdafx.h"
#include "GridMap.h"
#include "TileMap.h"

GridMap::GridMap(const std::string& textureId, const std::string& n)
{
	sortLayer = SortLayer::TILE;
}

GridMap::~GridMap()
{
}

bool GridMap::DrawGrid(TileMap* tileMap)
{
	size = tileMap->TileIntSize();
	float tileSizeX = tileMap->TilePixelSize().x;
	float tileSizeY = tileMap->TilePixelSize().y;

	vertexArray.setPrimitiveType(sf::Lines);
	vertexArray.resize((size.x + size.y + 2) * 2);

	int count = 0;
	for (int i = 0; i < size.y + 1; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertexArray[i * 2 + k].position = { k * tileSizeX * size.x, i * tileSizeY };
			vertexArray[i * 2 + k].color = sf::Color::Red;
			count++;
		}
	}

	for (int j = 0; j < size.x + 1; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertexArray[count + j * 2 + k].position = { j * tileSizeX, k * tileSizeY * size.y };
			vertexArray[count + j * 2 + k].color = sf::Color::Red;
		}
	}

	return true;
}

sf::Vector2f GridMap::TileSize()
{
	return sf::Vector2f();
}

float GridMap::TileXSize()
{
	return 0.0f;
}