#include "stdafx.h"
#include "OnTileMap.h"
#include "ResourceMgr.h"
#include "TileMap.h"

OnTileMap::OnTileMap(const std::string& textureId, const std::string& n)
	: VertexArrayGo(textureId, n)
{
	sortLayer = SortLayer::WALL;
    texture = RESOURCE_MGR.GetTexture(textureId);
}

OnTileMap::~OnTileMap()
{
}

void OnTileMap::Draw(sf::RenderWindow& window)
{
    VertexArrayGo::Draw(window);
    window.draw(ent);
    window.draw(start);
}

bool OnTileMap::LoadDrawOnTile(TileMap* tileMap)
{

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
            ChangeTile(j, i, texIndex);
            //for (int k = 0; k < 4; k++)
            //{
            //    int vertexIndex = tileIndex * 4 + k;
            //    //vertexArray[vertexIndex].position = currPos + offsets[k];
            //    if (texIndex > 0) //0 벽, 1~9 타일
            //    {
            //        vertexArray[vertexIndex].position = currPos + offsets[k];
            //        vertexArray[vertexIndex].texCoords = tileOffset[Wall::None][k];
            //    }
            //    else if(texIndex == 0)
            //    {
            //        vertexArray[vertexIndex].position = currPos + offsetsLong[k];
            //        vertexArray[vertexIndex].texCoords = tileOffset[Wall::Wood_L][k];
            //    }
            //}
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

   // ent.setTexture(*texture);
    //ent.setTextureRect((sf::IntRect)tileInfoArray[22].bound);

   // start.setTexture(*texture);
   // start.setTextureRect((sf::IntRect)tileInfoArray[23].bound);

    return true;
}

