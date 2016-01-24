#pragma once
#include "Common.hpp"

// Simple class to separate input, update and window logic from game logic
class GameBase
{
public:
    std::function<void()> onLoadContent{nullptr};
    std::function<void(const sf::Event&)> onEvent{nullptr};
    std::function<void(float ft)> onUpdateFixed{nullptr}, onUpdateVariable{nullptr};
    std::function<void(int)> onFpsUpdated{nullptr};
    std::function<void(sf::RenderTarget&)> onDraw{nullptr};

public:
    explicit GameBase(const std::string& windowTitle, unsigned int windowWidth = 1024, unsigned int windowHeight = 768) noexcept;
    GameBase(const GameBase&) = delete;
    GameBase& operator=(const GameBase&) = delete;

    void run();

    sf::RenderWindow& getWindow() noexcept;
    const sf::RenderWindow& getWindow() const noexcept;

    void setClearColor(const sf::Color& color) noexcept;

    auto getWindowWidth() const noexcept;
    auto getWindowHeight() const noexcept;

private:
    void updateFpsCounter(sf::Time dt) noexcept;

    // Safely invoke an std::function (check if null before invoking)
    template <typename TFunc, typename... TArgs>
    inline static void safeInvoke(TFunc& func, TArgs&&... args)
    {
        if (func != nullptr) func(std::forward<TArgs>(args)...);
    }

private:
    sf::RenderWindow m_Window;
    std::string m_WindowTitle;
    unsigned int m_WindowWidth, m_WindowHeight;

    sf::Color m_ClearColor{sf::Color::White};

    sf::Time m_FpsCounterTime{sf::Time::Zero};
    std::size_t m_FpsCounter{0};
};
