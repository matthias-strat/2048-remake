#include "Common.hpp"
#include "Tile.hpp"
#include "Assets.hpp"

Tile::Tile(Assets& assets) noexcept
    : m_Assets{assets}
{
    const auto ts(static_cast<float>(defaultTileSize));
    m_Vertices[0].position = {0.f, 0.f};
    m_Vertices[1].position = {ts, 0.f};
    m_Vertices[2].position = {ts, ts};
    m_Vertices[3].position = {0.f, ts};
    updateTexture();
}

bool Tile::getIsAlive() const noexcept
{
    return m_IsAlive;
}

void Tile::destroy() noexcept
{
    m_IsAlive = false;
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

void Tile::update(float ft)
{
    
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
