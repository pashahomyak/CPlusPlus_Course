#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

constexpr unsigned BALL_SIZE = 35;

struct Ball
{
	sf::Vector2f speed;
	sf::CircleShape shape;
};

struct PRNG
{
	mt19937 engine;
};

void initGenerator(PRNG& generator)
{
	random_device device;
	generator.engine.seed(device());
}

unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
	assert(minValue < maxValue);
	uniform_int_distribution<unsigned> distribution(minValue, maxValue);
	return distribution(generator.engine);
}

void init(vector<Ball>& balls)
{
	const vector<sf::Vector2f> positions = { { 60, 80 },
		{ 200, 150 },
		{ 421, 350 },
		{ 500, 500 } };

	srand(time(nullptr));

	for (size_t i = 0; i < 4; ++i)
	{
		balls[i].shape.setPosition(positions[i]);
		balls[i].shape.setOrigin(BALL_SIZE, BALL_SIZE);
		balls[i].shape.setRadius(BALL_SIZE);

		int colorX = (rand() % 256 + rand() % 256) / 2;
		int colorY = (rand() % 256 + rand() % 256) / 2;
		int colorZ = (rand() % 256 + rand() % 256) / 2;
		balls[i].shape.setFillColor(sf::Color(colorX, colorY, colorZ));
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
		for (size_t si = i + 1; si < 4; ++si)
		{
			sf::Vector2f deltaSpeedPlus = balls[i].speed - balls[si].speed;
			sf::Vector2f deltaSpeedMinus = balls[si].speed - balls[i].speed;
			sf::Vector2f deltaPosPlus = balls[si].shape.getPosition() - balls[i].shape.getPosition();
			float deltaPos = pow(deltaPosPlus.x, 2) + pow(deltaPosPlus.y, 2);
			float deltaPosLong = sqrt(deltaPos);
			sf::Vector2f deltaPosMinus = balls[i].shape.getPosition() - balls[si].shape.getPosition();
			if (deltaPosLong <= 70)
			{
				balls[i].speed = balls[i].speed - ((deltaSpeedPlus.x * deltaPosPlus.x + deltaSpeedPlus.y * deltaPosPlus.y) / deltaPos) * deltaPosPlus;
				balls[si].speed = balls[si].speed - ((deltaSpeedMinus.x * deltaPosMinus.x + deltaSpeedMinus.y * deltaPosMinus.y) / deltaPos) * deltaPosMinus;
			}
		}
	}

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

float getRandomFloat(PRNG& generator, float minValue, float maxValue)
{
	assert(minValue < maxValue);
	uniform_real_distribution<float> distribution(minValue, maxValue);
	return distribution(generator.engine);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Balls", sf::Style::Default, settings);

	sf::Clock clock;

	vector<Ball> balls(4);

	PRNG generator;
	initGenerator(generator);
	for (int i = 0; i < 4; ++i)
	{
		float speedX = getRandomFloat(generator, 50.f, 250.f);
		float speedY = getRandomFloat(generator, 50.f, 250.f);
		balls[i].speed = { speedX, speedY };
	}

	init(balls);

	while (window.isOpen())
	{
		pollEvents(window);
		float dt = clock.restart().asSeconds();
		update(balls, dt);
		redrawFrame(window, balls);
	}
}
