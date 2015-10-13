#pragma once

#include "Configuration.hpp"
#include "StateStack.hpp"

class Application
{
public:
	Application(Configuration& config);

	void run();

private:
	void processInput();
	void update(sf::Time ft);
	void updateFpsCounter(sf::Time dt);
	void render();

	void toggleShowFps();

	void registerStates();
	void loadTextures();

private:
	Configuration& m_Config;
	sf::RenderWindow m_Window;

	StateStack m_StateStack;

	FontHolder m_Fonts;
	TextureHolder m_Textures;

	sf::Text m_FpsCounterText;
	sf::Time m_FpsCounterTime;
	std::size_t m_FpsCounterNum;
};