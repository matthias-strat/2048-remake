#include "GameBase.hpp"

GameBase::GameBase(const std::string& windowTitle, unsigned windowWidth, unsigned windowHeight) noexcept
    : m_Window{{windowWidth, windowHeight}, windowTitle, sf::Style::Close},
      m_WindowWidth{windowWidth},
      m_WindowHeight{windowHeight}
{
    m_Window.setVerticalSyncEnabled(true);
}

void GameBase::run()
{
    safeInvoke(onLoadContent);
    safeInvoke(onFpsUpdated, 0);

    // Integrate at 60Hz
    static const auto timeStep(sf::seconds(1.f / 60.f));

    auto accumulator(sf::Time::Zero);
    sf::Clock clock;

    while (m_Window.isOpen())
    {
        auto dt(clock.restart());
        accumulator += dt;

        sf::Event event;
        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_Window.close();
            safeInvoke(onEvent, event);
        }

        while (accumulator >= timeStep)
        {
            accumulator -= timeStep;
            safeInvoke(onUpdateFixed, timeStep.asSeconds());
        }

        updateFpsCounter(dt);
        safeInvoke(onUpdateVariable, dt.asSeconds());

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

void GameBase::setClearColor(const sf::Color& color) noexcept
{
    m_ClearColor = color;
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