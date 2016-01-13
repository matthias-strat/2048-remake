#pragma once
#include "Common.hpp"
#include "Tile.hpp"

class TileManager
{
public:

    void update();
    void draw(sf::RenderTarget& target);

    Tile& create(int value);

private:
    std::vector<UPtr<Tile>> m_Tiles;
};
