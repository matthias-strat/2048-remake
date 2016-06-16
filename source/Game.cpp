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
      m_TileMgr{m_Assets, m_Grid.getSize()}
{
    m_Game.onLoadContent = [this]()
        {
            onLoadContent();
        };
    m_Game.onEvent = [this](const sf::Event& e)
        {
            onEvent(e);
        };
    m_Game.onUpdate = [this](float dt)
        {
            onUpdate(dt);
        };
    m_Game.onFpsUpdated = [this](int fps)
        {
            onFpsUpdated(fps);
        };
    m_Game.onDraw = [this](sf::RenderTarget& target)
        {
            onDraw(target);
        };
    m_Game.setCursorVisible(false);
}

void Game::run()
{
    m_Game.run();
}

void Game::onLoadContent()
{
    m_Assets.load();
    m_Game.setClearColor(m_Assets.colBackground);

    m_CursorSprite.setTexture(m_Assets.txCursor);

    Vec2f halfScreen{windowWidth/2.f, windowHeight/2.f};
    m_GridSprite.setTexture(*m_Assets.txGrid);
    m_GridSprite.setPosition(halfScreen*3.f);
    m_GridSprite.setOrigin(defaultGridSize/2.f, defaultGridSize/2.f);

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
            m_MoveDirection = {0, -1};
        else if (event.key.code == k::S || event.key.code == k::Down)
            m_MoveDirection = {0, 1};

        // Horizontal movement
        if (event.key.code == k::D || event.key.code == k::Right)
            m_MoveDirection = {1, 0};
        else if (event.key.code == k::A || event.key.code == k::Left)
            m_MoveDirection = {-1, 0};

        // Restart game
        if (event.key.code == k::R) m_Restart = true;

        if (event.key.code == k::Space) 
        {
            m_GridMoving = true;
            m_Grid.clear();
            m_TileMgr.clear();
        }
    }

}

void Game::onUpdate(float dt)
{
    if (m_IsFading)
    {
        Vec2f halfScreen{defaultWindowWidth/2.f, defaultWindowHeight/2.f};
        Vec2f start{halfScreen.x * 3.f, halfScreen.y};
        Vec2f end{halfScreen};

        auto x(easing::Bounce<float>::out(m_FadeTime, start.x, end.x - start.x, 1.f));
        if (m_FadeTime >= 1.f)
        {
            x = end.x;
            m_IsFading = false;
            m_FadeTime = 0.f;
        }
        else
            m_FadeTime += dt;

        m_GridSprite.setPosition(x, start.y);
    }
    else
    {
        m_TileMgr.update(dt);

        // Restart the game if requested.
        if (m_Restart)
        {
            restart();
            m_Restart = false;
        }

        // Check if we have to move tiles
        if (m_MoveDirection.x != 0 || m_MoveDirection.y != 0)
        {
            moveTiles();
            nullify(m_MoveDirection);
        }
    }

    m_CursorSprite.setPosition(m_Game.getCursorPosition());
}

void Game::onFpsUpdated(int fps)
{
}

void Game::onDraw(sf::RenderTarget& target)
{
    m_Window.draw(m_GridSprite);
    if (!m_IsFading)
        m_TileMgr.draw(target);
    m_Window.draw(m_CursorSprite);
}

void Game::onResize(unsigned width, unsigned height)
{
    // Fix view
    m_Window.setView(sf::View{{0.f, 0.f, static_cast<float>(width), static_cast<float>(height)}});

    // Center grid again
    m_GridSprite.setPosition(static_cast<float>(width/2), static_cast<float>(height/2));
}

void Game::onPlaygroundReady()
{

}

void Game::restart() noexcept
{
    m_TileMgr.clear();
    m_Grid.clear();
    addStartTiles();
}

void Game::addRandomTile() noexcept
{
    std::vector<Vec2i> freeCells;
    m_Grid.getFreeCells(freeCells);
    if (freeCells.size() < 1) return;
    
    auto freePos(freeCells[randomInt(static_cast<int>(freeCells.size()))]);
    auto value(randomInt(10) < 9 ? 2 : 4);

    //m_Grid.setCellValue(cell, value);
    //m_TileMgr.create(cell, value);

    m_Grid.setCellValue(freePos, value);
    m_TileMgr.create(freePos, value);
}

void Game::addStartTiles() noexcept
{
    for (auto n(0); n < numStartTiles; n++)
        addRandomTile();
}

void Game::moveTiles() noexcept
{
    // Keep track of how many moves were made, so we can decide if we should spawn a new tile or not.
    auto moves(0);

    // Prepare the grid cells (set merge flag to false)
    m_Grid.prepare();

    auto gridSize(static_cast<int>(m_Grid.getSize()));
    auto dirX(m_MoveDirection.x);
    auto dirY(m_MoveDirection.y);
    int col, row;

    // Loop through grid (based on direction of user input)
    // Explanation:
    // 
    // if direction is positive (== 1) loop from 3 to 0,
    // otherwise if direction is negative (== -1) loop from 0 to 3.
    // use "col" and "row"
    // "x" and "y" just for looping
    for (auto x(0), col = (dirX == 1 ? gridSize - 1 : 0); x < gridSize;
         x++, col = (dirX == 1 ? gridSize - x - 1 : x))
    {
        for (auto y(0), row = (dirY == 1 ? gridSize - 1 : 0); y < gridSize;
             y++, row = (dirY == 1 ? gridSize - y - 1 : y))
        {
            // Find empty slot:
            // curPos points to the current cell which should be moved
            // prevPos points to the empty cell
            // nextPos points to the cell next to the empty cell (not empty)
            //         can be out of grid bounds if there's not cell
            Vec2i curPos{col, row};
            Vec2i nextPos{col, row};
            Vec2i prevPos;

            do
            {
                prevPos = nextPos;
                nextPos = {prevPos.x + dirX, prevPos.y + dirY};
            }
            while (m_Grid.isWithinBounds(nextPos) &&
                   m_Grid.isCellEmpty(nextPos));
    
            // Get associated cells
            auto cell(m_Grid.getCell(col, row));

            // Check if this move can merge tiles (nextTile must be within bounds and not empty and
            // cell values have to match)
            if ((m_Grid.isWithinBounds(nextPos) && !m_Grid.isCellEmpty(nextPos)) &&
                (m_Grid.getCellValue(nextPos) == m_Grid.getCellValue(curPos) && 
                 !m_Grid.cellWasMerged(nextPos)))
            {
                m_Grid.mergeCells(curPos, nextPos);
                m_TileMgr.mergeTiles(curPos, nextPos);
            
                moves++;
            }
            else
            {
                // prevPos == curPos -> no moves available (first cell)
                if (prevPos == curPos) continue;
                if (m_Grid.isCellEmpty(prevPos) && m_Grid.isCellEmpty(curPos)) continue;

                m_Grid.setCellValue(prevPos, m_Grid.getCellValue(curPos));
                m_Grid.setCellValue(curPos, 0);

                m_TileMgr.moveTile(curPos, prevPos);

                moves++;
            }
        }
    }

    // Okay, moves were made, spawn a new tile.
    if (moves > 0) addRandomTile();
}