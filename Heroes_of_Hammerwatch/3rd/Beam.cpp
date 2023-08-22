#include "stdafx.h"
#include "Beam.h"
#include "TileMap.h"
#include "Player.h"
#include "Monster.h"
#include "Utils.h"

#define SX 1280
#define SY 720
#define RAD 3.14159265 / 180.0

Beam::Beam(int x, int y, float angle) : m_x(x), m_y(y), m_angle(angle), m_line(x, y, angle, 2)
{
}

void Beam::draw(sf::RenderWindow &window) const
{
    m_line.draw(window);
}

bool Beam::CheckShortestPath(const sf::Vector2f start, const sf::Vector2f goal)
{
    std::vector<sf::Vector2f> collisionPoints;
    std::vector<Wall> walls;

    float x1 = m_line.getX1();
    float y1 = m_line.getY1();
    float x2 = m_line.getX2();
    float y2 = m_line.getY2();
    float hypo = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    int arraySize = tileMap->GetTileArray().size() * tileMap->GetTileArray()[0].size();
    //Ÿ���� Wall�� ����
    for (int i = 0; i < arraySize; i++)
    {
        
        sf::IntRect rect = tileMap->GetTileBound(i);
        sf::Vector2i p1 = { rect.left, rect.top };
        sf::Vector2i p2 = { rect.left + rect.width, rect.top };
        sf::Vector2i p3 = { rect.left, rect.top + rect.height };
        sf::Vector2i p4 = { rect.left + rect.width, rect.top + rect.height };

        Wall topWall = { p1, p2 };
        Wall leftWall = { p1, p3 };
        Wall rightWall = { p2, p4 };
        Wall bottomWall = { p3, p4 };

        walls.push_back(topWall);
        walls.push_back(leftWall);
        walls.push_back(rightWall);
        walls.push_back(bottomWall);
    }
    
    sf::Vector2i goalIndex = PosToIndex(goal);

    sf::IntRect rect = tileMap->GetTileBound(goalIndex.y * + goalIndex.x);
    sf::Vector2i p1 = { rect.left, rect.top };
    sf::Vector2i p2 = { rect.left + rect.width, rect.top };
    sf::Vector2i p3 = { rect.left, rect.top + rect.height };
    sf::Vector2i p4 = { rect.left + rect.width, rect.top + rect.height };

    Wall topWall = { p1, p2 };
    Wall leftWall = { p1, p3 };
    Wall rightWall = { p2, p4 };
    Wall bottomWall = { p3, p4 };

    walls.push_back(topWall);
    walls.push_back(leftWall);
    walls.push_back(rightWall);
    walls.push_back(bottomWall);


    for (auto wall : walls)
    {
        float x3, y3, x4, y4, numerator1, numerator2, denominator;

        x3 = wall.p1.x;
        y3 = wall.p1.y;
        x4 = wall.p2.x;
        y4 = wall.p2.y;

        numerator1 = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        numerator2 = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3));
        denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (denominator != 0)
        {
            const float t = numerator1 / denominator;
            const float u = numerator2 / denominator;
            if (0 < u && 0 < t && u < 1)
            {
                float intersection_x = x1 + t * (x2 - x1);
                float intersection_y = y1 + t * (y2 - y1);

                collisionPoints.push_back({ intersection_x, intersection_y });

            }
        }
    }

    float xSize = tileMap->GetTileArray().size() * tileMap->TilePixelSize().x;
    float ySize = tileMap->GetTileArray()[0].size() * tileMap->TilePixelSize().y;
    float distance = Utils::Magnitude(sf::Vector2f(xSize, ySize));
    for (auto& point : collisionPoints)
    {
        float newDistance = Utils::Distance({ (float)m_line.getX1(), (float)m_line.getY1() }, (sf::Vector2f)point);
        if (distance > newDistance)
        {
            distance = newDistance;
            m_line.setEndPoint(point.x, point.y);
        }
    }    
    sf::Vector2i endPointIndex = PosToIndex(m_line.getEndPoint());
    return true;
}

