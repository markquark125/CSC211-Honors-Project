#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = hpMax;

}

void Player::initShape()
{
	this->shape.setFillColor(Color::Green);
	this->shape.setOutlineThickness(2.f);

	// Draws a shape with 2D vector
	this->shape.setSize(Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	// Set the player's position
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
	// PLACE HOLDER - Not needed.
}

const RectangleShape& Player::getShape() const
{
	// Return shape of the player
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}


const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::outlineColor()
{
	shape.setOutlineColor(Color::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 256));
}

// ACCESSORS
void Player::takeDamage(const int damage)
{
	// Decreament for damage.
	if (this->hp > 0)
		this->hp -= damage;
	
	// Do not want player HP to be lower than zero
	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	// Increament for health
	if (this->hp < this->hpMax)
		this->hp += health;

	// Do not want health to exceed HP max.
	if (this->hp > this->hpMax)
		this->hp = hpMax;
}

// Function for keyboard input
void Player::updateInput()
{
	// Move the player with keyboard input. Note that is it does not SET the player.
	// Note that uses (x,y). For up in Y, use negative. Weird, I know.
	// Note the if/if-else. It is to account for diagonal movements.
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->shape.move((-this->movementSpeed), 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->shape.move((this->movementSpeed), 0.f); // Moves instead of sets. Note: it uses (x,y)
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->shape.move(0.f, (-this->movementSpeed)); // Moves instead of sets. Note: it uses (x,y)
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->shape.move(0.f, (this->movementSpeed)); // Moves instead of sets. Note: it uses (x,y)
	}
}

void Player::updateWindowBoundsCollision(const RenderWindow* target)
{
	// Tried to use a pointer but it wasn't working. Revised code to account for issues with corner-window bounds.

	// Check left side of window with left side of player shape.
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);  // Set x at 0 and y remains the same (top = y)
	// Check for right bound. Takes some math as players x coord + width,
	// gives player's right bound. Then compare to window x size (AKA window's right bound)

	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition((target->getSize().x - this->shape.getGlobalBounds().width) , this->shape.getGlobalBounds().top);  
	// ^ Set player x with window size - player's width.

	// Top bound
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);  // Set x at 0 and y remains the same (top = y)
	// Bottom bound
	if ((this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height) >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, (target->getSize().y - this->shape.getGlobalBounds().height) ); 
	//  ^ Set player x coordinate with window size - player's width.
}

void Player::update(const RenderWindow* target)
{
	// Call the updateInput function.
	this->updateInput();

	// Window bounds collision
	this->updateWindowBoundsCollision(target);

}

void Player::render(RenderTarget* target)
{
	target->draw(this->shape);
}

