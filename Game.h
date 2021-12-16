#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

/*  Below headers are already included in player.h but will keep here for record.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
*/

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	// Needed to hold info about size(width,height of window) 
	VideoMode videoMode;
	// Main window to render everything
	RenderWindow* window;
	// Boolean variable to end game
	bool endGame;
	Event sfmlEvent;

	// Instantiate player object.
	Player player;
	int points;

	// Variables for text
	Font font;
	Text guiText;
	Text waterMark;
	Text GameOverText;

	// Vector for balls
	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;
	int spawnLimit;

	// Funtion to initilize variables
	void initVariables();
	// Function to create a window
	void initWindow();
	// Functions to initialized the text
	void initFont();
	void initText();

public:
	// Constructors and destructors
	Game();
	~Game();

	// Accessors *** PLACEHOLDER
	const bool& getEndGame() const;

	// Mutators *** PLACEHOLDER

	// Functions
	const bool running() const;
	void pollEvents();
	void despawnBall();
	void updateBall();

	void spawnSwagBalls();
	const int randomizeType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(RenderTarget* target);
	void render();
};

