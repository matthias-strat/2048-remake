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
constexpr unsigned int windowWidth{1024};
constexpr unsigned int windowHeight{768};

constexpr unsigned int defaultWindowWidth{1024};
constexpr unsigned int defaultWindowHeight{768};
constexpr unsigned int defaultNumCells{4}; // Default number of cells in the grid (x and y always the same)
constexpr unsigned int defaultSpacing{14}; // Default spacing between the cells (in pixels)
constexpr unsigned int defaultTileSize{110}; // Default size of the cells and tiles (in pixels)
constexpr float defaultVelMult{1.f}; // Default velocity multiplier when moving tiles.

// Number of maximum move tasks.
constexpr int maxMoveQueue{5};

// Number of starting tiles
constexpr int numStartTiles{2};

// Directory constants
const std::string fontDirectory{"assets/fonts"};
const std::string schemeDirectory{"assets/schemes"};

// Configuration file path
const std::string configFile{"save/config.json"};

// Default scheme file
const std::string defaultScheme{"default.json"};

// Specifies the difficulty of the game
enum class Difficulty
{
    // Enables unlimited un-dos.
    Practice,
    // Enabled 4 un-dos.
    Easy,
    // Classic gameplay, no un-dos
    Normal
};

// Specifies the current state of the game
enum class GameState
{
    InMenu,
    InGame
};

// Safely invoke an std::function (check if null before invoking)
template <typename TFunc, typename... TArgs>
inline static void safeInvoke(TFunc& func, TArgs&&... args)
{
    if (func != nullptr) func(std::forward<TArgs>(args)...);
}

template <typename T1, typename T2, typename T3>
inline constexpr Common<T1, T2, T3> calculateGridSize(T1 numCells, T2 cellSize, T3 spacing)
{
    return (numCells * cellSize) + ((numCells + 1) * spacing);
}

constexpr float defaultGridSize{static_cast<float>(calculateGridSize(defaultNumCells, defaultTileSize, defaultSpacing))};

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

template <typename TFunc, typename... TArgs>
inline void measureFunction(const std::string& desc, const TFunc& func, TArgs&&... args)
{
    auto tp1(HRClock::now());
    func(FWD(args)...);
    auto tp2(HRClock::now());
    auto elapsedMs(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count());
    std::cout << desc << "() took " << elapsedMs << " ms\n";
}