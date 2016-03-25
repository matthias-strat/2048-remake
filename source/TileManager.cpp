#include "TileManager.hpp"
#include <cassert>

TileManager::TileManager(Assets& assets, unsigned int gridSize)
    : m_Assets{assets},
      m_GridSize{gridSize}
{
    m_Tiles.resize(gridSize*gridSize);
    for (auto n(0); n < gridSize*gridSize; n++)
    {
        auto ptr(mkUPtr<Tile>(assets));
        ptr->setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);
        m_Tiles[n] = std::move(ptr);
    }
}

Tile& TileManager::create(const Vec2i& gridPos, int value)
{
    auto idx(get1DIndexFrom2D(gridPos, m_GridSize));
    auto& ptr(m_Tiles[idx]);
    auto worldPos(gridPosToWorldPos(gridPos));
    ptr->setPosition(worldPos);
    ptr->setValue(value);
    ptr->revive();

    ptr->addTask<PopTask>(0.3f, 1.0f, 0.2f, [](Tile& tile, float value)
    {
        tile.setScale(value, value);
    });

    return *m_Tiles[idx];
}

void TileManager::moveTile(const Vec2i& fromPos, const Vec2i& toPos)
{
}

void TileManager::mergeTiles(const Vec2i& fromPos, const Vec2i& toPos)
{
    
}

void TileManager::clear()
{
    for (auto& tile : m_Tiles) tile->destroy();
}

void TileManager::update(float dt)
{
   for (auto& t : m_Tiles)
   {
        if (t->isAlive()) t->update(dt);
   }
}

void TileManager::draw(sf::RenderTarget& target)
{
    for (const auto& t : m_Tiles)
    {
        if (t->isAlive()) target.draw(*t);
    }
}

void TileManager::resize(unsigned int width, unsigned int height)
{
    m_WindowWidth = width;
    m_WindowHeight = height;
}

Vec2f TileManager::gridPosToWorldPos(const Vec2i& gridPos) noexcept
{
    auto baseX(m_WindowWidth/2.f-defaultGridSize/2.f);
    auto baseY(m_WindowHeight/2.f-defaultGridSize/2.f);
    auto halfTileSize(defaultTileSize/2.f);
    baseX += defaultSpacing + halfTileSize;
    baseY += defaultSpacing + halfTileSize;

    return {baseX + (gridPos.x * defaultSpacing) + (gridPos.x * defaultTileSize),
            baseY + (gridPos.y * defaultSpacing) + (gridPos.y * defaultTileSize)};
}