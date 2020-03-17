// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
#include "Menu.h"
#include<sstream>
using namespace sf;
	int main(void)
	{

		// Create the main window 
		RenderWindow window(VideoMode(GAMEWIDTH, GAMEHEIGHT), "Pong");

		// Limit FPS to 60
		window.setFramerateLimit(60);


		// Game loop bool
		bool play = false;


		//option selection 
		bool opt = false;
		//option font 
		sf::Font font;
		if (!font.loadFromFile("Pacifico.ttf"))
			return EXIT_FAILURE;

		//option message 
		sf::Text option;
		option.setFont(font);
		option.setCharacterSize(40);
		option.setPosition(200.f, 425.f);
		option.setFillColor(sf::Color::White);
		option.setString("Press Backspace to return");


		// Pads
		PAD pad1;
		// Set length of pad
		pad1.length = 125;

		// Create the rectangle shape with given length and width and position it
		pad1.rect.setSize(Vector2f(pad1.width, pad1.length));
		pad1.rect.setPosition(20, 400);

		// Add texture
		pad1.texture.loadFromFile("resources/test.png");
		pad1.rect.setTexture(&pad1.texture);

		PAD pad2;
		// Set length of pad
		pad2.length = 125;

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
		//font of score 
        sf::Font scorefont;
		scorefont.loadFromFile("Pacifico.ttf");
	    // score of player 1  
		int scorep1 = 0;
		std::ostringstream ssScorep1;
		ssScorep1 << "p1: " << scorep1;
		//label of score of player 1 
		sf::Text lblscorep1;
		lblscorep1.setCharacterSize(30);
		lblscorep1.setPosition(25, 10);
		lblscorep1.setFont(scorefont);
		lblscorep1.setCharacterSize(50);
		lblscorep1.setFillColor(sf::Color::White);
		lblscorep1.setString(ssScorep1.str());
		bool p1score = false;


		// score of player 2  
		int scorep2 = 0;
		std::ostringstream ssScorep2;
		ssScorep2 << "p2: " << scorep2;
		//label of score of player 2 
		sf::Text lblscorep2;
		lblscorep2.setCharacterSize(30);
		lblscorep2.setPosition(675, 10);
		lblscorep2.setFont(scorefont);
		lblscorep2.setCharacterSize(50);
		lblscorep2.setFillColor(sf::Color::White);
		lblscorep2.setString(ssScorep1.str());
		bool p2score = false;



		// States

			// Keyboard buttons  
		bool W = false, S = false;
		bool Up = false, Down = false;


		// main menu 
		Menu menu(window.getSize().x, window.getSize().y);
		bool men = true;

		// GAME LOOP
		while (window.isOpen())
		{

			// EVENTS
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					play = false;
					window.close();
					return 0;
				}


				if (men) {
					if (event.type == sf::Event::KeyReleased) {
						switch (event.key.code)
						{
						case sf::Keyboard::Up:
							menu.MoveUp();
							break;

						case sf::Keyboard::Down:
							menu.MoveDown();
							break;

						case sf::Keyboard::Return:
							switch (menu.GetPresseditem())
							{
							case 0:
								if (!play)
								{
									play = true;
								}
								break;
							case 1:

								if (!opt) {
									opt = true;
									men = false;
								}
								break;
							case 3:
								window.close();
								break;
							}
							break;
						}


						break;
					}
				}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
					opt = false;
					men = true;
				}

				
			}	
			
			
			    // LOGIC

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

				

		
			if (play) {
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
				
		    // Check collisions between the ball and the screen with x axis // score of player 1 
			if (ball.circle.getPosition().x - 10 < 0.f)
			{
				p1score = true;
			}

			// Check collisions between the ball and the screen with x axis // score of player 2
			if (ball.circle.getPosition().x + 10 > GAMEWIDTH)
			{
				p2score = true;
			}

			}

			



			//recording p1 score  
			if (p1score) {
				scorep1++;
				ssScorep1.str("");
				ssScorep1 << "p1: " << scorep1;
				lblscorep1.setString(ssScorep1.str());
				p1score = false;
			}

			//recording p2 score  
			if (p2score) {
				scorep2++;
				ssScorep2.str("");
				ssScorep2 << "p2: " << scorep2;
				lblscorep2.setString(ssScorep2.str());
				p2score = false;
			}

			// reset the score of p1 and p2 
			if (!play) {
				scorep1 = 0;
				ssScorep1.str("");
				ssScorep1 << "p1: " << scorep1;
				lblscorep1.setString(ssScorep1.str());


				scorep2 = 0;
				ssScorep2.str("");
				ssScorep2 << "p2: " << scorep2;
				lblscorep2.setString(ssScorep2.str());
			}

			// RENDERING

			window.clear(Color::Black);

			if (play) {
				// Draw pads and ball
				window.draw(pad1.rect);
				window.draw(pad2.rect);
				window.draw(ball.circle);
				//draw score of player 1 
				window.draw(lblscorep1);

				//draw score of player 2
				window.draw(lblscorep2);
			}

			else {
				//render option window 
				if (opt) {
					window.draw(option);
					men = false;
				}
				// Rendering main menu 
				if (men)
					menu.Draw(window);
			}

			window.display();

		}

		// Clean up
		window.close();
		return 0;


	}