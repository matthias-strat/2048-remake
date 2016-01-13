#include "Game.hpp"

Game::Game()
    : m_Game{"2048", windowWidth, windowHeight},
      m_Window{m_Game.getWindow()}
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
}

void Game::onEvent(const sf::Event& event)
{
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
}
