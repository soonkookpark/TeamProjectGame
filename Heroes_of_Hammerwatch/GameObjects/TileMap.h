#pragma once
#include "VertexArrayGo.h"
#include <unordered_map>

struct TileInfo
{
	std::string texture_ID;
	sf::FloatRect bound;
	std::string name;
};

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

class TileMap : public VertexArrayGo
{
protected:
	//sf::VertexArray vertexArray;
	sf::Vector2f tileSize = { 32.f, 32.f };
	sf::Vector2f texSize = { 32.f, 32.f };
public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);
	bool LoadInfo(const std::string& filePath);

	std::vector<Tile> tiles;
	std::unordered_map<std::string, TileInfo> tileInfo;

	sf::Vector2f TileSize();
	float TileXSize();
	Tile& GetTile(int x, int y);
};

