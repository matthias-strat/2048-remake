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
    m_Vertices[1].position = {ts , 0.f};
    m_Vertices[2].position = {ts , ts};
    m_Vertices[3].position = {0.f, ts};
    updateTexture();
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
    assert(value%2==0);
    if (m_Value == value) return;
    m_Value = value;
    updateTexture();
}

void Tile::update(float dt)
{
    if (m_Tasks.size() == 0) return;

    // update only front task
    auto& task(m_Tasks.front());
    auto value(task(dt));

    safeInvoke(task.updateFunc, *this, value);
    if (task.finished)
    {
        safeInvoke(task.onCompleted, *this);
        m_Tasks.pop();
    }
}

void Tile::setDrawPriority(int priority) noexcept
{
    m_DrawPriority = priority;
}

int Tile::getDrawPriority() const noexcept
{
    return m_DrawPriority;
}

void Tile::updateTexture()
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

bool Tile::isMarkedForRemoval() const noexcept
{    return m_IsMarkedForRemoval;
}

void Tile::markForRemoval() noexcept
{
    m_IsMarkedForRemoval = true;
}