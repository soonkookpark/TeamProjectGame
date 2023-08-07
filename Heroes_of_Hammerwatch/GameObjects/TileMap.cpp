#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    sf::Vector2i size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

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
        { 128.f, 64.f },
        { 128 + texSize.x, 64 + 0.f },
        { 128 + texSize.x, 64 + texSize.y },
        { 128.f, 64 + texSize.y }
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

float TileMap::TileXSize()
{
    return 0.0f;
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
        // ���� ó��: �ε����� �ùٸ��� ���� ���
        throw std::out_of_range("Tile index out of range");
    }
}