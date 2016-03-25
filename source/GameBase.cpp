#include "GameBase.hpp"

GameBase::GameBase(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight) noexcept
    : m_WindowTitle{windowTitle},
      m_WindowWidth{windowWidth},
      m_WindowHeight{windowHeight}
{
}

void GameBase::run()
{
    safeInvoke(onLoadContent);
    safeInvoke(onFpsUpdated, 0);

    m_Window.create({ m_WindowWidth, m_WindowHeight }, m_WindowTitle, sf::Style::Default);
    m_Window.setVerticalSyncEnabled(true);
    m_Window.setKeyRepeatEnabled(false);
    m_Window.setMouseCursorVisible(m_CursorVisible);

    sf::Clock clock;
    while (m_Window.isOpen())
    {
        auto dt(clock.restart());

        sf::Event event;
        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_Window.close();
            if (event.type == sf::Event::Resized)
            {
                m_WindowWidth = event.size.width;
                m_WindowHeight = event.size.height;
            }
            safeInvoke(onEvent, event);
        }

        updateFpsCounter(dt);
        safeInvoke(onUpdate, dt.asSeconds());
    
        m_Window.clear(m_ClearColor);
        safeInvoke(onDraw, m_Window);
        m_Window.display();
    }
}

sf::RenderWindow& GameBase::getWindow() noexcept
{
    return m_Window;
}

const sf::RenderWindow& GameBase::getWindow() const noexcept
{
    return m_Window;
}

void GameBase::setCursorVisible(bool visible) noexcept
{
    m_CursorVisible = visible;
}

void GameBase::setClearColor(const sf::Color& color) noexcept
{
    m_ClearColor = color;
}

Vec2f GameBase::getCursorPosition() const noexcept
{
    return m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
}

auto GameBase::getWindowWidth() const noexcept
{
    return m_WindowWidth;
}

auto GameBase::getWindowHeight() const noexcept
{
    return m_WindowHeight;
}

void GameBase::updateFpsCounter(sf::Time dt) noexcept
{
    static const auto oneSecond(sf::seconds(1.f));
    m_FpsCounterTime += dt;
    m_FpsCounter++;
    if (m_FpsCounterTime >= oneSecond)
    {
        m_FpsCounterTime -= oneSecond;
        safeInvoke(onFpsUpdated, m_FpsCounter);
        m_FpsCounter = 0;
    }
}
