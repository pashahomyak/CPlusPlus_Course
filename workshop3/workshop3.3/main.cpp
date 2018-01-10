#include "main.h"
#include <iostream>

using namespace std;

void onMouseMove(sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	mousePosition = { float(event.x), float(event.y) };
	sf::Vector2f deltaPos = sf::Vector2f({ 400, 300 }) - mousePosition;
	float distance = hypot(deltaPos.x, deltaPos.y);
	printf("Line length: %f\n", distance);
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			onMouseMove(event.mouseMove, mousePosition);
			break;
		default:
			break;
		}
	}
}

void initLine(sf::VertexArray(&line), sf::Vector2f mousePosition)
{
	line[0].position = { 400, 300 };
	line[0].color = sf::Color(0, 0, 0);

	line[1].position = mousePosition;
	line[1].color = sf::Color(0, 0, 0);
}

void redrawFrame(sf::RenderWindow& window, sf::VertexArray& line)
{
	window.clear(sf::Color(0xFF, 0xFF, 0xFF));
	window.draw(line);
	window.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Line", sf::Style::Default, settings);

	sf::Vector2f mousePosition;

	sf::VertexArray line(sf::Lines, 2);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		redrawFrame(window, line);
		initLine(line, mousePosition);
	}
}