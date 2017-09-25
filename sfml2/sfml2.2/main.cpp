#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <SFML/System.hpp>

int main()
{
    constexpr int pointCount = 200;
    constexpr float periodY = 2.f;
    constexpr int okrRadius = 100;
    float time = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);
    sf::Clock clock;

    sf::Vector2f position = {400, 300};

    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float ellipseRadius = 200 * std::sin(6 * angle);

        sf::Vector2f point = {
            ellipseRadius * std::sin(angle),
            ellipseRadius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

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

        const float dt = clock.restart().asSeconds();

        time = time + dt;

        const float wavePhase = time * float(2 * M_PI);
        const float x = okrRadius * std::cos(wavePhase / periodY);
        const float y = okrRadius * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}
