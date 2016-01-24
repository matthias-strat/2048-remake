#include "TileManager.hpp"
#include <cassert>

TileManager::TileManager(Assets& assets)
{
    for (auto i(0); i < defaultNumCells * defaultNumCells; i++)
    {
        auto ptr(mkUPtr<Tile>(assets));
        m_Tiles.emplace_back(std::move(ptr));
    }
}

Tile& TileManager::create(int value)
{
    return *m_Tiles[0];
}

void TileManager::update(float ft)
{
    for (auto& t : m_Tiles)
    {
        if (t->getIsAlive()) t->update(ft);
    }
}

void TileManager::draw(sf::RenderTarget& target)
{
    for (const auto& t : m_Tiles)
    {
        if (!t->getIsAlive()) continue;
        target.draw(*t);
    }
}