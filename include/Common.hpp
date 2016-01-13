#pragma once

#include <iostream>
#include <chrono>
#include <memory>
#include <functional>
#include <array>

#include <SFML/Graphics.hpp>

// STL shortcuts
using HRClock = std::chrono::high_resolution_clock;
template <typename T>
using UPtr = std::unique_ptr<T>;

// SFML shortcuts
template <typename T>
using Vec2 = sf::Vector2<T>;
using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;

// Define some common constants used throughout the game
// TODO: Calculate grid size, tile size, spacing and positions based on screen resolution
constexpr unsigned int windowWidth{1024};
constexpr unsigned int windowHeight{768};

// old
constexpr unsigned int numTiles{4}; // Number of tiles (x, y always the same)
constexpr unsigned int spacing{14}; // Spacing between the tiles (in tiles)
constexpr unsigned int tileSize{110}; // Size of the tiles (in pixels)
constexpr float velocityMult{1.f}; // Velocity multiplier of the tiles

// Calculates the total size of the grid (in pixels)
inline constexpr unsigned int calculateGridSize()
{
    return (numTiles * tileSize) + ((numTiles + 1) * spacing);
}

constexpr float gridSize{static_cast<float>(calculateGridSize())};

constexpr unsigned int defaultNumCells{4}; // Default number of cells in the grid (x and y always the same)
constexpr unsigned int defaultSpacing{14}; // Default spacing between the cells (in pixels)
constexpr unsigned int defaultTileSize{110}; // Default size of the cells and tiles (in pixels)
constexpr float defaultVelMult{1.f}; // Default velocity multiplier when moving tiles.

template <typename T1, typename T2, typename T3>
inline constexpr std::common_type_t<T1, T2, T3> calculateGridSize(T1 numCells, T2 cellSize, T3 spacing)
{
    return (numCells * cellSize) + ((numCells + 1) * spacing);
}

constexpr float defaultGridSize{static_cast<float>(calculateGridSize(defaultNumCells, defaultTileSize, defaultSpacing))};

template <typename T>
inline constexpr float toWorldPosition(T value) noexcept
{
    return (static_cast<float>(value) * tileSize) + ((static_cast<float>(value) + 1) * spacing);
}

template <typename T>
inline constexpr Vec2f toWorldPosition(const Vec2<T>& value) noexcept
{
    return Vec2f{static_cast<float>(toWorldPosition(value.x)), static_cast<float>(toWorldPosition(value.y))};
}

inline constexpr int get1DIndexFrom2D(int x, int y, int width) noexcept
{
    return y + x * width;
}
