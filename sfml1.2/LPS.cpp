#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({150, 100}), "LPS");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({10, 60});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({40, 10});
    shape2.setRotation(0);
    shape2.setPosition({10, 70});
    shape2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({10, 70});
    shape3.setPosition({60, 10});
    shape3.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({20, 10});
    shape4.setRotation(0);
    shape4.setPosition({70, 30});
    shape4.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({20, 10});
    shape5.setRotation(0);
    shape5.setPosition({70, 10});
    shape5.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({10, 10});
    shape6.setPosition({80, 20});
    shape6.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({30, 10});
    shape7.setRotation(0);
    shape7.setPosition({100, 70});
    shape7.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({10, 30});
    shape8.setPosition({130, 50});
    shape8.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({30, 10});
    shape9.setRotation(0);
    shape9.setPosition({110, 40});
    shape9.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape9);

    sf::RectangleShape shape10;
    shape10.setSize({10, 40});
    shape10.setPosition({100, 10});
    shape10.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape10);

    sf::RectangleShape shape11;
    shape11.setSize({30, 10});
    shape11.setRotation(0);
    shape11.setPosition({110, 10});
    shape11.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(shape11);

    window.display();
    sf::sleep(sf::seconds(5));
}