#include "stdafx.h"

int main()
{
	// Draw a white (200x200) rectangle in the middle of a black screen.
	// Just to see if SFML actually works!

	sf::RectangleShape shape;
	shape.setPosition(1024.f*0.5f, 768.f*0.5f);
	shape.setSize({ 200.f, 200.f });
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(shape.getSize()*0.5f);

	sf::RenderWindow window{ {1024, 768}, "SFML - Test window", sf::Style::Close };
	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(shape);
		window.display();
	}

	return 0;
}