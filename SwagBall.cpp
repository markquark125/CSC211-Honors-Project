#include "SwagBall.h"

void SwagBall::initShape(const RenderWindow& window)
{
	this->movementSpeed = 2.f;

	// Randomize the radius and color.
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	Color color;

	switch (this->type)
	{
	case DEFAULT:
		color = Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = Color::Red;
		this->shape.setOutlineColor(Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = Color::Green;
		this->shape.setOutlineColor(Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}



	// Fill shape with randomized color.
	this->shape.setFillColor(color);

	// Randomize ball position. 
	this->shape.setPosition(Vector2f
	(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)) );

}

SwagBall::SwagBall(const RenderWindow& window, int type) : type(type)
{
	this->initShape(window);
}

SwagBall::~SwagBall()
{
}

const CircleShape SwagBall::getShape() const
{
	// Return the ball shape.
	return this->shape;
}

const int& SwagBall::getType() const
{
	return this->type;
}

void SwagBall::update(const RenderWindow& window)
{

	if (shape.getPosition().x < window.getSize().x)
	{
		shape.move(-(this->movementSpeed), 0.f);
	}
	
	if (shape.getPosition().x <= 0)
	{
		shape.move(this->movementSpeed, 0.f);
	}

	if (shape.getPosition().y < window.getSize().y)
	{
		shape.move(0.f, -(this->movementSpeed));
	}

	if (shape.getPosition().y <= 0)
	{
		shape.move(0.f, this->movementSpeed);
	}

}

void SwagBall::render(RenderTarget& target)
{
	target.draw(this->shape);
}
