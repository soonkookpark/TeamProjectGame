#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"
#include "ResourceMgr.h"

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
    sortLayer = SortLayer::TILE;
}

TileMap::~TileMap()
{
}

bool TileMap::DrawTexture(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.texIndex = map.GetCell<int>(j, i);
            tiles.push_back(tile);
        }
    }

    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };

    sf::Vector2f wallTexOffsets[4] =
    {
        { 32.f, 32.f },
        { 32 + texSize.x, 32},
        { 32 + texSize.x, 32 + texSize.y },
        { 32.f, 32 + texSize.y }
    };

    sf::Vector2f WOTexOffsets[4] =
    {
        { 64.f, 32.f },
        { 64 + texSize.x, 32},
        { 64 + texSize.x, 32 + texSize.y },
        { 64.f, 32 + texSize.y }
    };



    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            int tileIndex = size.x * i + j;
            int texIndex = tiles[tileIndex].texIndex;
            for (int k = 0; k < 4; k++)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];

                vertexArray[vertexIndex].texCoords = texOffsets[k];
                if (texIndex == 0)
                {
                    vertexArray[vertexIndex].texCoords = wallTexOffsets[k];
                }
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

    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { 32.f, 0.f },
        { 32.f, 32.f },
        { 0.f, 32.f }
    };



    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            int tileIndex = size.x * i + j;
            int texIndex = tiles[tileIndex].texIndex;
            for (int k = 0; k < 4; k++)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

    return true;
}

bool TileMap::ChangeTile(int tilePosX, int tilePosY, sf::IntRect rectInt)
{
    if (tilePosX < 0 || tilePosY < 0) return false;
    if (tilePosX >= size.x || tilePosY >= size.y) return false;

    sf::FloatRect rect = (sf::FloatRect)rectInt;

    sf::Vector2f texOffsets[4] =
    {
        { rect.left, rect.top },
        { rect.left + rect.width, rect.top },
        { rect.left + rect.width, rect.top + rect.height },
        { rect.left, rect.top + rect.height }
    };

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
    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(-1, -1));
    sf::Vector2i size = { (int)doc.GetColumnCount(), (int)doc.GetRowCount() };

    for (int col = 1; col < size.y; ++col)
    {
        for (int row = 0; row < size.x; ++row)
        {
            TileInfo tile;
            switch (row)
            {
            case 0:
                tile.texture_ID = doc.GetCell<std::string>(col, row);
                break;
            case 1:
                tile.bound.left = doc.GetCell<int>(col, row);
                break;
            case 2:
                tile.bound.top = doc.GetCell<int>(col, row);
                break;
            case 3:
                tile.bound.width = doc.GetCell<int>(col, row);
                break;
            case 4:
                tile.bound.height = doc.GetCell<int>(col, row);
                break;
            case 5:
                tile.name = doc.GetCell<std::string>(col, row);
                break;
            default:
                throw std::out_of_range("Can't Find");
            }

            tileInfo[tile.name] = tile;
        }
    }

    return true;
}

sf::Vector2f TileMap::TileSize()
{
    return sf::Vector2f();
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
