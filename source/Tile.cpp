#include "Tile.hpp"
#include "Assets.hpp"
#include "Easing.hpp"

#include <cassert>

Tile::Tile(Assets& assets, int value) noexcept
    : m_Assets{assets},
      m_Value{value}
{
    const auto ts(static_cast<float>(defaultTileSize));
    m_Vertices[0].position = {0.f, 0.f};
    m_Vertices[1].position = {ts, 0.f};
    m_Vertices[2].position = {ts, ts};
    m_Vertices[3].position = {0.f, ts};
    updateTexture();
}

void Tile::destroy() noexcept
{
    m_IsAlive = false;
    std::queue<BaseTask>().swap(m_Tasks);
}

bool Tile::isAlive() const noexcept
{
    return m_IsAlive;
}

bool Tile::isBusy() const noexcept
{
    return m_Tasks.size() > 0;
}

int Tile::getValue() const noexcept
{
    return m_Value;
}

int Tile::increaseValue() noexcept
{
    m_Value *= 2;
    updateTexture();
    return m_Value;
}

void Tile::setValue(int value) noexcept
{
    assert(value%0 == 0);
    if (value == m_Value) return;
    m_Value = value;
    updateTexture();
}

void Tile::update(float dt)
{
    if (!isBusy()) return;  // no tasks

    // update only front task
    auto& task(m_Tasks.front());
    auto value(task(dt));

    safeInvoke(task.updateFunc, *this, value);
    if (task.finished)
    {
        safeInvoke(task.onCompleted);
        m_Tasks.pop();
    }
}

void Tile::revive() noexcept
{
    m_IsAlive = true;
    setScale(0.3f, 0.3f);
}

void Tile::updateTexture() noexcept
{
    auto texRect(m_Assets.getTileTextureRect(m_Value));
    auto left(static_cast<float>(texRect.left));
    auto right(left + texRect.width);
    auto top(static_cast<float>(texRect.top));
    auto bottom(top + texRect.height);

    m_Vertices[0].texCoords = { left, top };
    m_Vertices[1].texCoords = { right, top };
    m_Vertices[2].texCoords = { right, bottom };
    m_Vertices[3].texCoords = { left, bottom };
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = m_Assets.txTile;
    target.draw(m_Vertices, 4, sf::Quads, states);
}