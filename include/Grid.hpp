#pragma once
#include "Common.hpp"

class Tile;

class Grid
{
public:
    struct Cell
    {
        // the value of the cell (0 = empty)
        int value{0};

        // A bool indicating whether this cell was already merged in the current move.
        // This prevents multiple merges in a single move (2 2 4 4 > 4 4 4 - > 8 4 - - )
        bool merged{false};
    };

public:
    explicit Grid(unsigned int size = defaultNumCells) noexcept;
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    void clear() noexcept;
    void resize(unsigned int size) noexcept;
    void prepare() noexcept;

    bool isWithinBounds(const Vec2i& pos) const noexcept;
    bool isWithinBounds(int col, int row) const noexcept;

    void getFreeCells(std::vector<Vec2i>& freeCells) const noexcept;
    bool hasFreeCells() const noexcept;

    const Cell& getCell(const Vec2i& pos) const noexcept;
    Cell& getCell(const Vec2i& pos) noexcept;

    const Cell& getCell(int col, int row) const noexcept;
    Cell& getCell(int col, int row) noexcept;

    int getCellValue(const Vec2i& pos) const noexcept;
    int getCellValue(int col, int row) const noexcept;

    void mergeCells(const Vec2i& from, const Vec2i& to) noexcept;

    bool isCellEmpty(const Vec2i& pos) const noexcept;
    bool isCellEmpty(int col, int row) const noexcept;

    bool cellWasMerged(const Vec2i& pos) const noexcept;

    void setCellValue(const Vec2i& pos, int value) noexcept;
    void setCellValue(int col, int row, int value) noexcept;
    void increaseCellValue(const Vec2i& pos) noexcept;

    unsigned int getSize() const noexcept;

private:
    unsigned int m_Size;
    std::vector<std::vector<Cell>> m_Cells;
};