#pragma once
#include "Line.h"

class TileMap;
class Player;
class Monster;

struct Wall
{
    sf::Vector2i p1;
    sf::Vector2i p2;
};

class Beam
{
private:
    Line m_line;
    int m_x, m_y;
    float m_angle;
    TileMap* tileMap;

public:
    Beam(int x = 0, int y = 0, float angle = 0);
    ~Beam();
    void draw(sf::RenderWindow &window) const;
    void move(int x, int y);
    void Rotation(float angle);

    void SetTileMap(TileMap* tileMap) { this->tileMap = tileMap; }

    bool CheckShortestPath(const sf::Vector2f start, const sf::Vector2f goal);

    const sf::Vector2i PosToIndex(sf::Vector2f pos);
};
