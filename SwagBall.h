#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

// Use to avoid sf:: prefix all the time.
using namespace sf;

// Enums for ball types.
enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};
enum direction {NORTH, SOUTH, EAST, WEST, NRODIRECTION};

class SwagBall
{
private:
	CircleShape shape;
	int type;
	int movementSpeed;
	int direction1;
	direction dirc;

	void initShape(const RenderWindow& window);

public:
	SwagBall(const RenderWindow& window, int type);
	virtual ~SwagBall();

	// Accessors
	const CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update(const RenderWindow& window);
	void render(RenderTarget &target);
};

