#include "Circle.hpp"

Circle::Circle()
{
	shape.setRadius(50.f);
	shape.setOrigin(50.f, 50.f);
	shape.setPosition(200.f, 200.f);
	mass = 10;
	isColliding = false;
	canJump = false;
}

Circle::Circle(float startX, float startY, float radiusInput, float massInput)
{
	shape.setRadius(radiusInput);
	shape.setOrigin(radiusInput, radiusInput);
	shape.setPosition(startX, startY);
	radius = radiusInput;
	mass = massInput;
	canJump = false;
	isColliding = false;
	px = startX;
	py = startY;
	vx = 0.0f;
	vy = 0.0f;
}

void Circle::update(sf::Time deltaTime)
{
	float dt = deltaTime.asSeconds();

	//applies nonconservative forces
	//force of friction
	float airResX = 0.5 * vx * vx;
	float airResY = 0.1 * vy * vy;

	if (vy > 0)
		fy -= airResY;
	else if (vy < 0)
		fy += airResY;
	if (vx > 0)
		fx -= airResX;
	else if (vx < 0)
		fx += airResX;

	//applies accleration based on force
	ax = fx / mass;
	ay = fy / mass;

	//applies velocity based on acceleration
	vx = vx + ax * dt;
	vy = vy + ay * dt;

	//changes position based on velocity
	px = px + vx * dt + 0.5f * ax * dt * dt;
	py = py + vy * dt + 0.5f * ax * dt * dt;

	std::cout << vy << std::endl;

	shape.setPosition(px, py);
}

void Circle::applyForce(float forceInputX, float forceInputY)
{
	fx = forceInputX;
	fy = forceInputY;
}