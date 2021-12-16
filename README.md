# SFML-Practice-2-
MARCOS ORTEGA
CSC211H Honor's Project


NOTE: This project started of from a tutorial given by Surja Sharma (Youtube page: https://www.youtube.com/channel/UC2i39AOpDSlO1Mrn1jQ8Xkg).
There was a lot to learn but this tutorial helped with the basics of SFML and how to use it.

The original design of my project was to to create a platformer-type game with the player character moving throughout a dungeon fighting monsters.
The player would then engage the monster and then a battle would start. It would have a in-game window with a question and a multiple choices for the player to answer with.
The only way to defeat a monster is to answer a series of math-based questions. Each correct answer would damage the enemy and a wrong answer would damage the
player. The game would loop until the player defeated the necessary number of enemies, thus winning the game. The game would be over if the player lost all his/her health. 
Unfortunately, I (wildly) underestimated the work involve in designing a game and could not create my original plan. So I had to change the plan to create a simple game at least.

The final product is a simple game with the player being a green square. The player is able to move around it's enviroment, colliding with balls, thus "collecting" 
the ball, and avoiding red balls with a white border which are the ones that cause damage. The green balls with a white border give health to the player.
All other balls add points for player. The game loops continuoulsy until the player dies, at which point the game stops and display a game over text. 

***ISSUES***
1. I wanted to move the balls themselves because stationary balls were boring in my opinion, so I used an update() function for the ball (class SwagBall object, btw) to 
   move the ball through the enviroment. I needed to account for the borders of the windo so the ball doesn't go out of bound, which I solved. The issue was that the balls 
   only move towards NE cornder of window. I didn't have enought time to remedy this but POSSIBLE solution:
---> Use enum {N,S,E,W} to initialize ball with a compass direction and move ball with respect to direction. When ball collides with border, switch direction and move.
       For example; if ball direction is N, decrement ball y-coordinate till ball.getPosition().y == 0, then switch direction to S and increment till == window.getSize().x 
       then switch back. Loops so ball's y-coordinate is bouncing around. Use same logic for E and W movements.
       
2. I didn't want balls to stay indefinitely in the enviroment so I created a despawnBall() function. Used a timer that increments as game plays. When timer is up && vector
   of balls is 10 (max num of balls in-game is 10) then randomly erase a ball from the vector. Used rand() % 10 to randomly erase a ball from the game. Was able to resolve
   so balls despawn after a certain amount of time, in order to keep variety in the game.

3. I wanted to pause the game. I did not have time to solve this issue but if i had time I would create an event for the space keystroke and create a pauseGame() function in
   the Game class. Possibly use a true/false value for space to set bool gamePause variable with would be check in each iteration of the game.
   
4. I wanted to add music to the game. I don't have a music file for the game at the time but I would search for one and use inputSoundFile class object for file IO. I did use
   file IO for font of the text in the game, tho.
