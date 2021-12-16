#include "Game.h"


void Game::initVariables()
{
	// Set to false and when true, ends game.
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10; 
	this->points = 0;
	this->spawnLimit = 0; // TEST SPAWN LIMIT
}

void Game::initWindow()
{	
	// Set up screen. Arguements are for size.
	this->videoMode = VideoMode(800, 600);
	// Render the window, pass videoMode, title name, and styles)
	this->window = new RenderWindow(this->videoMode, "Swag Ballz", Style::Close | Style::Titlebar);
	// Set the frame rate. IMPORTANT!
	// Use arguement 0 to disable limit. Might break it, tho (TO BE TESTED).
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	// If font not loaded, print error message.
	if (!this->font.loadFromFile("Fonts/BebasNeue-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS:: COULD NOT LOAD BebasNeue-Regular.ttf\n";
	}
}

void Game::initText()
{
	// Inititialize text with font
	this->guiText.setFont(this->font);
	// Inititialize text with color
	this->guiText.setFillColor(Color::White);
	// Inititialize text with size
	this->guiText.setCharacterSize(32);


	// Inititialize text with font
	this->waterMark.setFont(this->font);
	// Inititialize text with color
	this->waterMark.setFillColor(Color::Magenta);
	// Inititialize text with size
	this->waterMark.setCharacterSize(20);


	//End game text
	// Inititialize text with font
	this->GameOverText.setFont(this->font);
	// Inititialize text with color
	this->GameOverText.setFillColor(Color::Magenta);
	// Inititialize text with size
	this->GameOverText.setCharacterSize(60);
	this->GameOverText.setPosition(Vector2f(20, 300));
	this->GameOverText.setString("GAME OVER!!!\nEXIT GAME!");
}

// Constructor and Destructor
// We'll use functions to initialize variables as needed, avoiding long lines of code.
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	// to avoid memory leak. Recall that window is pointer to new RenderWindow.
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

//*************************** Functions**********************************//
const bool Game::running() const
{
	// If window open, running will return true.
	// Note: that isOPen() is a member function of Window class t.
	// 
	return this->window->isOpen(); //&& this->endGame == false; LEFT FOR RECORD
}

// Basically, input from user like key pressed and mouse clicks.
void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type) 
		{
		case Event::Closed:   // Closing window closes the rendered window.
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->sfmlEvent.key.code == Keyboard::Escape )
		// Enabling may annoy player (|| this->sfmlEvent.key.code == Keyboard::Q )  // close window with escape
				this->window->close();
			break;
		}
	}
}

// We don't want balls to stick around forever so lets delete them after a certain time.
void Game::despawnBall()
{
	this->spawnLimit++;

	// will delete once timer is up && ball vector size is 10.
	if (this->spawnLimit > 25 && this->swagBalls.size() == 10)
	{
		int i = (rand() % 10);
		this->swagBalls.erase(this->swagBalls.begin() + i);

		this->spawnLimit = 0;
	}

}

void Game::updateBall()
{
	// Iterate thru swagBalls vector. Need to check each for collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		this->swagBalls[i].update(*window);
	}
}

void Game::spawnSwagBalls()
{
	// Spawn timer of a swagBall, otherwise they may not spawn at all or 
	// spawn instantly. Which is not good. Of course.
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		// Check vector for room, add a ball.
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randomizeType() ) );
			this->spawnTimer = 0.f;
		}
	}
}


// Function to randomize ball type. Lower chance for damagining ball type .
const int Game::randomizeType() const
{
	int type = SwagBallTypes::DEFAULT;
	
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
	{
		type = SwagBallTypes::DAMAGING;
	}
	else if (randValue > 80 && randValue <= 100)
	{
		type = SwagBallTypes::HEALING;
	}

	return type;

	//return 0;
}

void Game::updatePlayer()
{
	// Function for player outline to alternate.
	this->player.outlineColor();

	this->player.update(this->window);

	if (this->player.getHp() <= 0)
	{
		this->endGame = true; 
	}
}

void Game::updateCollision()
{
	// Check for collision with player and ball. Will remove ball from vector if needed.
	

	// Iterate thru swagBalls vector. Need to check each for collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		// Get shape, get bounds, and check for intersection with an object
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{

			// Switch case for ball type. Add points given type.
			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(2);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			// Remove collided ball from the vector.
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}

	
}

void Game::updateGui()
{
	// Turn all kinds of data into string; less casting and stuff
	std::stringstream ss;
	std::stringstream ss2;

	ss << " - Points: " << this->points << "\n";
	ss << " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());

	// Included a watermark. Has not broken game yet.
	ss2 << "\n\n\n\n - A Marcos O. Production :)" << "\n";

	this->waterMark.setString(ss2.str());

}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{

		this->spawnSwagBalls();

		this->updateBall();

		// Update player on screen.
		this->updatePlayer();

		this->updateCollision();

		this->despawnBall();

		this->updateGui();
	}


}

void Game::renderGui(RenderTarget* target)
{
	// Draw text to target.
	target->draw(this->guiText);
	target->draw(this->waterMark);
}

// Render the whole game; player, enemies, text.
void Game::render()
{
	// Clear old frame to render new frame.
	// set background to color choice.
	this->window->clear(Color::Color(0, 40 ,0,255));


	// Render stuff
	this->player.render(this->window);

	for (auto i : this->swagBalls)
	{
		i.render(*this->window);
	}

	// Render GUI
	this->renderGui(this->window);


	if (this->endGame == true)
	{
		this->window->draw(this->GameOverText);
	}

	// Display what's been rendered so far. Put last.
	this->window->display();
}

 // Functions