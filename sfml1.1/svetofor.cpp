#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({220, 420}), "Svetofor");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({200, 400});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(133, 133, 133));
    window.draw(shape1);

    sf::CircleShape shape2(50);
    shape2.setPosition({60, 40});
    shape2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(50);
    shape3.setPosition({60, 160});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape3);

    sf::CircleShape shape4(50);
    shape4.setPosition({60, 280});
    shape4.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}