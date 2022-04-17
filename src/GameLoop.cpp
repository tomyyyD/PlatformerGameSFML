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
	rect1.setPosition((window.getSize().x / 2) - 100.0f, (window.getSize().y / 2) - 25.0f);
	rect1.setSize(rect1Size);

	walls[0] = rect1;
	numWalls++;
}

void GameLoop::Run()
{
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
				gameObjects[i].collisionDepth = (gameObjects[i].py + gameObjects[i].radius) - walls[j].getPosition().y;
				gameObjects[i].isColliding = true;
			}
			else
			{
				gameObjects[i].isColliding = false;
			}
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
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
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
			gameObjects[i].canJump = true;
			gameObjects[i].fy += gameObjects[i].mass * -gameObjects[i].vy / deltaTime.asSeconds();
			if (gameObjects[i].collisionDepth > 1)
			{
				gameObjects[i].py -= gameObjects[i].collisionDepth;
			}
		}
		else
		{
			gameObjects[i].fy += 200.f * gameObjects[i].mass;
		}
		gameObjects[i].update(deltaTime);
		gameObjects[i].fy = 0;
		gameObjects[i].fx = 0;
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
	window.display();
}

void GameLoop::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Space && isPressed && gameObjects[0].canJump)
	{
		gameObjects[0].fy += -100000;
		gameObjects[0].canJump = false;
	}
	if (key == sf::Keyboard::A && isPressed)
	{
		gameObjects[0].fx += -800;
	}
	if (key == sf::Keyboard::D && isPressed)
	{
		gameObjects[0].fx += 800;
	}
}

void GameLoop::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
	if (button == sf::Mouse::Left && isPressed && numObjects < 10)
	{
		Circle object(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 50.0f, 10.f);
		gameObjects[numObjects] = object;

		numObjects++;
	}
}

bool GameLoop::circleRectCollisionCheck(float cx, float cy, float radius, float rx, float ry, float width, float height)
{
	if (rx - radius < cx && rx + radius + width > cx && ry - radius < cy && ry + radius + height > cy)
	{
		return true;
	}
	return false;
}