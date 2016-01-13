#include "Grid.hpp"

Grid::Grid(unsigned int numCells, unsigned int tileSize, unsigned int spacing) noexcept
    : m_NumCells{numCells},
      m_TileSize{tileSize},
      m_Spacing{spacing},
      m_Size{static_cast<float>(calculateGridSize(numCells, tileSize, spacing))}
{
    // Initialize cells
    m_Cells.resize(numCells * numCells);
    for (auto x(0u); x < numCells; ++x)
    {
        for (auto y(0u); y < numCells; ++y)
        {
            auto& c(m_Cells[get1DIndexFrom2D(x, y, numCells)]);
            c.position = {x, y};
        }
    }

    updateVertices();
}

float Grid::getSize() const noexcept
{
    return m_Size;
}

void Grid::setTexture(const sf::Texture& texture) noexcept
{
    m_Texture = &texture;
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_Texture != nullptr)
    {
        states.transform *= getTransform();
        states.texture = m_Texture;
        target.draw(m_Vertices, 4, sf::Quads, states);
    }
}

void Grid::updateVertices()
{
    // Positions
    m_Vertices[0].position = {0.f, 0.f};
    m_Vertices[1].position = {m_Size, 0.f};
    m_Vertices[2].position = {m_Size, m_Size};
    m_Vertices[3].position = {0.f, m_Size};

    // Texture coords
    m_Vertices[0].texCoords = {0.f, 0.f};
    m_Vertices[1].texCoords = {m_Size, 0.f};
    m_Vertices[2].texCoords = {m_Size, m_Size};
    m_Vertices[3].texCoords = {0.f, m_Size};
}
