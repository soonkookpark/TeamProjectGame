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
	sf::Vector2f tileSize = { 16.f, 16.f };
	sf::Vector2f texSize = { 32.f, 32.f };
	sf::Vector2i size;

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool DrawTexture(const std::string& filePath);
	bool DrawTexture(int row, int col);
	bool ChangeTile(int tilePosX, int tilePosy, sf::IntRect rect);

	bool LoadInfo(const std::string& filePath);

	void LoadTileInfo(const std::string& filePath);

	std::vector<Tile> tiles;
	std::unordered_map<std::string, TileInfo> tileInfo;

	sf::Vector2f TileSize();
	sf::Vector2i TileIntSize();
	sf::Vector2f TilePixelSize();
	Tile& GetTile(int x, int y);
};

