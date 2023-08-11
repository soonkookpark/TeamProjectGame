#include "stdafx.h"
#include "OnTileMap.h"
#include "ResourceMgr.h"
#include "TileMap.h"

OnTileMap::OnTileMap(const std::string& textureId, const std::string& n)
	: VertexArrayGo(textureId, n)
{
	sortLayer = SortLayer::TILE;
}

OnTileMap::~OnTileMap()
{
}

bool OnTileMap::LoadDrawOnTile(TileMap* tileMap)
{
    texture = RESOURCE_MGR.GetTexture(textureId);

    size = tileMap->TileIntSize();
    float tileSizeX = tileMap->TilePixelSize().x;
    float tileSizeY = tileMap->TilePixelSize().y;

    //LoadTileDataArray(map);
    tileArray.resize(size.y, std::vector<int>(size.x));
    tileArray = tileMap->GetTileArray();


    LoadInfo("graphics/mine/on_mine_tile.csv");

    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            int tileIndex = size.x * i + j;
            int texIndex = tileArray[i][j];
            for (int k = 0; k < 4; k++)
            {
                int vertexIndex = tileIndex * 4 + k;
                //vertexArray[vertexIndex].position = currPos + offsets[k];
                if (texIndex == Wall::None)
                {
                    vertexArray[vertexIndex].position = currPos + offsets[k];
                    vertexArray[vertexIndex].texCoords = tileOffset[Wall::None][k];
                }
                else
                {
                    vertexArray[vertexIndex].position = currPos + offsetsLong[k];
                    vertexArray[vertexIndex].texCoords = tileOffset[Wall::Wood_L][k];
                }
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

    return true;
}

bool OnTileMap::DrawTexture(int row, int col)
{
	return false;
}

bool OnTileMap::ChangeTile(int tilePosX, int tilePosY, int idx)
{
    if (tilePosX < 0 || tilePosY < 0) return false;
    if (tilePosX >= size.x || tilePosY >= size.y) return false;

    if (idx == 0) {
        idx = 2;
    }

    sf::FloatRect rect = tileInfoArray[idx].bound;

    sf::Vector2f texOffsets[4] =
    {
        { rect.left, rect.top },
        { rect.left + rect.width, rect.top },
        { rect.left + rect.width, rect.top + rect.height },
        { rect.left, rect.top + rect.height }
    };

    tileArray[tilePosY][tilePosX] = idx;

    int tileIndex = tilePosY * size.x + tilePosX;
    for (int k = 0; k < 4; k++)
    {
        int vertexIndex = tileIndex * 4 + k;
        vertexArray[vertexIndex].texCoords = texOffsets[k];
    }
    return false;
}

bool OnTileMap::LoadInfo(const std::string& filePath)
{
    if (checkLoad) return true;
    checkLoad = true;

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
    sf::Vector2i size = { (int)doc.GetColumnCount(), (int)doc.GetRowCount() };

    for (int col = 0; col < size.y; ++col)
    {
        TileInfo tile;
        for (int row = 0; row < size.x - 1; ++row)
        {
            //std::cout << col << ", " << row << std::endl;
            switch (row)
            {
            case 0:
                tile.texture_ID = doc.GetCell<std::string>(row, col);
                break;
            case 1:
                tile.bound.left = doc.GetCell<int>(row, col);
                break;
            case 2:
                tile.bound.top = doc.GetCell<int>(row, col);
                break;
            case 3:
                tile.bound.width = doc.GetCell<int>(row, col);
                break;
            case 4:
                tile.bound.height = doc.GetCell<int>(row, col);
                break;
            case 5:
                tile.name = doc.GetCell<std::string>(row, col);
                break;
            case 6:
                tile.index = doc.GetCell<int>(row, col);
            default:
                std::cout << col << ", " << row << std::endl;
                break;
            }
        }
        tileInfoArray.push_back(tile);
        tileInfo[tile.index] = tile;
    }

    for (auto obj : tileInfoArray)
    {
        std::vector<sf::Vector2f> bound;
        bound.push_back({ obj.bound.left, obj.bound.top });
        bound.push_back({ obj.bound.left + obj.bound.width, obj.bound.top });
        bound.push_back({ obj.bound.left + obj.bound.width, obj.bound.top + obj.bound.height });
        bound.push_back({ obj.bound.left, obj.bound.top + obj.bound.height });
        tileOffset.push_back(bound);
    }

    return true;
}

void OnTileMap::SaveTexture(const std::string& filePath)
{
}

void OnTileMap::LoadTexture(const std::string& filePath)
{
}

void OnTileMap::LoadTileDataArray(rapidcsv::Document& map)
{
    tileArray.resize(size.y, std::vector<int>(size.x));

    for (size_t i = 0; i < size.y; i++)
    {
        for (size_t j = 0; j < size.x; j++)
        {
            if (map.GetCell<int>(j, i) == 0)
                tileArray[i][j] = Wall::None;
            else if (map.GetCell<int>(j, i) > 0)
                tileArray[i][j] = 1;
        }
    }
}

void OnTileMap::CheckAdjacent()
{
    for (size_t i = 0; i < size.y; i++)
    {
        for (size_t j = 0; j < size.x; j++)
        {
            int index = tileArray[i][j];

            if (index >= Wall::Wall_B && index < Wall::None)
            {
                bool left = CheckWall(i - 1, j);
                bool right = CheckWall(i + 1, j);
                bool up = CheckWall(i, j - 1);
                bool down = CheckWall(i, j + 1);

                SelectWall(left, right, up, down);
            }
        }
    }
}

void OnTileMap::ResetDataArray()
{
}

bool OnTileMap::CheckWall(int x, int y)
{
    if (x < 0 || x > size.x) return false;
    if (y < 0 || y > size.x) return false;


    int index = tileArray[x][y];
    if (index >= Wall::Wall_B && index < Wall::None) 
        return true;

    return false;
}

Wall OnTileMap::SelectWall(bool left, bool right, bool up, bool down)
{


    return Wall();
}

sf::IntRect OnTileMap::GetTileBound(int index)
{
	return sf::IntRect();
}

sf::Vector2f OnTileMap::TileSize()
{
	return sf::Vector2f();
}

sf::Vector2i OnTileMap::TileIntSize()
{
	return sf::Vector2i();
}

sf::Vector2f OnTileMap::TilePixelSize()
{
	return sf::Vector2f();
}