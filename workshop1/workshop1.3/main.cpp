#include <SFML/Graphics.hpp>  //Запускал в терминале из workshop1.
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "cat", sf::Style::Default, settings);

	sf::Texture texture;
	texture.loadFromFile("./workshop1.3/cat.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(400, 300);

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
		window.draw(sprite);
		window.display();
	}
}
