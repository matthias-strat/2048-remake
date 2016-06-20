#include "TileManager.hpp"
#include <cassert>

TileManager::TileManager(Assets& assets, unsigned int gridSize)
    : m_Assets{assets},
      m_GridSize{gridSize}
{    
    m_Tiles.reserve(gridSize*gridSize);

    // Initialize tile grid
    m_TileGrid.resize(gridSize);
    for (auto col(0); col < gridSize; col++)
        m_TileGrid[col].resize(gridSize);
    
    for (auto col(0); col < m_GridSize; col++)
    {
        for (auto row(0); row < m_GridSize; row++)
            m_TileGrid[col][row].worldPos = gridPosToWorldPos({col, row});
    }
}

void TileManager::clear() noexcept
{
    // Clear tile accessor grid
    for (auto col(0); col < m_GridSize; col++)
    {
        for (auto row(0); row < m_GridSize; row++)
            m_TileGrid[col][row].tile = nullptr;
    }

    // Now remove all tiles
    m_Tiles.clear();
}

void TileManager::create(const Vec2i& gridPos, int value) noexcept
{
    m_PendingList.emplace_back(TileAction::Create, gridPos, Vec2i{}, value);
}

void TileManager::moveTile(const Vec2i& from, const Vec2i& to, bool merge) noexcept
{
    m_PendingList.emplace_back((merge ? TileAction::MoveMerge : TileAction::Move), from, to);
}

void TileManager::update(float dt)
{
    removeDeadTiles();
    applyPendingChanges();
    for (auto& t : m_Tiles) t->update(dt);
}

void TileManager::draw(sf::RenderTarget& target)
{
    m_ToSort.clear();
    for (const auto& t : m_Tiles) m_ToSort.emplace_back(t.get());
    {
        std::stable_sort(m_ToSort.begin(), m_ToSort.end(), 
            [](const Tile* a, const Tile* b)
            {
                return a->getDrawPriority() > b->getDrawPriority();
            });
    }

    for (const auto& t : m_ToSort) target.draw(*t);
}

