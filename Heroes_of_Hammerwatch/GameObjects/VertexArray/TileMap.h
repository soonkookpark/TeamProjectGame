#pragma once
#include "VertexArrayGo.h"
#include <unordered_map>
#include "rapidcsv.h"

class Tree;
class OnTileMap;
class Astar;

class TileMap : public VertexArrayGo
{
protected:
	bool checkLoad = false;
	OnTileMap* onTileMap;

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

	Tree* route;
	Astar* finder;

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	virtual void Draw(sf::RenderWindow& window) override;

	bool LoadDrawTexture(const std::string& filePath);
	bool DrawTexture(int row, int col);
	bool ChangeTile(int tilePosX, int tilePosy, int idx);

	bool LoadInfo(const std::string& filePath);
	
	void SaveTexture(const std::string& filePath);
	void LoadTexture(const std::string& filePath);

	void LoadDataArray(rapidcsv::Document& map);
	void ResetDataArray();

	sf::IntRect GetTileBound(int index);
	std::vector<std::vector<int>> GetTileArray() { return tileArray; }
	int FindTileInfo(sf::Vector2f pos);
	int FindTileInfo(float x, float y) { return FindTileInfo({ x,y }); }

	std::vector<Tile> tiles;
	std::unordered_map<int, TileInfo> tileInfo;

	sf::Vector2f TileSize();
	sf::Vector2i TileIntSize();
	sf::Vector2f TilePixelSize();
	Tile& GetTile(int x, int y);

	void SetOnTileMap(OnTileMap* onTileMap) { this->onTileMap = onTileMap; }
	void Divide();
	void ConnectRoom();
	bool SelectDoor();
	void CreateDoor(sf::Vector2i start, sf::Vector2i ent);
	void Debug();
	int ReturnTile(int x, int y) { return tileArray[y][x]; }
	sf::Vector2f GetFloatPosition(sf::Vector2i intPos);

	Astar* GetAstar();
	void Summon();
};

