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
	Font font;
	if (!font.loadFromFile("resources/Pacifico.ttf"))
		return EXIT_FAILURE;

	//option message 
	Text option;
	option.setFont(font);
	option.setCharacterSize(40);
	option.setPosition(200.f, 425.f);
	option.setFillColor(Color::White);
	option.setString("Press Backspace to return");


	// Pads
	PAD pad1;
	// Set length of pad
	pad1.length = 125;

	// Create the rectangle shape with given length and width
	pad1.rect.setSize(Vector2f(pad1.width, pad1.length));
	// Set the orgin
	pad1.rect.setOrigin(pad1.width / 2.f, pad1.length / 2.f);
	// Set the position
	pad1.rect.setPosition(pad1.width + /*the needed distance*/ 30, 400);
	// texture
	pad1.texture.loadFromFile("resources/test.png");
	pad1.rect.setTexture(&pad1.texture);

	PAD pad2;
	// Set length of pad
	pad2.length = 125;

	// Create the rectangle shape with given length and width
	pad2.rect.setSize(Vector2f(pad1.width, pad1.length));
	// Set the orgin
	pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
	// Set the position
	pad2.rect.setPosition(GAMEWIDTH - pad2.width -  /*the needed distance*/ 30, 350);

	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(15);

	// Add texture
	ball.texture.loadFromFile("resources/col.png");
	// Set the positon and orgin
	ball.circle.setPosition(400, 300);
	ball.circle.setOrigin(ballRadius / 2.f, ballRadius / 2.f);

	// States
	//font of score 
	sf::Font scorefont;
	scorefont.loadFromFile("resources/Pacifico.ttf");
  
	// score of player 1  // 3dad score 1 
	float scorep1 = 0;
	std::ostringstream ssScorep1;
	ssScorep1 << scorep1;
	sf::Text lblscorep1;
	lblscorep1.setCharacterSize(30);
	lblscorep1.setPosition(290, 5);
	lblscorep1.setFont(scorefont);
	lblscorep1.setCharacterSize(50);
	lblscorep1.setFillColor(sf::Color::White);
	lblscorep1.setString(ssScorep1.str());


	float scorep2 = 0;
	std::ostringstream ssScorep2;
	ssScorep2 << scorep2;
	//label of score of player 2 
	sf::Text lblscorep2;
	lblscorep2.setCharacterSize(30);
	lblscorep2.setPosition(440, 5);
	lblscorep2.setFont(scorefont);
	lblscorep2.setCharacterSize(50);
	lblscorep2.setFillColor(sf::Color::White);
	lblscorep2.setString(ssScorep1.str());




	// States

		// Keyboard buttons  
	bool W = false, S = false;
	bool Up = false, Down = false;


	// main menu 
	Menu menu(window.getSize().x, window.getSize().y);
	bool men = true;
	//sounds of main menu 
	// main menu song....
	//lesa m7ttsh sound ll menu .......

	//sound of when you press enter.....
	SoundBuffer whenpressed;
	whenpressed.loadFromFile("resources/choose_button.wav");
	Sound whenpressed_detector;
	whenpressed_detector.setBuffer(whenpressed);

	//when return sound....(when you press backspace)
	SoundBuffer whenreturn;
	whenreturn.loadFromFile("resources/switch.wav");
	Sound whenreturn_detector;
	whenreturn_detector.setBuffer(whenreturn);


	//losing/wining message 
	//lw_font 
	Font lw_font;
	lw_font.loadFromFile("resources/Youmurdererbb-pwoK.otf");
	//p1 winning message 
	Text p1win;
	p1win.setCharacterSize(100);
	p1win.setPosition(GAMEWIDTH / 2 - 125, GAMEHEIGHT / 2 - 100);
	p1win.setFillColor(sf::Color::White);
	p1win.setString("p1..Wins");
	p1win.setFont(lw_font);
	//p2 wining message 
	Text p2win;
	p2win.setCharacterSize(100);
	p2win.setPosition(GAMEWIDTH / 2 - 125, GAMEHEIGHT / 2 - 100);
	p2win.setFillColor(sf::Color::White);
	p2win.setString("p2..Wins");
	p2win.setFont(lw_font);
	//in losing/wining bools 
	bool p1win_detector = 0;
	bool p2win_detector = 0;





	// GAME LOOP
	while (window.isOpen())
	{

		// EVENTS
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || isPressed(Keyboard::Escape))
			{
				play = false;
				window.close();
				return 0;
			}


			if (men) {
				if (event.type == Event::KeyReleased) {
					switch (event.key.code)
					{
					case Keyboard::Up:
						menu.MoveUp();
						break;

					case Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						//main menu orders....
						switch (menu.GetPresseditem())
						{
						case 0:
							if (!play)
							{
								play = true;
								whenpressed_detector.play();
								
							}
							break;
						case 1:

							if (!opt) {
								opt = true;
								men = false;
								whenpressed_detector.play();

							}
							break;

						case 2:
							whenpressed_detector.play();
							break;

						case 3:
							whenpressed_detector.play();
							window.close();
							

							break;
						}
						break;
					}


					break;
				}
			}
			//the way that leads to main menu (dos backspace htrg3 llmenu mn ay 7eta)
			if (isPressed(Keyboard::BackSpace)) {
				opt = false;
				men = true;
				p1win_detector = 0;
				p2win_detector = 0;
				play = 0;
				//when you press return sound......
				whenreturn_detector.play();
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
			// Movement

		// Pad1 Movement
			pad1.velocity = Get_Movement(S, W) * 10;
			pad1.rect.move(0, pad1.velocity);
			boundcheck(pad1);


			// Pad2 Movement
			pad2.velocity = Get_Movement(Down, Up) * 10;
			pad2.rect.move(0, pad2.velocity);
			boundcheck(pad2);

			// Ball Movement
			ball.circle.move(ball.xVelocity, ball.yVelocity);
			boundcheck_ball(ball);
			isColliding(ball, pad1.rect);
			isColliding(ball, pad2.rect);

			// Check collisions between the ball and the screen with x axis // score of player 1 
			if (ball.circle.getPosition().x +10 < 0.f)
			{
				scorep2++;
				ssScorep2.str("");
				ssScorep2 << scorep2;
				lblscorep2.setString(ssScorep2.str());
				p1win_detector = 1;
			}

			// Check collisions between the ball and the screen with x axis // score of player 2
			if (ball.circle.getPosition().x -10 > GAMEWIDTH)
			{
				scorep1++;
				ssScorep1.str("");
				ssScorep1 << scorep1;
				lblscorep1.setString(ssScorep1.str());
				p2win_detector = 1;
			}

		}

		//Determing the end point of game
		if (scorep1 == 10 || scorep2 == 10) {
			play = false;
		}

		// reset the score of p1 and p2 
		if (!play) {
			scorep1 = 0;
			ssScorep1.str("");
			ssScorep1 << scorep1;
			lblscorep1.setString(ssScorep1.str());


			scorep2 = 0;
			ssScorep2.str("");
			ssScorep2  << scorep2;
			lblscorep2.setString(ssScorep2.str());

			
		}

		// RENDERING

		window.clear(Color::Black);

		if (play) {
			// Draw pads and ball
			window.draw(ball.circle);
			window.draw(pad1.rect);
			window.draw(pad2.rect);
			//draw score of player 1 
			window.draw(lblscorep1);

			//draw score of player 2
			window.draw(lblscorep2);
			men = false;
		}

		
		else {
		     //rendering p1 winning message 
		     if (p1win_detector) {
			
			window.draw(p1win);
			window.draw(option);
		     }

		     //rendering p2 winning message 
		    if (p2win_detector) {

			window.draw(p2win);
			window.draw(option);
		    }

		    //render option window 
		    if (opt) {
				window.draw(option);
				men = false;
			}
			// Rendering main menu 
			if (men) {
				menu.Draw(window);
		
			}
		}

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}