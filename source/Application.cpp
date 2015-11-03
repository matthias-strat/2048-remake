#include "Pch.hpp"
#include "Application.hpp"
#include <States/MenuState.hpp>
#include <States/GameState.hpp>
#include <iostream>

Application::Application(Configuration& config)
    : m_Config{config},
    m_StateStack{ {m_Window, m_Textures, m_Fonts, m_Config} },
    m_FpsCounterTime{ sf::Time::Zero },
    m_FpsCounterNum{ 0 }
{
    m_Fonts.load(Fonts::Verdana, "C:/Windows/Fonts/verdana.ttf");
    m_Fonts.load(Fonts::Sansation, "assets/Sansation_Regular.ttf");

    sf::Clock clock;
    loadTextures();
    auto elapsed{ clock.getElapsedTime() };
    std::cout << "Application::ctor() -> loadTextures() took " << elapsed.asMilliseconds() << " ms" << std::endl;

    m_FpsCounterText.setFont(m_Fonts.get(Fonts::Sansation));
    m_FpsCounterText.setString("FPS: 0");
    m_FpsCounterText.setPosition(3.f, 3.f);
    m_FpsCounterText.setColor({ 119, 110, 101 });
    m_FpsCounterText.setCharacterSize(14u);

    // All global resources loaded, create and configure the window now
    m_Window.create({ config.getVideoWidth(), config.getVideoHeight() }, "2048 Puzzle", sf::Style::Close, sf::ContextSettings{ 0, 0, config.getAntialiasing() });
    m_Window.setVerticalSyncEnabled(true);
    m_Window.setKeyRepeatEnabled(false);

    registerStates();
    m_StateStack.pushState(StateId::Menu);
}

void Application::run()
{
    static const sf::Time timePerFrame{ sf::seconds(1.f / 60.f) };
    sf::Clock clock;
    sf::Time timeSinceLastUpdate{ sf::Time::Zero };
	
    while (m_Window.isOpen())
    {
        auto dt{ clock.restart() };
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            processInput();
            update(timePerFrame);

            // Close the window when no states left in the state stack
            if (m_StateStack.isEmpty()) m_Window.close();
        }

        updateFpsCounter(dt);
        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))	// loop until we don't have any pending events anymore
    {
        // check if FPS counter show/hide key was pressed
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1) toggleShowFps();

        // forward event to the state stack
        m_StateStack.handleEvent(event);

        // Check for window close event. When closed event was received, close the window explicitly.
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
            break;
        }
    }
}

void Application::update(sf::Time ft)
{
    m_StateStack.update(ft);
}

void Application::updateFpsCounter(sf::Time dt)
{
    // Count FPS and update it each second
    static const sf::Time oneSecond{ sf::seconds(1) };
    m_FpsCounterTime += dt;
    m_FpsCounterNum++;
    if (m_FpsCounterTime >= oneSecond)
    {
        m_FpsCounterTime -= oneSecond;
        m_FpsCounterText.setString("FPS: " + std::to_string(m_FpsCounterNum));
        m_FpsCounterNum = 0;
    }
}

void Application::render()
{
    static const sf::Color clearColor{ 250, 248, 239 };

    // Clear the entire screen and fill it with the specified clearColor.
    m_Window.clear(clearColor);
    m_StateStack.draw();
    if (m_Config.getShowFps()) m_Window.draw(m_FpsCounterText);
    m_Window.display();
}

void Application::toggleShowFps()
{
    auto showFps{ m_Config.getShowFps() };
    m_Config.setShowFps(!showFps);
}

void Application::registerStates()
{
    m_StateStack.registerState<MenuState>(StateId::Menu);
    m_StateStack.registerState<GameState>(StateId::Game);
}

void Application::loadTextures()
{
    // Load all textures globally at application start up since we only need a few textures
    m_Textures.load(Textures::Resize, "assets/resize.png");
    m_Textures.load(Textures::Tiles, "assets/tiles.png");
    m_Textures.load(Textures::Grid, "assets/grid.png");
    m_Textures.load(Textures::Menu, "assets/menu.png");
    m_Textures.load(Textures::MenuButton, "assets/menu_button.png");
    m_Textures.load(Textures::Scoreboard, "assets/scoreboard.png");
}