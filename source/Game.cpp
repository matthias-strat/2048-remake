#include "Game.hpp"
#include "Easing.hpp"

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

    m_Grid.setTexture(*m_Assets.txGrid);
    m_Grid.setPosition(windowWidth / 2.f, windowHeight / 2.f);
    m_Grid.setOrigin(m_Grid.getSize() / 2.f, m_Grid.getSize() / 2.f);

    auto posX(defaultWindowWidth/2-defaultGridSize/2+defaultSpacing+defaultTileSize/2.f);
    auto posY(defaultWindowHeight/2-defaultGridSize/2+defaultSpacing+defaultTileSize/2.f);
    m_TestTile.setPosition(posX, posY);
    m_TestTile.setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);
    //m_TestTile.increaseValue();
    //m_TestTile.setValue(64);

    m_TestTile2.setPosition(posX + defaultSpacing + defaultTileSize, posY + defaultSpacing * 2 + defaultTileSize*2);
    m_TestTile2.setOrigin(defaultTileSize/2.f, defaultTileSize/2.f);
    m_TestTile2.setValue(4096);    
}

void Game::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Resized) onResize(event.size.width, event.size.height);

    if (event.type == sf::Event::KeyPressed)
    {
        using k = sf::Keyboard::Key;
        
        // Vertical movement
        if (event.key.code == k::W || event.key.code == k::Up)
            m_MoveDirection.y = 1;
        else if (event.key.code == k::S || event.key.code == k::Down)
            m_MoveDirection.y = -1;

        // Horizontal movement
        if (event.key.code == k::D || event.key.code == k::Right)
            m_MoveDirection.x = 1;
        else if (event.key.code == k::A || event.key.code == k::Left)
            m_MoveDirection.x = -1;

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
    if (m_MoveDirection.x != 0 || m_MoveDirection.y != 0)
    {

        nullify(m_MoveDirection);
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
    m_Window.draw(m_Grid);
    m_Window.draw(m_TestTile);
    m_Window.draw(m_TestTile2);
}

void Game::onResize(unsigned width, unsigned height)
{
    // Fix view
    m_Window.setView(sf::View{{0.f, 0.f, static_cast<float>(width), static_cast<float>(height)}});

    // Center grid again
    m_Grid.setPosition(static_cast<float>(width/2), static_cast<float>(height/2));
}

void Game::restart()
{
    std::cout << "Game::restart()\n";
}