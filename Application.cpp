#include "stdafx.h"
#include "Application.hpp"

Application::Application()
	: m_Window{ {1280, 760}, "2048 Puzzle", sf::Style::Close }
{
	m_Window.setVerticalSyncEnabled(true);
	m_Window.setKeyRepeatEnabled(false);
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
		}

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (m_Window.pollEvent(event))	// loop until we don't have any pending events anymore
	{
		// Check for window close event. When closed event was received, close the window explicitly.
		if (event.type == sf::Event::Closed) m_Window.close();
	}
}


void Application::update(sf::Time ft)
{
}

void Application::render()
{
	static const sf::Color clearColor{ sf::Color::White };

	// Clear the entire screen with the given clear color.
	m_Window.clear(clearColor);

	m_Window.display();
}

