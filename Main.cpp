
// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
int main(void)
{

	// Create the main window 
	RenderWindow window(VideoMode(GAMEWIDTH, GAMEHEIGHT), "Pong");

	// Limit FPS to 60
	window.setFramerateLimit(60);


	// Game loop bool
	bool play = true;



	// Pads
	PAD pad1;
	// Set length of pad
	pad1.length = 150;

	// Create the rectangle shape with given length and width and position it
	pad1.rect.setSize(Vector2f(pad1.width, pad1.length));
	pad1.rect.setPosition(20, 400);

	// Add texture
	pad1.texture.loadFromFile("resources/test.png");
	pad1.rect.setTexture(&pad1.texture);

	PAD pad2;
	// Set length of pad
	pad2.length = 150;

	// Create the rectangle shape with given length and width
	pad2.rect.setSize(Vector2f(pad1.width, pad1.length));

	pad2.rect.setPosition(750, 350);


	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(15);

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
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				play = false;
				return 0;
			}

			// pad1 Movement
			if (isPressed(Keyboard::W))
				W = true;
			else
				W = false;

			if (isPressed(Keyboard::S))
				S = true;
			else
				S = false;

			// pad2 Movement
			if (isPressed(Keyboard::Up))
				Up = true;
			else
				Up = false;

			if (isPressed(Keyboard::Down))
				Down = true;
			else
				Down = false;


		}

		// LOGIC

			// Movment

		// Pad1 Movement
		pad1.velocity = Get_Movement(S, W) * 10;
		pad1.rect.move(0, pad1.velocity);
		boundcheck(pad1.rect);

		// Pad2 Movement
		pad2.velocity = Get_Movement(Down, Up) * 10;
		pad2.rect.move(0, pad2.velocity);
		boundcheck(pad2.rect);

		// Ball Movement

		ball.circle.move(ball.xVelocity, ball.yVelocity);
		boundcheck_ball(ball);
		isColliding(ball, pad1, pad2);


		// RENDERING

		window.clear(Color::Black);

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