#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
	sf::ConvexShape ellipse;
	sf::ConvexShape mellipse;
	sf::Vector2f position;
	float rotation = 0;
};

sf::Vector2f toEuclidian(float rotationRadiusX, float rotationRadiusY, float angle)
{
	return {
		rotationRadiusX * float(cos(angle)),
		rotationRadiusY * float(sin(angle))
	};
}

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

void updateEyesElements(Eye& eye1, Eye& eye2)
{
	constexpr float rotationRadiusX = 30.f;
	constexpr float rotationRadiusY = 60.f;

	const sf::Vector2f eye1EllipseOffset = toEuclidian(rotationRadiusX, rotationRadiusY, eye1.rotation);
	eye1.mellipse.setPosition(eye1.position + eye1EllipseOffset);

	const sf::Vector2f eye2EllipseOffset = toEuclidian(rotationRadiusX, rotationRadiusY, eye2.rotation);
	eye2.mellipse.setPosition(eye2.position + eye2EllipseOffset);
}

void initEyes(Eye& eye1, Eye& eye2)
{
	const sf::Vector2f ellipseRadius = { 100.f, 200.f };
	const sf::Vector2f mellipseRadius = { 25.f, 50.f };
	constexpr int pointCount = 200;

	eye1.position = { 250, 400 };
	eye2.position = { 700, 400 };

	eye1.ellipse.setPosition(eye1.position);
	eye1.mellipse.setPosition(eye1.position);
	eye1.ellipse.setFillColor(sf::Color(255, 255, 255));
	eye1.mellipse.setFillColor(sf::Color(0, 0, 0));
	eye1.ellipse.setPointCount(pointCount);
	eye1.mellipse.setPointCount(pointCount);

	eye2.ellipse.setPosition(eye2.position);
	eye2.mellipse.setPosition(eye2.position);
	eye2.ellipse.setFillColor(sf::Color(255, 255, 255));
	eye2.mellipse.setFillColor(sf::Color(0, 0, 0));
	eye2.ellipse.setPointCount(pointCount);
	eye2.mellipse.setPointCount(pointCount);

	for (int pointNo = 0; pointNo < pointCount; ++pointNo)
	{
		float angle = float(2 * M_PI * pointNo) / float(pointCount);
		sf::Vector2f point = {
			ellipseRadius.x * std::sin(angle),
			ellipseRadius.y * std::cos(angle)
		};
		eye1.ellipse.setPoint(pointNo, point);
		eye2.ellipse.setPoint(pointNo, point);
	}

	for (int pointNo = 0; pointNo < pointCount; ++pointNo)
	{
		float angle = float(2 * M_PI * pointNo) / float(pointCount);
		sf::Vector2f point = {
			mellipseRadius.x * std::sin(angle),
			mellipseRadius.y * std::cos(angle)
		};
		eye1.mellipse.setPoint(pointNo, point);
		eye2.mellipse.setPoint(pointNo, point);
	}

	updateEyesElements(eye1, eye2);
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

void updateEyes(const sf::Vector2f& mousePosition, Eye& eye1, Eye& eye2)
{
	const sf::Vector2f firstEyeDelta = mousePosition - eye1.position;
	eye1.rotation = atan2(firstEyeDelta.y, firstEyeDelta.x);

	const sf::Vector2f secondEyeDelta = mousePosition - eye2.position;
	eye2.rotation = atan2(secondEyeDelta.y, secondEyeDelta.x);

	updateEyesElements(eye1, eye2);
}

void redrawFrame(sf::RenderWindow& window, Eye& eye1, Eye& eye2)
{
	window.clear();
	window.draw(eye1.ellipse);
	window.draw(eye2.ellipse);
	window.draw(eye1.mellipse);
	window.draw(eye2.mellipse);
	window.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({ 1000, 768 }),
		"Eyes follows mouse", sf::Style::Default, settings);

	Eye eye1;
	Eye eye2;
	sf::Vector2f mousePosition;

	initEyes(eye1, eye2);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		updateEyes(mousePosition, eye1, eye2);
		redrawFrame(window, eye1, eye2);
	}
}