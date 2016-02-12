#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <random>
#include <chrono>

#include "Aliases.hpp"

#include <SFML/Graphics.hpp>

// Define some common constants used throughout the game
// TODO: Calculate grid size, tile size, spacing and positions based on screen resolution
constexpr unsigned int windowWidth{800};
constexpr unsigned int windowHeight{600};

constexpr unsigned int defaultWindowWidth{800};
constexpr unsigned int defaultWindowHeight{600};
constexpr unsigned int defaultNumCells{4}; // Default number of cells in the grid (x and y always the same)
constexpr unsigned int defaultSpacing{14}; // Default spacing between the cells (in pixels)
constexpr unsigned int defaultTileSize{110}; // Default size of the cells and tiles (in pixels)
constexpr float defaultVelMult{1.f}; // Default velocity multiplier when moving tiles.

// Directory constants
const std::string fontDirectory{"assets/fonts"};
const std::string schemeDirectory{"assets/schemes"};

// Configuration file path
const std::string configFile{"save/config.json"};

// Default scheme file
const std::string defaultScheme{"default.json"};

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

inline sf::Color toColor(const std::string& str) noexcept
{
    using namespace std;

    sf::Color color{0, 0, 0, 255};

    string parsed;
    stringstream stream(str);

    if (getline(stream, parsed, ',')) color.r = stoi(parsed);
    if (getline(stream, parsed, ',')) color.g = stoi(parsed);
    if (getline(stream, parsed, ',')) color.b = stoi(parsed);
    if (getline(stream, parsed, ',')) color.a = stoi(parsed);

    return color;
}

// Sets the components of a vector to zero.
template <typename T>
inline void nullify(Vec2<T>& vec) noexcept
{
    vec.x = vec.y = T(0);
}