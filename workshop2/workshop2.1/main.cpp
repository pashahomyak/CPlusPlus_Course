#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

constexpr unsigned BALL_SIZE = 35;

struct Ball
{
	sf::Vector2f speed;
	sf::CircleShape shape;
};

void init(vector<Ball>& balls)
{
	const vector<sf::Vector2f> positions = { { 60, 80 }, { 150, 100 }, { 300, 300 }, { 600, 540 } };

	const vector<sf::Vector2f> speeds = { { 100.f, 95.f }, { -200.f, 150.f }, { 200.f, 200.f }, { -150.f, 100.f } };

	const vector<sf::Color> colors = { sf::Color(0, 255, 255), sf::Color(255, 69, 0), sf::Color(250, 128, 114), sf::Color(75, 0, 130) };

	for (size_t i = 0; i < 4; ++i)
	{
		balls[i].shape.setPosition(positions[i]);
		balls[i].shape.setOrigin(BALL_SIZE, BALL_SIZE);
		balls[i].shape.setFillColor(colors[i]);
		balls[i].shape.setRadius(BALL_SIZE);
		balls[i].speed = speeds[i];
	}
}

void pollEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void update(vector<Ball>& balls, float& dt)
{
	for (size_t i = 0; i < 4; ++i)
	{
		sf::Vector2f position = balls[i].shape.getPosition();
		position += balls[i].speed * dt;

		if ((position.x + BALL_SIZE >= 800) && (balls[i].speed.x > 0))
		{
			balls[i].speed.x = -balls[i].speed.x;
		}
		if ((position.x - BALL_SIZE < 0) && (balls[i].speed.x < 0))
		{
			balls[i].speed.x = -balls[i].speed.x;
		}
		if ((position.y + BALL_SIZE >= 600) && (balls[i].speed.y > 0))
		{
			balls[i].speed.y = -balls[i].speed.y;
		}
		if ((position.y - BALL_SIZE < 0) && (balls[i].speed.y < 0))
		{
			balls[i].speed.y = -balls[i].speed.y;
		}

		balls[i].shape.setPosition(position);
	}
}

void redrawFrame(sf::RenderWindow& window, vector<Ball>& balls)
{
	window.clear();
	for (size_t i = 0; i < 4; ++i)
	{
		window.draw(balls[i].shape);
	}
	window.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Balls", sf::Style::Default, settings);

	sf::Clock clock;

	vector<Ball> balls(4);

	init(balls);

	while (window.isOpen())
	{
		pollEvents(window);
		float dt = clock.restart().asSeconds();
		update(balls, dt);
		redrawFrame(window, balls);
	}
}
