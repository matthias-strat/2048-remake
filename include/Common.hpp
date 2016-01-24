#pragma once

#include <iostream>
#include <array>
#include "Aliases.hpp"

#include <SFML/Graphics.hpp>

// Define some common constants used throughout the game
// TODO: Calculate grid size, tile size, spacing and positions based on screen resolution
constexpr unsigned int windowWidth{1024};
constexpr unsigned int windowHeight{768};

constexpr unsigned int defaultWindowWidth{1024};
constexpr unsigned int defaultWindowHeight{768};

constexpr unsigned int defaultNumCells{4}; // Default number of cells in the grid (x and y always the same)
constexpr unsigned int defaultSpacing{14}; // Default spacing between the cells (in pixels)
constexpr unsigned int defaultTileSize{110}; // Default size of the cells and tiles (in pixels)
constexpr float defaultVelMult{1.f}; // Default velocity multiplier when moving tiles.

template <typename T1, typename T2, typename T3>
inline constexpr Common<T1, T2, T3> calculateGridSize(T1 numCells, T2 cellSize, T3 spacing)
{
    return (numCells * cellSize) + ((numCells + 1) * spacing);
}

constexpr float defaultGridSize{static_cast<float>(calculateGridSize(defaultNumCells, defaultTileSize, defaultSpacing))};

inline constexpr int get1DIndexFrom2D(int x, int y, int width) noexcept
{
    return y + x * width;
}
