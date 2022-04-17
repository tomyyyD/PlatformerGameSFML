#ifndef CIRCLE_H
#define CIRCLE_H

#include "SFML/Graphics.hpp"

class Circle
{
public:
	Circle();
	Circle(float startX, float startY, float radiusInput, float massInput);
	void applyForce(float forceInputX, float forceInputY);
	void update(sf::Time deltaTime);
	sf::CircleShape shape;
	bool isColliding;
	bool canJump;
	float collisionDepth;
	float radius;
	float mass;
	float fx;
	float fy;
	float ax;
	float ay;
	float vx;
	float vy;
	float px;
	float py;
};

#endif