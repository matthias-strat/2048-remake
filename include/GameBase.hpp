#pragma once
#include "Common.hpp"

// Simple class to separate input, update and window logic from game logic
class GameBase
{
public:
    Func<void()> onLoadContent{nullptr};
    Func<void(const sf::Event&)> onEvent{nullptr};
    Func<void(float)> onUpdate{nullptr};
    Func<void(int)> onFpsUpdated{nullptr};
    Func<void(sf::RenderTarget&)> onDraw{nullptr};

public:
    explicit GameBase(const std::string& windowTitle, unsigned int windowWidth = 1024, 
        unsigned int windowHeight = 768) noexcept;

    // Delete copy constructor and copy assignment operator.
    GameBase(const GameBase&) = delete;
    GameBase& operator=(const GameBase&) = delete;

    void run();

    sf::RenderWindow& getWindow() noexcept;
    const sf::RenderWindow& getWindow() const noexcept;

    void setCursorVisible(bool visible) noexcept;
    void setClearColor(const sf::Color& color) noexcept;

    Vec2f getCursorPosition() const noexcept;

    auto getWindowWidth() const noexcept;
    auto getWindowHeight() const noexcept;

private:
    void updateFpsCounter(sf::Time dt) noexcept;

private:
    sf::RenderWindow m_Window;
    std::string m_WindowTitle;
    unsigned int m_WindowWidth, m_WindowHeight;

    bool m_CursorVisible{true};
    sf::Color m_ClearColor{sf::Color::White};

    sf::Time m_FpsCounterTime{sf::Time::Zero};
    std::size_t m_FpsCounter{0};
};
