#pragma once

#include "GameBase.hpp"
#include "Assets.hpp"
#include "Grid.hpp"
#include "Tile.hpp"

class Game
{
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run();

private:
    void onLoadContent();
    void onEvent(const sf::Event& event);
    void onUpdateFixed(float ft);
    void onUpdateVariable(float ft);
    void onFpsUpdated(int fps);
    void onDraw(sf::RenderTarget& target);

    void onResize(unsigned int width, unsigned int height);

private:
    GameBase m_Game;
    Config m_Config;
    sf::RenderWindow& m_Window;
    Assets m_Assets;

    Grid m_Grid;
    Tile m_TestTile, m_TestTile2;
    float m_Test{0.f};
};
