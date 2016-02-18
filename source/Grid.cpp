#include "Grid.hpp"
#include <cassert>

Grid::Grid(unsigned int numCells) noexcept
{
    resize(numCells);
    clear();
}

void Grid::clear() noexcept
{
    for (auto col(0u); col < m_NumCells; col++)
    {
        for (auto row(0u); row < m_NumCells; row++)
            m_Cells[col][row] = 0;
    }
}

void Grid::resize(unsigned int numCells) noexcept
{
    assert(numCells > 1);
    m_NumCells = numCells;

    m_Cells.resize(numCells);
    for (auto col(0u); col < numCells; col++)
        m_Cells[col].resize(numCells);
}

void Grid::rotate(int times) noexcept
{
    for (; times > 0; times--)
    {
        for (auto i(0); i < m_NumCells; i++)
        {
            for (auto j(i+1); j < m_NumCells; j++)
                std::swap(m_Cells[i][j], m_Cells[j][i]);
        }

        for (auto i(0); i < m_NumCells; i++)
        {
            for (auto j(0); j < m_NumCells/2; j++)
                std::swap(m_Cells[i][j], m_Cells[i][m_NumCells-1-j]);
        }
    }
}

bool Grid::isWithinBounds(const Vec2u& pos) const noexcept
{
    return pos.x < m_NumCells && pos.y < m_NumCells;
}

bool Grid::isWithinBounds(unsigned int col, unsigned int row) const noexcept
{
    return isWithinBounds({col, row});
}

void Grid::getFreeCells(std::vector<Vec2u>& freeCells) const noexcept
{
    freeCells.reserve(m_NumCells*m_NumCells);
    for (auto col(0u); col < m_NumCells; col++)
    {
        for (auto row(0u); row < m_NumCells; row++)
        {
            if (m_Cells[col][row] == 0)
                freeCells.emplace_back(col, row);
        }
    }
}

bool Grid::hasFreeCells() const noexcept
{
    std::vector<Vec2u> freeCells;
    getFreeCells(freeCells);
    return freeCells.size() > 0;
}

int Grid::getCell(const Vec2u& pos) const noexcept
{
    assert(isWithinBounds(pos));
    return m_Cells[pos.x][pos.y];
}

int Grid::getCell(unsigned int col, unsigned int row) const noexcept
{
    return getCell({col, row});
}

bool Grid::isCellEmpty(unsigned int col, unsigned int row) const noexcept
{
    return getCell(col, row) == 0;
}

bool Grid::hasAnyValueInColumn(int col, int startRow) const noexcept
{
    assert(isWithinBounds(col, startRow));

    for (auto y(startRow); y < m_NumCells; y++)
    {
        if (m_Cells[col][y] != 0)
            return true;
    }

    return false;
}

void Grid::setCell(const Vec2u& pos, int value) noexcept
{
    assert(isWithinBounds(pos));
    m_Cells[pos.x][pos.y] = value;
}

void Grid::setCell(unsigned int col, unsigned int row, int value) noexcept
{
    setCell({col, row}, value);
}

void Grid::increaseCell(unsigned int col, unsigned int row) noexcept
{
    assert(isWithinBounds(col, row));
    m_Cells[col][row] *= 2;
}

unsigned int Grid::getNumCells() const noexcept
{
    return m_NumCells;
}

void Grid::print()
{
    for (auto row(0); row < m_NumCells; row++) {
        for (auto col(0); col < m_NumCells; col++) {
            if (m_Cells[col][row] == 0) std::cout << "- ";
            else std::cout << m_Cells[col][row] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}