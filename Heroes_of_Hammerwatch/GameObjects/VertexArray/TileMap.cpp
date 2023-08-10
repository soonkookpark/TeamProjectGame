#include "stdafx.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <vector>

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
    sortLayer = SortLayer::TILE;
}

TileMap::~TileMap()
{
}

bool TileMap::LoadDrawTexture(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(0, -1));
    std::cout << (int)map.GetRowCount();
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    LoadDataArray(map);
    LoadInfo("graphics/mine/mine_tile.csv");

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
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = tileOffset[texIndex][k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

    return true;
}

bool TileMap::DrawTexture(int row, int col)
{
    texture = RESOURCE_MGR.GetTexture(textureId);

    size = { col, row };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tiles.push_back(tile);
        }
    }
    ResetDataArray();
    LoadInfo("graphics/mine/mine_tile.csv");

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
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = tileOffset[texIndex][k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }
    return true;
}

bool TileMap::ChangeTile(int tilePosX, int tilePosY, int idx)
{
    if (tilePosX < 0 || tilePosY < 0) return false;
    if (tilePosX >= size.x || tilePosY >= size.y) return false;

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

bool TileMap::LoadInfo(const std::string& filePath)
{
    if (checkLoad) return true;
    checkLoad = true;

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
    sf::Vector2i size = { (int)doc.GetColumnCount(), (int)doc.GetRowCount() };

    for (int col = 0; col < size.y; ++col)
    {
        TileInfo tile;
        for (int row = 0; row < size.x-1; ++row)
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

void TileMap::SaveTexture(const std::string& filePath)
{
    std::ofstream outputFile(filePath);
    if (outputFile.is_open())
    {
        outputFile << textureId << "\n";
        for (const auto& row : tileArray)
        {
            for (size_t i = 0; i < row.size(); i++)
            {
                outputFile << row[i];
                if (i < row.size() - 1)
                    outputFile << ", ";
            }
            outputFile << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "File Open Error!" << std::endl;
    }

}

void TileMap::LoadTexture(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(0, -1));
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    LoadDataArray(map);
    LoadInfo("graphics/mine/mine_tile.csv");

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
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = tileOffset[texIndex][k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }
}

void TileMap::LoadDataArray(rapidcsv::Document& map)
{
    tileArray.resize(size.y, std::vector<int>(size.x));

    for (size_t i = 0; i < size.y; i++)
    {
        for (size_t j = 0; j < size.x; j++)
        {
            tileArray[i][j] = map.GetCell<int>(j, i);
        }
    }

}

void TileMap::ResetDataArray()
{
    tileArray.resize(size.y, std::vector<int>(size.x));

    for (size_t i = 0; i < size.y; i++)
    {
        for (size_t j = 0; j < size.x; j++)
        {
            tileArray[i][j] = 1;
        }
    }
}

sf::IntRect TileMap::GetTileBound(int index)
{
    return sf::IntRect(tileInfoArray[index].bound);
}

sf::Vector2f TileMap::TileSize()
{
    return tileSize;
}

sf::Vector2i TileMap::TileIntSize()
{
    return size;
}

sf::Vector2f TileMap::TilePixelSize()
{
    return tileSize;
}

Tile& TileMap::GetTile(int x, int y)
{
    if (x >= 0 && x < 40 && y >= 0 && y < 40)
    {
        int index = y * 40 + x;
        return tiles[index];
    }
    else
    {
        // 예외 처리: 인덱스가 올바르지 않은 경우
        throw std::out_of_range("Tile index out of range");
    }
}
