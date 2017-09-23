#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({700, 650}), "Home");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({450, 325});
    shape1.setRotation(0);
    shape1.setPosition({100, 350});
    shape1.setFillColor(sf::Color(150, 75, 0));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({125, 250});
    shape2.setPosition({175, 425});
    shape2.setFillColor(sf::Color(105, 105, 105));
    window.draw(shape2);

    sf::ConvexShape tr;
    tr.setFillColor(sf::Color(128, 0, 128));
    tr.setPosition({325, 200});
    tr.setPointCount(4);
    tr.setPoint(0, {-300, +150});
    tr.setPoint(1, {-150, 0});
    tr.setPoint(2, {+150, 0});
    tr.setPoint(3, {+300, +150});
    window.draw(tr);

    sf::RectangleShape shape3;
    shape3.setSize({50, 125});
    shape3.setPosition({350, 175});
    shape3.setFillColor(sf::Color(128, 128, 128));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({100, 50});
    shape4.setRotation(0);
    shape4.setPosition({325, 125});
    shape4.setFillColor(sf::Color(128, 128, 128));
    window.draw(shape4);

    sf::CircleShape shape5(29);
    shape5.setPosition({400, 100});
    shape5.setFillColor(sf::Color(211, 211, 211));
    window.draw(shape5);

    sf::CircleShape shape6(30);
    shape6.setPosition({450, 75});
    shape6.setFillColor(sf::Color(211, 211, 211));
    window.draw(shape6);

    sf::CircleShape shape7(33);
    shape7.setPosition({500, 50});
    shape7.setFillColor(sf::Color(211, 211, 211));
    window.draw(shape7);

    window.display();

    sf::sleep(sf::seconds(5));
}
