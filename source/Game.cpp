#include "Game.hpp"
#include "Easing.hpp"

namespace
{
    auto randomSeed(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 randomEngine{randomSeed};

    int randomInt(int exclusiveMax) noexcept
    {
        std::uniform_int_distribution<int> ui{0, exclusiveMax - 1};
        return ui(randomEngine);
    }
}

Game::Game()
    : m_Game{"2048", windowWidth, windowHeight},
      m_Window{m_Game.getWindow()},
      m_Assets{m_Config},
      m_TestTile{m_Assets},
      m_TestTile2{m_Assets}
{
    m_Game.onLoadContent = [this]()
        {
            onLoadContent();
        };
    m_Game.onEvent = [this](const sf::Event& e)
        {
            onEvent(e);
        };
    m_Game.onUpdateFixed = [this](float ft)
        {
            onUpdateFixed(ft);
        };
    m_Game.onUpdateVariable = [this](float dt)
        {
            onUpdateVariable(dt);
        };
    m_Game.onFpsUpdated = [this](int fps)
        {
            onFpsUpdated(fps);
        };
    m_Game.onDraw = [this](sf::RenderTarget& target)
        {
            onDraw(target);
        };
}

void Game::run()
{
    m_Game.run();
}

void Game::onLoadContent()
{
    m_Assets.load();
    m_Game.setClearColor(m_Assets.colBackground);

    m_GridSprite.setTexture(*m_Assets.txGrid);
    m_GridSprite.setPosition(windowWidth/2.f, windowHeight/2.f);
    m_GridSprite.setOrigin(defaultGridSize/2.f, defaultGridSize/2.f);

    auto posX(defaultWindowWidth/2-defaultGridSize/2+defaultSpacing+defaultTileSize/2.f);
    auto posY(defaultWindowHeight/2-defaultGridSize/2+defaultSpacing+defaultTileSize/2.f);
    m_TestTile.setPosition(posX, posY);
    m_TestTile.setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);
    //m_TestTile.increaseValue();
    //m_TestTile.setValue(64);

    m_TestTile2.setPosition(posX + defaultSpacing + defaultTileSize, posY + defaultSpacing * 2 + defaultTileSize*2);
    m_TestTile2.setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);
    m_TestTile2.setValue(4096);

    restart();
}

void Game::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Resized) onResize(event.size.width, event.size.height);

    if (event.type == sf::Event::KeyPressed)
    {
        using k = sf::Keyboard::Key;
        
        // Vertical movement
        if (event.key.code == k::W || event.key.code == k::Up)
            m_MoveDirection = MoveUp;
        else if (event.key.code == k::S || event.key.code == k::Down)
            m_MoveDirection = MoveDown;

        // Horizontal movement
        if (event.key.code == k::D || event.key.code == k::Right)
            m_MoveDirection = MoveRight;
        else if (event.key.code == k::A || event.key.code == k::Left)
            m_MoveDirection = MoveLeft;

        // Restart game
        if (event.key.code == k::R) m_Restart = true;
    }

}

void Game::onUpdateFixed(float ft)
{
    // Restart the game if requested.
    if (m_Restart)
    {
        restart();
        m_Restart = false;
    }

    // Check if we have to move tiles
    if (m_MoveDirection != MoveNone)
    {
        moveTiles();
        m_Grid.print();
        m_MoveDirection = MoveNone;
    }
}

void Game::onUpdateVariable(float dt)
{
}

void Game::onFpsUpdated(int fps)
{
}

void Game::onDraw(sf::RenderTarget& target)
{
    m_Window.draw(m_GridSprite);
    m_Window.draw(m_TestTile);
    m_Window.draw(m_TestTile2);
}

void Game::onResize(unsigned width, unsigned height)
{
    // Fix view
    m_Window.setView(sf::View{{0.f, 0.f, static_cast<float>(width), static_cast<float>(height)}});

    // Center grid again
    m_GridSprite.setPosition(static_cast<float>(width/2), static_cast<float>(height/2));
}

void Game::restart()
{
    std::cout << "Game::restart()\n";

    addStartTiles();

    m_Grid.print();
}

void Game::addRandomTile()
{
    std::vector<Vec2u> freeCells;
    m_Grid.getFreeCells(freeCells);
    if (freeCells.size() < 1) return;
    
    auto cell(freeCells[randomInt(static_cast<int>(freeCells.size()))]);
    auto value(randomInt(10) < 9 ? 2 : 4);

    m_Grid.setCell(cell, value);
}

void Game::addStartTiles()
{
    for (auto n(0); n < numStartTiles; n++)
        addRandomTile();
}

int Game::moveTilesUp()
{
    // Keep track of how many moves were made, so we can decide if we should spawn a new tile
    // (moves > 0) or not (moves = 0).
    auto moves(0);

    // Step 1: foreach column, iterate from top to bottom and find empty cell.
    for (auto col(0u); col < m_Grid.getNumCells(); col++)
    {
        for (auto row(0u); row < m_Grid.getNumCells() - 1; row++)
        {
            while(m_Grid.isCellEmpty(col, row) && m_Grid.hasAnyValueInColumn(col, row))
            {
                for (auto y(row); y < m_Grid.getNumCells() - 1; y++)
                {
                    m_Grid.setCell(col, y, m_Grid.getCell(col, y + 1));
                    m_Grid.setCell(col, y + 1, 0);
                }
                moves++;
            }
        }
    }

    // All empty spaces are now on the bottom side and all tiles are next to each other.
 
    // Step 2: foreach column, combine like tiles
    for (auto col(0u); col < m_Grid.getNumCells(); col++)
    {
        for (auto row(0u); row < m_Grid.getNumCells() - 1; row++)
        {
            // Check if value of current tile matches value of adjacent tile.
            if (!m_Grid.isCellEmpty(col, row) && 
                m_Grid.getCell(col, row) == m_Grid.getCell(col, row + 1))
            {
                // Move all tiles starting from the current cell to the top by one.
                for (auto y(row); y < m_Grid.getNumCells() - 1; y++)
                {
                    m_Grid.setCell(col, y, m_Grid.getCell(col, y + 1));
                    m_Grid.setCell(col, y + 1, 0);
                }

                // Increase value of current tile
                m_Grid.increaseCell(col, row);

                // TODO: add score here

                moves++;
            }
        }
    }

    return moves;
}

void Game::moveTiles()
{
    auto iter(moveMap.find(m_MoveDirection));
    if (iter == moveMap.end()) return;

    auto times(iter->second);

    m_Grid.rotate(times);
    auto moves(moveTilesUp());
    m_Grid.rotate(4 - times);

    // Check if moves were made, if so add a new tile!
    if (moves > 0) addRandomTile();
}