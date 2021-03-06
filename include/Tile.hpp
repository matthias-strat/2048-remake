#pragma once

#include <queue>

#include "Common.hpp"
#include "Task.hpp"

class TileManager;
class Assets;

class Tile : public sf::Drawable, public sf::Transformable
{
    // Share private members with TileManager class.
    friend class TileManager;

public:
    explicit Tile(Assets& assets, int value = 2) noexcept;

    int getValue() const noexcept;
    int increaseValue() noexcept;
    void setValue(int value) noexcept;

    template <typename TTask>
    void addTask(float start, float end, float duration, BaseTask::UpdateFunc updateFunc, BaseTask::CompleteFunc compeleteFunc = nullptr)
    {
        TTask task{start, end, duration, updateFunc, compeleteFunc};
        m_Tasks.push(task);
    }

    void update(float dt);

    void setDrawPriority(int priority) noexcept;
    int getDrawPriority() const noexcept;

private:
    void updateTexture();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isMarkedForRemoval() const noexcept;
    void markForRemoval() noexcept;

private:
    Assets& m_Assets;

    int m_Value;
    sf::Vertex m_Vertices[4];

    bool m_IsMarkedForRemoval{false};

    std::queue<BaseTask> m_Tasks;

    int m_DrawPriority{0};
};