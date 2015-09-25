#pragma once

class Application
{
public:
	Application();

	void run();

private:
	void processInput();
	void update(sf::Time ft);
	void render();

private:
	sf::RenderWindow m_Window;
};