bool OnTileMap::ChangeTile(int tilePosX, int tilePosY, int idx)
{
    /*
    idx 0 벽
    idx 1 ~ 9 타일
    idx 10 절벽
    */
    Wall wall[5] = { Wall::None };

    if (tilePosX < 0 || tilePosY < 0) return false;
    if (tilePosX >= size.x || tilePosY >= size.y) return false;

    tileArray[tilePosY][tilePosX] = idx;

    if (idx == 0 || idx == 10)
    {
        wall[0] = CheckAdjacent(tilePosX, tilePosY);
    }
    else if (idx >= 1 && idx < 10)
    {
        wall[0] = Wall::None;
    }

    if (tilePosX - 1 < 0) wall[1] = Wall::None;
    else if (tileArray[tilePosY][tilePosX - 1] == 0 || tileArray[tilePosY][tilePosX - 1] == 10)
    {
        wall[1] = CheckAdjacent(tilePosX - 1, tilePosY);
    }

    if (tilePosX + 1 >= size.x) wall[2] = Wall::None;
    else if (tileArray[tilePosY][tilePosX + 1] == 0 || tileArray[tilePosY][tilePosX + 1] == 10)
    {
        wall[2] = CheckAdjacent(tilePosX + 1, tilePosY);
    }

    if (tilePosY - 1 < 0) wall[3] = Wall::None;
    else if (tileArray[tilePosY - 1][tilePosX] == 0 || tileArray[tilePosY - 1][tilePosX] == 10)
    {
        wall[3] = CheckAdjacent(tilePosX, tilePosY - 1);
    }
    
    if (tilePosY + 1 >= size.y) wall[4] = Wall::None;
    else if (tileArray[tilePosY + 1][tilePosX] == 0 || tileArray[tilePosY + 1][tilePosX] == 10)
    {
        wall[4] = CheckAdjacent(tilePosX, tilePosY + 1);
    }

    sf::Vector2f currPos[5] = {
        {tilePosX * tileSize.x, tilePosY * tileSize.y},
        {(tilePosX - 1) * tileSize.x, tilePosY * tileSize.y},
        {(tilePosX + 1) * tileSize.x, tilePosY * tileSize.y},
        {tilePosX * tileSize.x, (tilePosY - 1) * tileSize.y},
        {tilePosX * tileSize.x, (tilePosY + 1) * tileSize.y}
    };

    for (int i = 0; i < 5; i++)
    {
        sf::FloatRect rect = tileInfoArray[wall[i]].bound;
        sf::Vector2f texOffsets[4] =
        {
            { rect.left, rect.top },
            { rect.left + rect.width, rect.top },
            { rect.left + rect.width, rect.top + rect.height },
            { rect.left, rect.top + rect.height }
        };

        int tileIndex;
        switch (i)
        {
        case 0:
            tileIndex = tilePosY * size.x + tilePosX;
            break;
        case 1:
            tileIndex = tilePosY * size.x + tilePosX - 1;
            if (tilePosX - 1 < 0) continue;
            break;
        case 2:
            tileIndex = tilePosY * size.x + tilePosX + 1;
            if (tilePosX + 1 >= size.x) continue;
            break;
        case 3:
            tileIndex = (tilePosY - 1) * size.x + tilePosX;
            if (tilePosY - 1 < 0) continue;
            break;
        case 4:
            tileIndex = (tilePosY + 1) * size.x + tilePosX;
            if (tilePosY + 1 >= size.y) continue;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            int vertexIndex = tileIndex * 4 + k;
            if (rect.height < 0)
            {
                vertexArray[vertexIndex].position = currPos[i] + offsetsLong[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
            }
            else
            {
                vertexArray[vertexIndex].position = currPos[i] + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
            }
        }
    }
    return false;
}

void OnTileMap::ChangeDoor(sf::Vector2i startPos, sf::Vector2i entPos, TileMap* tileMap)
{
    for (int i = entPos.x - 3; i < entPos.x + 3; i++)
    {
        for (int j = entPos.y + 1; j < entPos.y + 4; j++)
        {
            if (j == startPos.y + 4)
            {
                ChangeTile(i, j, 0);
                tileMap->ChangeTile(i, j, 0);

                if (i == startPos.x - 1 || i == startPos.x)
                {
                    //ChangeTile(i, j, 8);
                    tileMap->ChangeTile(i, j, 8);
                }
                continue;
            }
            ChangeTile(i, j, 0);
            tileMap->ChangeTile(i, j, 0);
        }
    }

    for (int i = startPos.x - 3; i < startPos.x + 3; i++)
    {
        for (int j = startPos.y + 1; j < startPos.y + 8; j++)
        {
            if (j >= startPos.y + 4)
            {

                ChangeTile(i, j, 0);
                tileMap->ChangeTile(i, j, 0);

                if (i == startPos.x - 1 || i == startPos.x)
                {
                    ChangeTile(i, j, 8);
                    tileMap->ChangeTile(i, j, 8);
                }
                continue;
            }
            else if (j == startPos.y + 5)
            {
                if (i == startPos.x - 1 || i == startPos.x)
                {
                    ChangeTile(i, j, 8);
                    tileMap->ChangeTile(i, j, 8);
                }
                continue;
            }
            ChangeTile(i, j, 0);
            tileMap->ChangeTile(i, j, 0);
        }
    }

    ent.setTexture(*texture);
    ent.setTextureRect((sf::IntRect)tileInfoArray[22].bound);
    ent.setPosition(tileSize.x * (entPos.x - 2), tileSize.y * (entPos.y));

    start.setTexture(*texture);
    start.setTextureRect((sf::IntRect)tileInfoArray[23].bound);
    start.setPosition(tileSize.x * (startPos.x - 2), tileSize.y * (startPos.y));
}

bool OnTileMap::DrawTexture(int row, int col)
{
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
        if (tile.bound.height == 48)
        {
            tile.bound.top += tile.bound.height;
            tile.bound.height = -tile.bound.height;
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

Wall OnTileMap::CheckAdjacent(int i, int j)
{
    int index = tileArray[j][i];

    if (index == 0)
    {
        bool left = CheckWall(j, i - 1);
        bool right = CheckWall(j, i + 1);
        bool top = CheckWall(j - 1, i);
        bool behind = CheckWall(j + 1, i);
        //벽이 있으면 true 없으면 false

        return SelectWall(left, right, top, behind);
    }
    else if (index == 10)
    {
        bool left = CheckHole(j, i - 1);
        bool right = CheckHole(j, i + 1);
        bool top = CheckHole(j - 1, i);
        bool behind = CheckHole(j + 1, i);
        //벽이 있으면 true 없으면 false
        
        if (SelectHole(left, right, top, behind) == Wall::Hole_None)
        {
            if (CheckHole(j - 1, i - 1))
            {
                return Wall::Hole_X1;
            }
            else if (CheckHole(j - 1, i + 1))
            {
                return Wall::Hole_X2;
            }
            else if (CheckHole(j + 1, i + 1))
            {
                return Wall::Hole_X4;
            }
            else if (CheckHole(j + 1, i - 1))
            {
                return Wall::Hole_X3;
            }
        }

        return SelectHole(left, right, top, behind);
    }

    return Wall::None;
}

bool OnTileMap::CheckWall(int x, int y)
{
    if (x < 0 || x >= size.y) return false;
    if (y < 0 || y >= size.x) return false;

    int index = tileArray[x][y];

    if (index == 0) 
        return true;
    return false;
}

bool OnTileMap::CheckHole(int x, int y)
{
    if (x < 0 || x >= size.y) return false;
    if (y < 0 || y >= size.x) return false;

    int index = tileArray[x][y];

    if (index == 10)
        return false;
    return true;
}

Wall OnTileMap::SelectWall(bool left, bool right, bool up, bool down)
{
    switch ((left << 3) | (right << 2) | (up << 1) | down) {
    case 0b0000:
        return Wall::Wall_None;
    case 0b0001:
        return Wall::Wall_B;
    case 0b0010:
        return Wall::Wall_T;
    case 0b0011:
        return Wall::Wall_TB;
    case 0b0100:
        return Wall::Wall_R;
    case 0b0101:
        return Wall::Wall_RB;
    case 0b0110:
        return Wall::Wall_RT;
    case 0b0111:
        return Wall::Wall_RTB;
    case 0b1000:
        return Wall::Wall_L;
    case 0b1001:
        return Wall::Wall_LB;
    case 0b1010:
        return Wall::Wall_LT;
    case 0b1011:
        return Wall::Wall_LTB;
    case 0b1100:
        return Wall::Wall_LR;
    case 0b1101:
        return Wall::Wall_LRB;        
    case 0b1110:
        return Wall::Wall_LRT;
    case 0b1111:
        return Wall::Wall_LRTB;
    default:
        std::cout << "Invalid combination of variables." << std::endl;
        break;
    }

    return Wall::None;
}

Wall OnTileMap::SelectHole(bool left, bool right, bool top, bool down)
{
    switch ((left << 3) | (right << 2) | (top << 1) | down) {
    case 0b0000:
        return Wall::Hole_None;
    case 0b0001:
        return Wall::Hole_B;
    case 0b0010:
        return Wall::Hole_T;
    case 0b0011:
        //return Wall::Hole_TB;
        return Wall::Hole_None;
    case 0b0100:
        return Wall::Hole_R;
    case 0b0101:
        return Wall::Hole_RB;
    case 0b0110:
        return Wall::Hole_RT;
    case 0b0111:
        //return Wall::Wall_RTB;
        return Wall::Hole_None;
    case 0b1000:
        return Wall::Hole_L;
    case 0b1001:
        return Wall::Hole_LB;
    case 0b1010:
        return Wall::Hole_LT;
    case 0b1011:
        //return Wall::Wall_LTB;
        return Wall::Hole_None;
    case 0b1100:
        //return Wall::Wall_LR;
        return Wall::Hole_None;
    case 0b1101:
        //return Wall::Wall_LRB;
        return Wall::Hole_None;
    case 0b1110:
        //return Wall::Wall_LRT;
        return Wall::Hole_None;
    case 0b1111:
        return Wall::Hole_None;
    default:
        std::cout << "Invalid combination of variables." << std::endl;
        break;
    }
    
    return Wall::Hole_None;
}

void OnTileMap::SetEntrance()
{

}

bool OnTileMap::CheckEnt(sf::FloatRect bound)
{
    if (ent.getGlobalBounds().intersects(bound))
        return true;
    return false;
}
