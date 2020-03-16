
// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"


int main(void)
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

	// Limit FPS to 60
	window.setFramerateLimit(60);


	// Game loop bool
	bool play = true;



	// Pads
	PAD pad1;
	// Set length of pad
	pad1.length = 150;

	// Create the rectangle shape with given length and width and position it
	pad1.rect.setSize(sf::Vector2f(pad1.width, pad1.length));
	pad1.rect.setPosition(20, 400);

	// Add texture
	pad1.texture.loadFromFile("resources/test.png");
	pad1.rect.setTexture(&pad1.texture);

	PAD pad2;
	// Set length of pad
	pad2.length = 150;

	// Create the rectangle shape with given length and width
	pad2.rect.setSize(sf::Vector2f(pad1.width, pad1.length));

	pad2.rect.setPosition(750, 350);


	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(10);

	// Add texture
	ball.texture.loadFromFile("resources/col.png");

	ball.circle.setPosition(400, 300);






	// States

		// Keyboard buttons  
	bool W = false, S = false;
	bool Up = false, Down = false;

	// Variables 


	
	// GAME LOOP
	while (play)
	{

		// EVENTS
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}

			// Movement if statments, "if (1)" is just to minimize 
			if (1)
			{
				if (isPressed('W' - 'A'))
					W = true;
				if (isPressed('S' - 'A'))
					S = true;
				if (isReleased('W' - 'A'))
					W = false;
				if (isReleased('S' - 'A'))
					S = false;

				if (isPressed(73))
					Up = true;

				if (isPressed(74))
					Down = true;

				if (isReleased(73))
					Up = false;

				if (isReleased(74))
					Down = false;
			}

		}

		// LOGIC

			// Movment

				// Pad1 Movement
		pad1.velocity = Get_Movement(S, W) * 5;
		pad1.rect.move(0, pad1.velocity);
		boundcheck(pad1.rect);

		// Pad2 Movement
		pad2.velocity = Get_Movement(Down, Up) * 5;
		pad2.rect.move(0, pad2.velocity);
		boundcheck(pad2.rect);

		// Ball Movement

		ball.circle.move(ball.xVelocity, ball.yVelocity);
		boundcheck_ball(ball);
		isColliding(ball, pad1, pad2);


		// RENDERING

		window.clear(sf :: Color :: Cyan);

		// Draw pads and ball
		window.draw(pad1.rect);
		window.draw(pad2.rect);
		window.draw(ball.circle);

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}