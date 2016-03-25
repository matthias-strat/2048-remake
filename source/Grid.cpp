#include "Grid.hpp"
#include <cassert>

Grid::Grid(unsigned int size) noexcept
{
    resize(size);
}

void Grid::clear() noexcept
{
    for (auto col(0); col < m_Size; col++)
    {
        for (auto row(0); row < m_Size; row++)
            m_Cells[col][row].value = 0;
    }
}

void Grid::resize(unsigned int size) noexcept
{
    assert(size > 1);
    m_Size = size;

    m_Cells.resize(size);
    for (auto col(0); col < size; col++)
        m_Cells[col].resize(size);
}

void Grid::prepare() noexcept
{
    for (auto col(0); col < m_Size; col++)
    {
        for (auto row(0); row < m_Size; row++)
            m_Cells[row][col].merged = false;
    }
}

bool Grid::isWithinBounds(const Vec2i& pos) const noexcept
{
    return (pos.x >= 0 && pos.x < m_Size) && (pos.y >= 0 && pos.y < m_Size);
}

bool Grid::isWithinBounds(int col, int row) const noexcept
{
    return isWithinBounds({col, row});
}

void Grid::getFreeCells(std::vector<Vec2i>& freeCells) const noexcept
{
    freeCells.reserve(m_Size*m_Size);
    for (auto col(0u); col < m_Size; col++)
    {
        for (auto row(0u); row < m_Size; row++)
        {
            if (m_Cells[col][row].value == 0)
                freeCells.emplace_back(col, row);
        }
    }
}

bool Grid::hasFreeCells() const noexcept
{
    std::vector<Vec2i> freeCells;
    getFreeCells(freeCells);
    return freeCells.size() > 0;
}

const Grid::Cell& Grid::getCell(const Vec2i& pos) const noexcept
{
    assert(isWithinBounds(pos));
    return m_Cells[pos.x][pos.y];
}

Grid::Cell& Grid::getCell(const Vec2i& pos) noexcept
{
    assert(isWithinBounds(pos));
    return m_Cells[pos.x][pos.y];
}

const Grid::Cell& Grid::getCell(int col, int row) const noexcept
{
    return getCell({col, row});
}

Grid::Cell& Grid::getCell(int col, int row) noexcept
{
    return getCell({col, row});
}

int Grid::getCellValue(const Vec2i& pos) const noexcept
{
    assert(isWithinBounds(pos));
    return m_Cells[pos.x][pos.y].value;
}

int Grid::getCellValue(int col, int row) const noexcept
{
    return getCellValue({col, row});
}

void Grid::mergeCells(const Vec2i& from, const Vec2i& to) noexcept
{
    assert(isWithinBounds(from));
    assert(isWithinBounds(to));

    m_Cells[to.x][to.y].value *= 2;
    m_Cells[from.x][from.y].value = 0;
    m_Cells[to.x][to.y].merged = true;
}

bool Grid::isCellEmpty(const Vec2i& pos) const noexcept
{
    return getCellValue(pos) == 0;
}

bool Grid::isCellEmpty(int col, int row) const noexcept
{
    return isCellEmpty({col, row});
}

bool Grid::cellWasMerged(const Vec2i& pos) const noexcept
{
    return getCell(pos).merged;
}

void Grid::setCellValue(const Vec2i& pos, int value) noexcept
{
    assert(isWithinBounds(pos));
    m_Cells[pos.x][pos.y].value = value;
}

void Grid::setCellValue(int col, int row, int value) noexcept
{
    setCellValue({col, row}, value);
}

void Grid::increaseCellValue(const Vec2i& pos) noexcept
{
    assert(isWithinBounds(pos));
    m_Cells[pos.x][pos.y].value *= 2;
}

unsigned int Grid::getSize() const noexcept
{
    return m_Size;
}