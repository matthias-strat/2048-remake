#pragma once
#include "Common.hpp"
#include "Tile.hpp"

class TileManager
{
public:
    TileManager(Assets& assets, unsigned int gridSize);

    void clear() noexcept;

    void create(const Vec2i& gridPos, int value = 2) noexcept;
    void moveTile(const Vec2i& from, const Vec2i& to, bool merge) noexcept;

    void update(float dt);
    void draw(sf::RenderTarget& target);

private:
    void applyPendingChanges();
    void removeDeadTiles();
    Vec2f gridPosToWorldPos(const Vec2i& gridPos) noexcept;

private:
    struct TileCell
    {
        Vec2f worldPos;
        Tile* tile{nullptr};
    };

    enum class TileAction
    {
        Create,
        Move,
        MoveMerge
    };

    struct PendingChange
    {
        TileAction action;
        Vec2i from;
        Vec2i to;
        int value;

        PendingChange(TileAction action, const Vec2i& from = Vec2i{}, 
            const Vec2i& to = Vec2i{}, int value = 0)
            : action{action},
              from{from}, to{to},
              value{value}
        { }
    };

    Assets& m_Assets;
    unsigned int m_GridSize;
    unsigned int m_WindowWidth{defaultWindowWidth}, m_WindowHeight{defaultWindowHeight};

    std::vector<UPtr<Tile>> m_Tiles;
    std::vector<std::vector<TileCell>> m_TileGrid;
    std::vector<Tile*> m_ToSort;

    std::vector<PendingChange> m_PendingList;
};