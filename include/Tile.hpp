#pragma once

#include <queue>

#include "Common.hpp"
#include "Task.hpp"

class TileManagerNew;
class TileManager;
class Assets;

class NewTile : public sf::Drawable, public sf::Transformable
{
    friend class TileManager;

public:
    NewTile(TileManager& tileMgr, Assets& assets, int value = 2) noexcept;

    void destroy() noexcept;
    bool isAlive() const noexcept;

private:
    void revive();

private:
    TileManager& m_TileMgr;
    Assets& m_Assets;

    int m_Value;
    sf::Vertex m_Vertices[4];

    bool m_IsAlive{false};
};

class Tile : public sf::Drawable, public sf::Transformable
{
    friend class TileManager;
    friend class TileManagerNew;

public:
    explicit Tile(Assets& assets, int value = 2) noexcept;

    // destroys the tile (also kills all tasks)
    void destroy() noexcept;
    bool isAlive() const noexcept;
    bool isBusy() const noexcept;

    int getValue() const noexcept;
    int increaseValue() noexcept;
    void setValue(int value) noexcept;

    template <typename TTask, typename... TArgs>
    void addTask(TArgs&&... args)
    {
        TTask task{FWD(args)...};
        m_Tasks.push(task);
    }

    template <typename TTask, typename... TArgs>
    void addTask(TArgs&&... args, Func<void()> onCompleted)
    {
        TTask task{FWD(args)..., onCompleted};
        m_Tasks.push(task);
    }

    void update(float dt);

private:
    void revive() noexcept;
    void updateTexture() noexcept;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Assets& m_Assets;

    int m_Value;
    sf::Vertex m_Vertices[4];

    bool m_IsAlive{false};

    std::queue<BaseTask> m_Tasks;
};