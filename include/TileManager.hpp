#pragma once
#include "Common.hpp"
#include "Tile.hpp"

class TileManager
{
public:
    TileManager(Assets& assets);
    
    void update(float ft);
    void draw(sf::RenderTarget& target);

    Tile& create(int value);

private:
    std::vector<UPtr<Tile>> m_Tiles;
    std::size_t m_Size{0};  // Actual number of tiles
    std::size_t m_SizeNext{0};  // Number of tiles after the next refresh() call
    std::size_t m_Capacity{defaultTileSize*defaultTileSize};  // Maximum number of tiles
};
