#pragma once

#include "GameBase.hpp"
#include "Assets.hpp"
#include "Grid.hpp"
#include "Tile.hpp"

#include <queue>

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

    void restart();

    void addRandomTile();
    void addStartTiles();

    int moveTilesUp();
    void moveTiles();

private:
    GameBase m_Game;
    Config m_Config;
    sf::RenderWindow& m_Window;
    Assets m_Assets;

    bool m_Restart{false};

    MoveDirection m_MoveDirection{MoveNone};

    Grid m_Grid;
    sf::Sprite m_GridSprite;
    Tile m_TestTile, m_TestTile2;
};