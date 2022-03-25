#include "GameLoop.hpp"
#include "Circle.hpp"
#include "Platform/Platform.hpp"
#include <iostream>

const sf::Time GameLoop::TimePerFrame = sf::seconds(1.0f / 60.0f);

sf::RectangleShape boundsBox;

GameLoop::GameLoop()
{
	util::Platform platform;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	window.create(sf::VideoMode(800.0f * screenScalingFactor, 600.0f * screenScalingFactor), "The Sim", sf::Style::Default, settings);
	platform.setIcon(window.getSystemHandle());

	sf::RectangleShape rect1;
	sf::Vector2f rect1Size(200.f, 50.0f);
	rect1.setPosition(0, 0);
	rect1.setSize(rect1Size);

	walls[0] = rect1;
	numWalls++;
}

void GameLoop::Run()
{

	std::cout << "starting game" << std::endl;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			checkWalls();
			update(TimePerFrame);
		}
		render();
	}
}

void GameLoop::checkWalls()
{
	for (int i = 0; i < numObjects; i++)
	{
		for (int j = 0; j < numWalls; j++)
		{
			sf::Vector2f wallPos(walls[j].getPosition());
			sf::Vector2f wallSize(walls[j].getSize());
			boundsBox.setPosition(wallPos);
			boundsBox.setSize(wallSize);
			if (circleRectCollisionCheck(gameObjects[i].px, gameObjects[i].py, gameObjects[i].radius, walls[j].getPosition().x, walls[j].getPosition().y, wallSize.x, wallSize.y))
			{
				gameObjects[i].isColliding = true;
				std::cout << "Collision" << std::endl;
			}
			gameObjects[i].isColliding = false;
		}
	}
}

void GameLoop::processEvents()
{
	sf::Event event {};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// case sf::Event::KeyPressed:
			// 	handlePlayerInput(event.key.code, true);
			// 	break;
			// case sf::Event::KeyReleased:
			// 	handlePlayerInput(event.key.code, false);
			// 	break;
			case sf::Event::MouseButtonPressed:
				handleMouseInput(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				handleMouseInput(event.mouseButton.button, false);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
		}
	}
}

void GameLoop::update(sf::Time deltaTime)
{
	for (int i = 0; i < numObjects; i++)
	{
		if (gameObjects[i].isColliding)
		{
			gameObjects[i].fx = 0;
			gameObjects[i].fy = 0;
			gameObjects[i].vx = 0;
			gameObjects[i].vy = 0;
		}
		else
		{
			gameObjects[i].fy = -9.81;
			gameObjects[i].update(deltaTime);
		}
	}
}

void GameLoop::render()
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < numObjects; i++)
	{
		window.draw(gameObjects[i].shape);
	}
	for (int i = 0; i < numWalls; i++)
	{
		window.draw(walls[i]);
	}
	boundsBox.setOutlineColor(sf::Color::Green);
	boundsBox.setOutlineThickness(5.0f);
	boundsBox.setFillColor(sf::Color::Black);
	window.draw(boundsBox);
	window.display();
}

// void GameLoop::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
// {
// 		if (key == sf::Keyboard::Left && isPressed)
// 	{
// 		vx = -10;
// 	}
// 	else if (key == sf::Keyboard::Right)
// 	{
// 		vx = 10;
// 	}
// 	else if (key == sf::Keyboard::Up)
// 	{
// 		vy = -10;
// 	}
// 	else if (key == sf::Keyboard::Down)
// 	{
// 		vy = 10;
// 	}
// 	else if (!isPressed)
// 	{
// 		vx = 0;
// 		vy = 0;
// 	}
// }

void GameLoop::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
	if (button == sf::Mouse::Left && isPressed && numObjects < 10)
	{
		Circle object(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 50.0f, 10.f);
		gameObjects[numObjects] = object;

		numObjects++;
	}
}

bool GameLoop::circleRectCollisionCheck(float px1, float py1, float radius, float px2, float py2, float width, float height)
{
	if (px2 - radius < px1 && px1 < px2 + radius + height && py2 - radius < py1 && py1 < py2 + radius + width)
		return true;
	return false;
}