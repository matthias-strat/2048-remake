#pragma once
#include "Common.hpp"
#include "Tile.hpp"

class TileManager
{
public:
    TileManager(Assets& assets, unsigned int gridSize);
    
    void update(float dt);
    void draw(sf::RenderTarget& target);

    Tile& create(const Vec2i& gridPos, int value = 2);
    void clear();

    void resize(unsigned int width, unsigned int height);

    void moveTile(const Vec2i& from, const Vec2i& to);
    void mergeTiles(const Vec2i& from, const Vec2i& to);

private:
    Vec2f gridPosToWorldPos(const Vec2i& gridPos) noexcept;

private:
    Assets& m_Assets;
    unsigned int m_GridSize;
    unsigned int m_WindowWidth{defaultWindowWidth}, m_WindowHeight{defaultWindowHeight};
    std::vector<UPtr<Tile>> m_Tiles;
};
