#pragma once

#include "GameBase.hpp"
#include "Assets.hpp"
#include "Grid.hpp"

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
    sf::RenderWindow& m_Window;
    Assets m_Assets;

    Grid m_Grid;
};
