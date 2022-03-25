#include "Circle.hpp"

Circle::Circle()
{
	shape.setRadius(50.f);
	shape.setOrigin(50.f, 50.f);
	shape.setPosition(200.f, 200.f);
	mass = 10;
	isColliding = false;
}

Circle::Circle(float startX, float startY, float radiusInput, float massInput)
{
	shape.setRadius(radiusInput);
	shape.setOrigin(radiusInput, radiusInput);
	shape.setPosition(startX, startY);

	mass = massInput;
	px = startX;
	py = startY;
	vx = 0.0f;
	vy = 0.0f;
}

void Circle::update(sf::Time deltaTime)
{
	float dt = deltaTime.asSeconds();

	ax = fx * mass;
	ay = fy * mass;

	vx = vx + ax * dt;
	vy = vy + ay * dt;

	px = px + vx * dt + 0.5f * ax * dt * dt;
	py = py + vy * dt + 0.5f * ax * dt * dt;

	shape.setPosition(px, py);
}

void Circle::applyForce(float forceInputX, float forceInputY)
{
	fx = forceInputX;
	fy = forceInputY;
}