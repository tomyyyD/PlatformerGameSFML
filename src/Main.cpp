#include "GameLoop.hpp"
#include "Platform/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <time.h>

// int main()
// {
// 	util::Platform platform;

// #if defined(_DEBUG)
// 	std::cout << "Hello World!" << std::endl;
// #endif

// 	//anti-aliasing
// 	sf::ContextSettings settings;
// 	settings.antialiasingLevel = 8;

// 	sf::RenderWindow window;

// 	// in Windows at least, this must be called before creating the window
// 	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

// 	// Use the screenScalingFactor
// 	window.create(sf::VideoMode(800.0f * screenScalingFactor, 600.0f * screenScalingFactor), "SFML works!", sf::Style::Default, settings);
// 	platform.setIcon(window.getSystemHandle());

// 	float circleRadius = 100.0f;
// 	sf::CircleShape shape(circleRadius, 40);
// 	shape.setFillColor(sf::Color::Green);
// 	shape.setOrigin(circleRadius, circleRadius);
// 	shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);

// 	sf::Event event;

// 	while (window.isOpen())
// 	{
// 		while (window.pollEvent(event))
// 		{
// 			if (event.type == sf::Event::Closed)
// 				window.close();
// 		}
// 		shape.setPosition(shape.getPosition().x, shape.getPosition().y + 1);

// 		window.clear();
// 		window.draw(shape);
// 		window.display();
// 	}

// 	return 0;
// }

int main()
{
	GameLoop gameLoop;
	gameLoop.Run();
	return 0;
}