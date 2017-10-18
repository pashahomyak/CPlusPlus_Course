#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "arrow", sf::Style::Default, settings);

	sf::ConvexShape arrow;
	arrow.setPosition(400, 400);
	arrow.setRotation(15);
	arrow.setFillColor(sf::Color(255, 255, 0));
	arrow.setPointCount(7);
	arrow.setPoint(0, { 0, -50 });
	arrow.setPoint(1, { 50, 0 });
	arrow.setPoint(2, { 20, 0 });
	arrow.setPoint(3, { 20, 50 });
	arrow.setPoint(4, { -20, 50 });
	arrow.setPoint(5, { -20, 0 });
	arrow.setPoint(6, { -50, 0 });

	arrow.setOutlineColor(sf::Color(0, 0, 0));
	arrow.setOutlineThickness(2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));
		window.draw(arrow);
		window.display();
	}
}