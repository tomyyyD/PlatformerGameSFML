#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Circle.hpp"
#include <SFML/Graphics.hpp>

class GameLoop
{
public:
	GameLoop();
	void Run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handleMouseInput(sf::Mouse::Button button, bool isPressed);
	void checkWalls();
	bool circleRectCollisionCheck(float px, float py, float radius, float px1, float px2, float width, float height);

	sf::RenderWindow window;
	static const sf::Time TimePerFrame;
	Circle gameObjects[10];

	sf::RectangleShape walls[10];
	int numObjects = 0;
	int numWalls = 0;
};

#endif //GAMELOOP_H