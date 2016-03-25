#pragma once

#include "GameBase.hpp"
#include "Assets.hpp"
#include "Grid.hpp"
#include "TileManager.hpp"
#include "ScoreManager.hpp"

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
    void onFpsUpdated(int fps);
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& target);

    void onResize(unsigned int width, unsigned int height);

    void restart() noexcept;

    void addRandomTile() noexcept;
    void addStartTiles() noexcept;

    //int moveTilesUp();
    void moveTiles() noexcept;

    bool isGameOver() const noexcept;

private:
    GameBase m_Game;
    Config m_Config;
    sf::RenderWindow& m_Window;
    Assets m_Assets;

    sf::Sprite m_CursorSprite;

    bool m_Restart{false};

    Vec2i m_MoveDirection{0, 0};

    Grid m_Grid;
    sf::Sprite m_GridSprite;
    TileManager m_TileMgr;

    bool m_GridMoving{false};
    float m_GridMoveTime{0.f};
};