bool Beam::checkCollision(Player* player)
{
    std::vector<sf::Vector2f> collisionPoints;
    std::vector<int> wallTiles;
    std::vector<Wall> walls;

    //Wall Ÿ�ϸ� ����
    int i = 0; 
    for (auto& tileArrayX : tileMap->GetTileArray())
    {
        for (auto& tile : tileArrayX)
        {
            if (tile != 0)
                continue;
            else
                wallTiles.push_back(i);
            i++;
        }
    }


    float x1 = m_line.getX1();
    float y1 = m_line.getY1();
    float x2 = m_line.getX2();
    float y2 = m_line.getY2();
    float hypo = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    //Ÿ���� Wall�� ����
    int arraySize = tileMap->GetTileArray().size() * tileMap->GetTileArray()[0].size();
    for (int wallTile : wallTiles)
    {
        sf::IntRect rect = tileMap->GetTileBound(wallTile);
        sf::Vector2i p1 = { rect.left, rect.top };
        sf::Vector2i p2 = { rect.left + rect.width, rect.top };
        sf::Vector2i p3 = { rect.left, rect.top + rect.height };
        sf::Vector2i p4 = { rect.left + rect.width, rect.top + rect.height };

        Wall topWall = { p1, p2 };
        Wall leftWall = { p1, p3 };
        Wall rightWall = { p2, p4 };
        Wall bottomWall = { p3, p4 };

        walls.push_back(topWall);
        walls.push_back(leftWall);
        walls.push_back(rightWall);
        walls.push_back(bottomWall);
    }

    {
        sf::IntRect rect = (sf::IntRect)player->GetPlayerBox().getGlobalBounds();
        sf::Vector2i p1 = { rect.left, rect.top };
        sf::Vector2i p2 = { rect.left + rect.width, rect.top };
        sf::Vector2i p3 = { rect.left, rect.top + rect.height };
        sf::Vector2i p4 = { rect.left + rect.width, rect.top + rect.height };

        Wall topWall = { p1, p2 };
        Wall leftWall = { p1, p3 };
        Wall rightWall = { p2, p4 };
        Wall bottomWall = { p3, p4 };

        walls.push_back(topWall);
        walls.push_back(leftWall);
        walls.push_back(rightWall);
        walls.push_back(bottomWall);
    }


    for (auto wall : walls)
    {
        float x3, y3, x4, y4, numerator1, numerator2, denominator;

        x3 = wall.p1.x;
        y3 = wall.p1.y;
        x4 = wall.p2.x;
        y4 = wall.p2.y;

        numerator1 = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        numerator2 = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3));
        denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (denominator != 0)
        {
            const float t = numerator1 / denominator;
            const float u = numerator2 / denominator;
            if (0 < u && 0 < t && u < 1)
            {
                float intersection_x = x1 + t * (x2 - x1);
                float intersection_y = y1 + t * (y2 - y1);

                collisionPoints.push_back({ intersection_x, intersection_y });
            }
        }
    }
    return collisionPoints.empty();
    /*
    float distance = 1000;
    for (auto& point : collisionPoints)
    {
        float newDistance = Utils::Distance({ (float)m_line.getX1(), (float)m_line.getY1() }, (sf::Vector2f)point);
        if (distance > newDistance)
        {
            distance = newDistance;
            m_line.setEndPoint(point.x, point.y);
        }
    }
    */
}


void Beam::move(int x, int y)
{
    m_x = x;
    m_y = y;
    m_line.move(x, y);
}

void Beam::Rotation(float angle)
{
    m_angle = angle;
    m_line.Rotation(m_angle);
}


Beam::~Beam()
{
}

const sf::Vector2i Beam::PosToIndex(sf::Vector2f pos)
{
    int rowIndex = pos.x / tileMap->TilePixelSize().x;
    int columnIndex = pos.y / tileMap->TilePixelSize().y;

    return sf::Vector2i(rowIndex, columnIndex);
}