void TileManager::applyPendingChanges()
{
    for (auto change : m_PendingList)
    {
        switch (change.action)
        {
            case TileAction::Create:
            {
                const auto& gridPos(change.from);

                // Create the tile entity
                auto ptr(mkUPtr<Tile>(m_Assets, change.value));
                ptr->setPosition(m_TileGrid[gridPos.x][gridPos.y].worldPos);
                ptr->setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);

                // Add animation
                ptr->addTask<PopTask>(0.3f, 1.0f, 0.2f, [](Tile& tile, float value)
                {
                    tile.setScale(value, value);
                });

                // Register to grid
                m_TileGrid[gridPos.x][gridPos.y].tile = ptr.get();

                m_Tiles.emplace_back(std::move(ptr));
                break;
            }
            case TileAction::Move:
            {
                const auto& from(change.from);
                const auto& to(change.to);

                auto* ptr(m_TileGrid[from.x][from.y].tile);

                // Check if source is not empty
                assert(ptr != nullptr);

                // Check if destination is empty
                assert(m_TileGrid[to.x][to.y].tile == nullptr);

                m_TileGrid[to.x][to.y].tile = ptr;
                m_TileGrid[from.x][from.y].tile = nullptr;

                // Finally add move task
                auto dir(from - to);
                auto start(m_TileGrid[from.x][from.y].worldPos);
                auto end(m_TileGrid[to.x][to.y].worldPos);
                if (dir.x == 0)
                {
                    // Move vertically
                    ptr->addTask<MoveTask>(start.y, end.y, 0.08f, [start](Tile& tile, float value)
                    {
                        tile.setPosition(start.x, value);
                    });
                }
                else
                {
                    // Move horizontally
                    ptr->addTask<MoveTask>(start.x, end.x, 0.08f, [start](Tile& tile, float value)
                    {
                        tile.setPosition(value, start.y);
                    });
                }

                break;
            }
            case TileAction::MoveMerge:
            {
                const auto& from(change.from);
                const auto& to(change.to);

                auto* fromPtr(m_TileGrid[from.x][from.y].tile);
                auto* toPtr(m_TileGrid[to.x][to.y].tile);
                
                // Check if pointers are empty.
                assert(fromPtr != nullptr);
                assert(toPtr != nullptr);

                m_TileGrid[from.x][from.y].tile = nullptr;
                toPtr->setDrawPriority(0);
                fromPtr->setDrawPriority(1);

                // Finally add move task
                auto dir(from - to);
                auto start(m_TileGrid[from.x][from.y].worldPos);
                auto end(m_TileGrid[to.x][to.y].worldPos);
                if (dir.x == 0)
                {
                    // Move vertically
                    fromPtr->addTask<MoveTask>(start.y, end.y, 0.08f, [start](Tile& tile, float value)
                    {
                        tile.setPosition(start.x, value);
                    }, 
                    [toPtr](Tile& tile)
                    {
                        toPtr->increaseValue();
                        tile.markForRemoval();
                        toPtr->addTask<PopTask>(1.0f, 1.15f, 0.05f, [](Tile& t, float value)
                        {
                            t.setScale(value, value);
                        },
                        [](Tile& t2)
                        {
                            t2.addTask<BlinkTask>(1.15f, 1.0f, 0.05f, [](Tile& t, float value)
                            {
                                t.setScale(value, value);
                            });
                        });
                    });
                }
                else
                {
                    // Move horizontally
                    fromPtr->addTask<MoveTask>(start.x, end.x, 0.08f, [start](Tile& tile, float value)
                    {
                        tile.setPosition(value, start.y);
                    }, 
                    [toPtr](Tile& tile)
                    {
                        toPtr->increaseValue();
                        tile.markForRemoval();
                        toPtr->addTask<BlinkTask>(1.0f, 1.15f, 0.05f, [](Tile& t, float value)
                        {
                            t.setScale(value, value);
                        },
                        [](Tile& t2)
                        {
                            t2.addTask<PopTask>(1.15f, 1.0f, 0.05f, [](Tile& t, float value)
                            {
                                t.setScale(value, value);
                            });
                        });

                    });
                }

                break;
            }
        }
    }
    m_PendingList.clear();
}

void TileManager::removeDeadTiles()
{
    m_Tiles.erase(std::remove_if(m_Tiles.begin(), 
                                 m_Tiles.end(), [](auto& tile) { return tile->isMarkedForRemoval(); }),
                  m_Tiles.end());
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

/*TileManager::TileManager(Assets& assets, unsigned int gridSize)
    : m_Assets{assets},
      m_GridSize{gridSize}
{
    m_Tiles.resize(gridSize*gridSize);
    for (auto x(0); x < gridSize; x++)
    {
        for (auto y(0); y < gridSize; y++) 
        {
            auto ptr(mkUPtr<Tile>(assets));
            ptr->setPosition(gridPosToWorldPos({x, y}));
            ptr->setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);

            m_Tiles[get1DIndexFrom2D(x, y, m_GridSize)] = std::move(ptr);
        }
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
    auto fromIdx(get1DIndexFrom2D(fromPos, m_GridSize));
    auto toIdx(get1DIndexFrom2D(toPos, m_GridSize));

    m_Tiles[toIdx]->setValue(m_Tiles[fromIdx]->getValue());
    m_Tiles[fromIdx]->destroy();
    m_Tiles[toIdx]->revive();
    m_Tiles[toIdx]->setScale(1.0, 1.0);
}

void TileManager::mergeTiles(const Vec2i& fromPos, const Vec2i& toPos)
{
    auto fromIdx(get1DIndexFrom2D(fromPos, m_GridSize));
    auto toIdx(get1DIndexFrom2D(toPos, m_GridSize));

    m_Tiles[toIdx]->setValue(m_Tiles[fromIdx]->getValue());
    m_Tiles[toIdx]->increaseValue();
    m_Tiles[fromIdx]->destroy();
    m_Tiles[toIdx]->revive();
    m_Tiles[toIdx]->setScale(1.0, 1.0);
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
}*/