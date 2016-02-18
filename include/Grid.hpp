#pragma once
#include "Common.hpp"

class Tile;

// Implements the logic for the game grid.
class Grid
{
public:
    explicit Grid(unsigned int numCells = defaultNumCells) noexcept;
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    void clear() noexcept;
    void resize(unsigned int numCells) noexcept;
    void rotate(int times = 1) noexcept;

    bool isWithinBounds(const Vec2u& pos) const noexcept;
    bool isWithinBounds(unsigned int col, unsigned int row) const noexcept;

    void getFreeCells(std::vector<Vec2u>& freeCells) const noexcept;
    bool hasFreeCells() const noexcept;

    int getCell(const Vec2u& pos) const noexcept;
    int getCell(unsigned int col, unsigned int row) const noexcept;

    bool isCellEmpty(unsigned int col, unsigned int row) const noexcept;
    bool hasAnyValueInColumn(int col, int startRow) const noexcept;

    void setCell(const Vec2u& pos, int value) noexcept;
    void setCell(unsigned int col, unsigned int row, int value) noexcept;

    void increaseCell(unsigned int col, unsigned int row) noexcept;

    unsigned int getNumCells() const noexcept;

    void print();

private:
    unsigned int m_NumCells;

    std::vector<std::vector<int>> m_Cells;
};
