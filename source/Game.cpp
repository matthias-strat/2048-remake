#include "Game.hpp"
#include "Easing.hpp"

Game::Game()
    : m_Game{"2048", windowWidth, windowHeight},
      m_Window{m_Game.getWindow()},
      m_Assets{m_Config},
      m_TestTile{m_Assets}
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
    m_TestTile.increaseValue();
}

void Game::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Resized) onResize(event.size.width, event.size.height);
}

void Game::onUpdateFixed(float ft)
{
}

void Game::onUpdateVariable(float ft)
{
}

void Game::onFpsUpdated(int fps)
{
}

void Game::onDraw(sf::RenderTarget& target)
{
    m_Window.draw(m_Grid);
    m_Window.draw(m_TestTile);
}

void Game::onResize(unsigned width, unsigned height)
{
    // Fix view
    m_Window.setView(sf::View{{0.f, 0.f, static_cast<float>(width), static_cast<float>(height)}});

    // Center grid again
    m_Grid.setPosition(static_cast<float>(width/2), static_cast<float>(height/2));
}
