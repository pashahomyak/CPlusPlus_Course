#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

void init(sf::ConvexShape& pointer)
{
	pointer.setPointCount(7);
	pointer.setPoint(0, { 0, 50 });
	pointer.setPoint(1, { 50, 0 });
	pointer.setPoint(2, { 0, -50 });
	pointer.setPoint(3, { 0, -20 });
	pointer.setPoint(4, { -50, -20 });
	pointer.setPoint(5, { -50, 20 });
	pointer.setPoint(6, { 0, 20 });
	pointer.setPosition({ 400, 300 });
	pointer.setFillColor(sf::Color(255, 255, 0));
	pointer.setOutlineColor(sf::Color(0, 0, 0));
	pointer.setOutlineThickness(2);
}

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

	mousePosition = { float(event.x), float(event.y) };
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

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, float& dt)
{
	const sf::Vector2f delta = mousePosition - pointer.getPosition();
	float maxSpeed = 90;
	float angle = atan2(delta.y, delta.x);
	if (angle < 0)
	{
		angle = angle + 2 * M_PI;
	}
	angle = toDegrees(angle);
	const float maxRotation = maxSpeed * dt;
	const float rotation = std::abs((angle - pointer.getRotation())); //выводит абсолютное значение
	if (angle < pointer.getRotation())
	{
		if ((angle + 180) < pointer.getRotation())
		{
			pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
		}
		else
		{
			pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
		}
	}
	else
	{
		if ((angle - 180) > pointer.getRotation())
		{
			pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
		}
		else
		{
			pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
		}
	}

	const float deltaModule = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	sf::Vector2f direction = { 0, 0 };
	sf::Vector2f position = { 400, 300 };
	const float speed = 20 * dt;
	direction = { delta.x / deltaModule, delta.y / deltaModule };

	pointer.setPosition(pointer.getPosition() + direction * speed);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(pointer);
	window.display();
}

int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Pointer follows mouse", sf::Style::Default, settings);

	sf::Vector2f position;
	sf::ConvexShape pointer;
	sf::Vector2f mousePosition;
	sf::Clock clock;

	init(pointer);
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		pollEvents(window, mousePosition);
		update(mousePosition, pointer, dt);
		redrawFrame(window, pointer);
	}
}