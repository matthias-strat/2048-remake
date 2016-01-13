#include "Tile.hpp"

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
    return m_Value *= 2;
}
