#pragma once

class TileManager;

class Tile
{
    friend class TileManager;

public:
    bool getIsAlive() const noexcept;
    void destroy() noexcept;

    int getValue() const noexcept;
    int increaseValue() noexcept;

private:
    bool m_IsAlive{false};
    int m_Value{2};
};
