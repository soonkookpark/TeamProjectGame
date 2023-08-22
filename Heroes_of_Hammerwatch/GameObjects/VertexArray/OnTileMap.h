#pragma once
#include "VertexArrayGo.h"
#include <unordered_map>
#include "rapidcsv.h"

enum Wall
{
	None = 0,
	ITEM = 1,
	Wood_L,
	Wood_R,
	Wall_R,
	Wall_L,
	Wall_RB,
	Wall_LB,
	Wall_RT,
	Wall_LT,
	Wood_T,
	Wood_B,
	Wall_B,
	Wall_T,
	Wall_LRB,
	Wall_TB,
	Wall_LRTB,
	Wall_RTB,
	Wall_LTB,
	Wall_LRT,
	Wall_LR,
	Wall_None,
};

class TileMap;

class OnTileMap : public VertexArrayGo
{
protected:
	bool checkLoad = false;

	sf::Sprite ent;
	sf::Sprite start;

	sf::Vector2f tileSize = { 16.f, 16.f };
	sf::Vector2f texSize = { 16.f, 16.f };
	sf::Vector2i size;

	sf::Vector2f offsets[4]
	{
		{ 0.f, 0.f },
		{ tileSize.x, 0.f },
		{ tileSize.x, tileSize.y },
		{ 0, tileSize.y }
	};

	sf::Vector2f offsetsLong[4]
	{
		{ 0.f, 16.f },
		{ 16.f, 16.f },
		{ 16.f, -32.f },
		{ 0, -32.f }
	};

	std::vector<std::vector<sf::Vector2f>> tileOffset;

	std::vector<TileInfo> tileInfoArray;
	std::vector<std::vector<int>> tileArray;
	std::vector<std::vector<int>> wallArray;

public:
	OnTileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~OnTileMap() override;

	virtual void Draw(sf::RenderWindow& window) override;

	bool LoadDrawOnTile(TileMap* tileMap);

	bool DrawTexture(int row, int col);
	bool ChangeTile(int tilePosX, int tilePosY, int idx);
	void ChangeDoor(sf::Vector2i ent, sf::Vector2i start, TileMap* tileMap);

	bool LoadInfo(const std::string& filePath);
	//void SaveTexture(const std::string& filePath);
	//void LoadTexture(const std::string& filePath);

	void LoadTileDataArray(rapidcsv::Document& map);

	Wall CheckAdjacent(int i, int j);
	bool CheckWall(int x, int y);
	Wall SelectWall(bool left, bool right, bool top, bool down);

	std::vector<Tile> tiles;
	std::unordered_map<int, TileInfo> tileInfo;

	void SetEntrance();
	std::vector<std::vector<int>> GetTileArray() { return tileArray; }

	sf::Vector2f GetStartPos() { return start.getPosition(); }
};