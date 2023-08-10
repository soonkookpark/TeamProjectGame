#pragma once
#include "VertexArrayGo.h"
#include <unordered_map>
#include "rapidcsv.h"

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

class TileMap : public VertexArrayGo
{
protected:
	bool checkLoad = false;

	sf::Vector2f tileSize = { 16.f, 16.f };
	sf::Vector2f texSize = { 32.f, 32.f };
	sf::Vector2i size;

	sf::Vector2f offsets[4]
	{
		{ 0.f, 0.f },
		{ tileSize.x, 0.f },
		{ tileSize.x, tileSize.y },
		{ 0, tileSize.y }
	};

	//std::vector<sf::Vector2f[4]> tileOffset;
	std::vector<std::vector<sf::Vector2f>> tileOffset;

	std::vector<TileInfo> tileInfoArray;
	std::vector<std::vector<int>> tileArray;

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool LoadDrawTexture(const std::string& filePath);
	bool DrawTexture(int row, int col);
	bool ChangeTile(int tilePosX, int tilePosy, int idx);

	bool LoadInfo(const std::string& filePath);

	void LoadTileInfo(const std::string& filePath);
	
	void SaveTexture(const std::string& filePath);
	void LoadTexture(const std::string& filePath);

	void LoadDataArray(rapidcsv::Document& map);
	void ResetDataArray();

	sf::IntRect GetTileBound(int index);

	std::vector<Tile> tiles;
	std::unordered_map<int, TileInfo> tileInfo;

	sf::Vector2f TileSize();
	sf::Vector2i TileIntSize();
	sf::Vector2f TilePixelSize();
	Tile& GetTile(int x, int y);
};

