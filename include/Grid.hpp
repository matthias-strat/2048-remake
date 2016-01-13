#pragma once
#include "Common.hpp"

// Represents the ingame grid. This class combines both draw and game logic (is this a bad approach?)
class Grid : public sf::Drawable, public sf::Transformable
{
public:
    // Represents a cell inside a grid.
    struct Cell
    {
        // A value indicating whether this cell is empty.
        bool isEmpty{true};

        // The position of the cell in the grid.
        Vec2u position;

        // The position of the cell in the world (render position)
        Vec2f worldPosition;
    };

public:
    explicit Grid(unsigned int numCells = defaultNumCells, unsigned int tileSize = defaultTileSize, unsigned int spacing = defaultSpacing) noexcept;
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    float getSize() const noexcept;

    void setTexture(const sf::Texture& texture) noexcept;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateVertices();

private:
    unsigned int m_NumCells, m_TileSize, m_Spacing;
    float m_Size;

    sf::Vertex m_Vertices[4];
    const sf::Texture* m_Texture{nullptr};
    std::vector<Cell> m_Cells;
};
