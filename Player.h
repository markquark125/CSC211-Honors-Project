#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

// Use to avoid sf:: prefix all the time.
using namespace sf;

class Player
{
private:
	RectangleShape shape;

	// Player variables
	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	// Accessors
	const RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// Mutator
	void outlineColor();

	// FUNCTIONS
	void takeDamage(const int damage);
	void gainHealth(const int health);


	void updateInput();
	// Seperate func for collision
	void updateWindowBoundsCollision(const RenderWindow* target);
	// Send window to player.update func to account for collision
	void update(const RenderWindow* target);
	void render(RenderTarget* target);
};

