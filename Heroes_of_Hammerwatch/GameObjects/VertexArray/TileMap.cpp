#include "stdafx.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <vector>
#include "Tree.h"
#include "OnTileMap.h"
#include "Astar.h"

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
    sortLayer = SortLayer::TILE;
    route = nullptr;
    finder = new Astar();
    finder->SetTileArray(tileArray);
    finder->SetMaxFindValueRate(2);
}

TileMap::~TileMap()
{
    if (route != nullptr)
        delete route;

    if (finder != nullptr)
        delete finder;

    route = nullptr;
    finder = nullptr;
}

void TileMap::Draw(sf::RenderWindow& window)
{
    VertexArrayGo::Draw(window);
    if (route == nullptr) return;

    route->Draw(window);
}

bool TileMap::LoadDrawTexture(const std::string& filePath)
{
    texture = RESOURCE_MGR.GetTexture(textureId);

    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    //std::cout << (int)map.GetRowCount();
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount()-1 };

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
            //ChangeTile(j, i, tileArray[i][j]);
            int tileIndex = size.x * i + j;
            int texIndex = tileArray[i][j];
            for (int k = 0; k < 4; k++)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = tileOffset[texIndex][k];
            }
            currPos.x += tileSize.x;
            //std::cout << tileArray[i][j] << std::endl;
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

    if (onTileMap != nullptr)
    {
        onTileMap->ChangeTile(tilePosX, tilePosY, idx);
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
        outputFile << textureId << ",";
        outputFile << onTileMap->GetStartIndex().x << "," << onTileMap->GetStartIndex().y << ",";
        outputFile << onTileMap->GetStartIndex().x << "," << onTileMap->GetStartIndex().y << ",";
        

        for (size_t i = 0; i < tileArray[0].size() - 6; i++)
        {
            outputFile << ",";
        }
        outputFile << "\n";

        for (const auto& row : tileArray)
        {
            for (size_t i = 0; i < row.size(); i++)
            {
                outputFile << row[i];
                if (i < row.size() - 1)
                    outputFile << ",";
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
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
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

    start = { map.GetCell<float>(1, 0), map.GetCell<float>(2, 0) };
    ent = { map.GetCell<float>(3, 0), map.GetCell<float>(4, 0) };
    onTileMap->SetStartPos(start * 16.f);
    onTileMap->SetEntPos(ent * 16.f);

    for (size_t i = 1; i < size.y+1; i++)
    {
        for (size_t j = 0; j < size.x; j++)
        {
            tileArray[i - 1][j] = map.GetCell<int>(j, i);
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

void TileMap::Divide()
{
    if (route == nullptr)
    {
        route = new Tree(sf::IntRect{ 5, 5, size.x - 10, size.y - 10});
    }
    route->Divide(this);
}

void TileMap::ConnectRoom()
{
    if (route == nullptr) return;
    route->ConnectRoom(this);
}

bool TileMap::SelectDoor()
{
    finder->SetTileArray(tileArray);
    finder->SetMaxFindValueRate(100000);

    if (route == nullptr) return false;
    return route->Room(this, finder);
}

void TileMap::CreateDoor(sf::Vector2i start, sf::Vector2i ent)
{
    onTileMap->ChangeDoor(start, ent, this);
    this->start = (sf::Vector2f)start;
    this->ent = (sf::Vector2f)ent;

    finder->SetTileArray(tileArray);
}

void TileMap::Debug()
{
    route->Debug();
}

sf::Vector2f TileMap::GetFloatPosition(sf::Vector2i intPos)
{
    return { (intPos.x * 16.f + 8.f) ,(intPos.y * 16.f + 8.f) };
}

Astar* TileMap::GetAstar()
{
    finder->SetTileArray(tileArray);
    finder->SetMaxFindValueRate(2);
    return finder;
}

void TileMap::Summon()
{
    route->SummonMonster(onTileMap->GetStartPos(), this);
}

bool TileMap::CheckEnt(sf::FloatRect bound)
{
    return onTileMap->CheckEnt(bound);
    //return true;
}
