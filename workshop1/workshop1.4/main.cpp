#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace std;

struct Cat
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f scale;
	float rotation = 0;
};

struct Laser
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f ClickPosition;
	sf::Vector2f position;
};

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

void init(Cat& cat, Laser& laser)
{
	cat.texture.loadFromFile("./cat.png");
	cat.sprite.setTexture(cat.texture);
	cat.sprite.setPosition(400, 300);

	laser.texture.loadFromFile("./laser.png");
	laser.sprite.setTexture(laser.texture);
	laser.sprite.setPosition(400, 300);
	laser.sprite.setOrigin(laser.texture.getSize().x / 2, laser.texture.getSize().y / 2);
}

void onMouseClick(sf::Event::MouseButtonEvent& event, sf::Vector2f& ClickPosition)
{
	ClickPosition = { float(event.x), float(event.y) };
}
void pollEvents(sf::RenderWindow& window, sf::Vector2f& ClickPosition)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			onMouseClick(event.mouseButton, ClickPosition);
			break;
		default:
			break;
		}
	}
}
void redrawFrame(sf::RenderWindow& window, Cat& cat, Laser& laser)
{
	window.clear(sf::Color(255, 255, 255));
	window.draw(cat.sprite);
	window.draw(laser.sprite);
	window.display();
}

void updateCatElements(Cat& cat, Laser& laser)
{
	laser.sprite.setPosition(laser.position);
	cat.sprite.setPosition(cat.position);
	cat.sprite.setScale(cat.scale);
}

void update(const sf::Vector2f& ClickPosition, Cat& cat, Laser& laser, float deltaTime)
{
	const sf::Vector2f delta = ClickPosition - cat.position;
	float angle = atan2(delta.y, delta.x);
	laser.position = ClickPosition;

	if (angle < 0)
	{
		angle = angle + 2 * M_PI;
	}
	angle = toDegrees(angle);

	if (((angle >= 0) && (angle < 90)) || ((angle <= 360) && (angle > 270)))
	{
		cat.scale = { 1, 1 };
	}
	else
	{
		cat.scale = { -1, 1 };
	}

	const float deltaModule = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	sf::Vector2f direction = { 0, 0 };
	const float speed = 50 * deltaTime;
	direction = { delta.x / deltaModule, delta.y / deltaModule };

	cat.position = cat.position + direction * speed;

	updateCatElements(cat, laser);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cat and laser");
	sf::Clock clock;

	sf::Vector2f ClickPosition = { 400, 300 };

	Cat cat;
	Laser laser;

	init(cat, laser);

	while (window.isOpen())
	{
		pollEvents(window, ClickPosition);
		float deltaTime = clock.restart().asSeconds();
		update(ClickPosition, cat, laser, deltaTime);
		redrawFrame(window, cat, laser);
	}
}
