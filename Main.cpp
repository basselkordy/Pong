// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
#include "Menu.h"
#include <sstream>
using namespace sf;
int main(void)
{


	// Sounds

	// Set to true/false to activate or mute
	bool sfxSwitch = true;
	bool musicSwitch = true;

		//sounds of main menu 

		// Theme music
		Music theme;
		theme.openFromFile("resources/sfx/main_menu/theme.ogg");
		theme.setLoop(true);
		if (musicSwitch)
		{
			theme.play();
		}

		//sound of when you press enter.....
		SoundBuffer whenpressed;
		whenpressed.loadFromFile("resources/sfx/main_menu/choose_button.wav");
		Sound whenpressed_detector;
		whenpressed_detector.setBuffer(whenpressed);

		//when return sound....(when you press backspace)
		SoundBuffer whenreturn;
		whenreturn.loadFromFile("resources/sfx/main_menu/switch.wav");
		Sound whenreturn_detector;
		whenreturn_detector.setBuffer(whenreturn);




		// Ball sounds
		// Score
		SoundBuffer scor;
		scor.loadFromFile("resources/sfx/fire/score.wav");
		Sound score_sound;
		score_sound.setBuffer(scor);
		// Wall hit
		SoundBuffer wall;
		wall.loadFromFile("resources/sfx/fire/wall.wav");
		Sound wall_hit;
		wall_hit.setBuffer(wall);
		// Pad hit
		SoundBuffer pad;
		pad.loadFromFile("resources/sfx/fire/pad.wav");
		Sound pad_hit;
		pad_hit.setBuffer(pad);


		// Background

		Music background;
		background.openFromFile("resources/sfx/fire/background.ogg");
		background.setLoop(true);


		// Powerups

		// Elongate
		SoundBuffer Elon_bfr;
		Elon_bfr.loadFromFile("resources/sfx/powerups/elongate.wav");
		Sound elongate_sound;
		elongate_sound.setBuffer(Elon_bfr);

		// Freeze
		SoundBuffer frz_bfr;
		frz_bfr.loadFromFile("resources/sfx/powerups/freeze.wav");
		Sound freeze_sound;
		freeze_sound.setBuffer(frz_bfr);

		// Slow
		SoundBuffer slow_bfr;
		slow_bfr.loadFromFile("resources/sfx/powerups/slow.wav");
		Sound slow_sound;
		slow_sound.setBuffer(slow_bfr);

		// Dissapear
		SoundBuffer dspr_bfr;
		dspr_bfr.loadFromFile("resources/sfx/powerups/dissapear.wav");
		Sound dissapear_sound;
		dissapear_sound.setBuffer(dspr_bfr);






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
	if (!font.loadFromFile("resources/fonts/Pacifico.ttf"))
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
	pad2.rect.setSize(Vector2f(pad2.width, pad2.length));
	// Set the orgin
	pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
	// Set the position
	pad2.rect.setPosition(GAMEWIDTH - pad2.width -  /*the needed distance*/ 30, 350);

	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(15);

	// Set the positon and orgin
	ball.circle.setPosition(400, 300);
	ball.circle.setOrigin(ballRadius / 2.f, ballRadius / 2.f);


	//////powerUps///////

		//longate

		pUp longate; //struct containing powerup attributes
		Clock longC; //clock decleration to work a timer later for how long the powerup stays
			longate.isSpawned = false;
			longate.isActive = false;
			longate.circle.setFillColor(Color::Red); //pUp color
			longate.circle.setRadius(10); //pUp size


		//freeze 

		pUp freeze;
		Clock freezeC;
			freeze.isSpawned = false;
			freeze.isActive = false;
			freeze.circle.setFillColor(Color::Blue); //pUp color
			freeze.circle.setRadius(10); //pUp size	

		//slow

		pUp slow;
		Clock slowC;
			slow.isSpawned = false;
			slow.isActive = false;
			slow.circle.setFillColor(Color::Green); //pUp color
			slow.circle.setRadius(10); //pUp size

		//Invisibility

		pUp invis;
		Clock invisC;
			invis.isSpawned = false;
			invis.isActive = false;
			invis.circle.setFillColor(Color::Magenta); //pUp color
			invis.circle.setRadius(10); //pUp size

	bool frozen1 = 0, frozen2 = 0, slow1 = 0, slow2 = 0, invis1 = 0 , invis2 = 0;  //could be changed later



	// States
	//font of score 
	sf::Font scorefont;
	scorefont.loadFromFile("resources/fonts/Pacifico.ttf");
  
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


	//losing/wining message 
	//lw_font 
	Font lw_font;
	lw_font.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf");
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
								// Stop theme music
								theme.stop();
								// Play background sounds
								if (musicSwitch)
								{
									background.play();
								}
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
				if (musicSwitch)
				{
					theme.play();
				}
				background.stop();
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
				if (!frozen1) //it can only take input if not frozen
				{

					if (slow1) //changing speed depending if slowed or not
					{
						pad1.velocity = Get_Movement(S, W) * 3;
					}
					else
						pad1.velocity = Get_Movement(S, W) * 10;

					pad1.rect.move(0, pad1.velocity);
					boundcheck(pad1);

				}


			// Pad2 Movement
				if (!frozen2)
				{

					if (slow2)
					{
						pad2.velocity = Get_Movement(Down, Up) * 3;
					}
					else
						pad2.velocity = Get_Movement(Down, Up) * 10;

					pad2.rect.move(0, pad2.velocity);
					boundcheck(pad2);
				}

			// Ball Movement
			ball.circle.move(ball.xVelocity, ball.yVelocity);
			// sound_key is a number refering to which sound should be played


			if (boundcheck_ball(ball))
			{
				wall_hit.play();
			}
			
			// Ball hit pad sound
			if (isCollidingFromLeft(ball, pad2.rect) || isCollidingFromRight(ball, pad1.rect))
			{
				if (sfxSwitch)
				{
					pad_hit.play();
				}
			}
			


			//PowerUPS

					//spawn

					// spawns only if no player has the pUp ,
					//it's not yet spawned (prevent multi spawn) and depends on a random number generated (controls spawn rate)
					if (longate.isActive == false && longate.isSpawned == false && rand() % 100 > 90)
					{
						longate.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
						longate.isSpawned = 1; //change spawned state
					}

					if (freeze.isActive == false && freeze.isSpawned == false && rand() % 1000 > 995)
					{
						freeze.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
						freeze.isSpawned = 1; //change spawned state
					}

					if (slow.isActive == false && slow.isSpawned == false && rand() % 1000 > 900)
					{
						slow.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
						slow.isSpawned = 1; //change spawned state
					}

					if (invis.isActive == false && invis.isSpawned == false && rand() % 1000 > 900)
					{
						invis.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
						invis.isSpawned = 1; //change spawned state
					}

			//Deactivate the effect of pUP after it's time is up by tracing how long it has been activated

				//ELONGATE
				if (longate.isActive == true && longC.getElapsedTime() > seconds(6))
				{

					if (pad1.rect.getSize().y != 125) //if the player that has the pUp is p1  (logic could be changed later)
					{
						int len = elongate(pad1, false); //variable for the sake of code readability
						pad1.rect.setSize(Vector2f(pad1.width, len)); // return size of p1 to normal
						pad1.length = len;
						pad1.rect.setOrigin(pad2.width / 2.f, pad1.length / 2.f);
					}
					else  //if the player that has the pUp is p2  (logic could be changed later)
					{
						int len = elongate(pad2, false);  //variable for the sake of code readability
						pad2.rect.setSize(Vector2f(pad2.width, len)); // return size of p1 to normal
						pad2.length = len;
						pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
					}


					longate.isActive = 0; //pUp is no longer active
				}

				//FREEZE
				if (freeze.isActive == true && freezeC.getElapsedTime() > seconds(2))
				{

					if (frozen1) //if the player that has the pUp is p1  (logic could be changed later)
					{
						frozen1 = 0;
						pad1.rect.setFillColor(Color::Magenta);
					}
					else  //if the player that has the pUp is p2  (logic could be changed later)
					{
						frozen2 = 0;
						pad2.rect.setFillColor(Color::White);
					}


					freeze.isActive = 0; //pUp is no longer active
				}

				//SLOW
				if (slow.isActive == true && slowC.getElapsedTime() > seconds(4))
				{

					if (slow1) //if the player that has the pUp is p1  (logic could be changed later)
					{
						slow1 = 0;
						pad1.rect.setFillColor(Color::Magenta);
					}
					else  //if the player that has the pUp is p2  (logic could be changed later)
					{
						slow2 = 0;
						pad2.rect.setFillColor(Color::White);
					}


					slow.isActive = 0; //pUp is no longer active
				}

				//INVIS
				if (invis.isActive == true && invisC.getElapsedTime() > seconds(2))
				{

					if (invis1) //if the player that has the pUp is p1  (logic could be changed later)
					{
						invis1 = 0;
						
					}
					else  //if the player that has the pUp is p2  (logic could be changed later)
					{
						invis2 = 0;
						
					}


					invis.isActive = 0; //pUp is no longer active
				}


				// Check collisions between the ball and the screen with x axis // score of player 1
					/*
							USE THE BALL RADIUS DON'T USE OTHER VALUES
					*/
				if (ball.circle.getPosition().x - ballRadius < 0.f)
				{
					score_sound.play();
					scorep2++;
					ssScorep2.str("");
					ssScorep2 << scorep2;
					lblscorep2.setString(ssScorep2.str());
					// handles the bug of counting more than one point
					RandomPos(ball);
					p1win_detector = 1;
				}


				if (ball.circle.getPosition().x + ballRadius > GAMEWIDTH)
				{
					score_sound.play();
					scorep1++;
					ssScorep1.str("");
					ssScorep1 << scorep1;
					lblscorep1.setString(ssScorep1.str());
					// handle the bug of counting more than one point
					RandomPos(ball);
					p2win_detector = 1;
				}
		}


		//check for collision with ball and pUp and only do so if it's already spawned on screen

				//elongate
				if (longate.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(longate.circle.getGlobalBounds()))
				{
					elongate_sound.play();
					longC.restart(); //reset pUP timer
					longate.isSpawned = 0; //prevent multi spawn
					longate.isActive = 1;


					//if player1 is the one who took the pUP
					if (ball.xVelocity > 0)
					{
						int len = elongate(pad1, true);
						pad1.rect.setSize(Vector2f(pad1.width, len)); //make p1 longer
						pad1.length = len;
						pad1.rect.setOrigin(pad1.width / 2.f, pad1.length / 2.f);
						cout << pad1.rect.getPosition().y << endl;
						if (pad1.rect.getPosition().y + len / 2.f > 600)
						{
							pad1.rect.setPosition(pad1.rect.getPosition().x, GAMEHEIGHT - pad1.length / 2.f);
						}
						else if (pad1.rect.getPosition().y - len / 2.f < 0)
						{
							pad1.rect.setPosition(pad1.rect.getPosition().x, pad1.length / 2.f);
						}
					}
					//if player2 is the one who took the pUP
					else
					{
						int len = elongate(pad2, true);
						pad2.rect.setSize(Vector2f(pad2.width, len)); //make p2 longer
						pad2.length = len;
						pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);

						if (pad2.rect.getPosition().y + len / 2.f > 600)
						{
							pad2.rect.setPosition(pad2.rect.getPosition().x, GAMEHEIGHT - pad2.length / 2.f);
						}
						else if (pad2.rect.getPosition().y - len / 2.f < 0)
						{
							pad2.rect.setPosition(pad2.rect.getPosition().x, pad2.length / 2.f);
						}
					}
				}

				//Freeze
				if (freeze.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(freeze.circle.getGlobalBounds()))
				{
					freeze_sound.play();
					freezeC.restart(); //reset pUP timer
					freeze.isSpawned = 0; //prevent multi spawn
					freeze.isActive = 1;

					//if player1 is the one who took the pUP
					if (ball.xVelocity > 0)
					{
						frozen2 = 1; //make p2 frozen
						pad2.rect.setFillColor(Color::Blue);
					}
					//if player2 is the one who took the pUP
					else
					{
						frozen1 = 1; //make p2 frozen
						pad1.rect.setFillColor(Color::White);
						pad1.rect.setFillColor(Color::Blue);
					}
				}

				//Slow
				if (slow.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(slow.circle.getGlobalBounds()))
				{
					slow_sound.play();
					slowC.restart(); //reset pUP timer
					slow.isSpawned = 0; //prevent multi spawn
					slow.isActive = 1;

					//if player1 is the one who took the pUP
					if (ball.xVelocity > 0)
					{
						slow2 = 1; //make p2 frozen
						pad2.rect.setFillColor(Color::Red);

					}
					//if player2 is the one who took the pUP
					else
					{
						slow1 = 1; //make p2 longer
						pad1.rect.setFillColor(Color::White);
						pad1.rect.setFillColor(Color::Red);
					}
				}

				//Invis 
				if (invis.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(invis.circle.getGlobalBounds()))
				{
					dissapear_sound.play();
					invisC.restart(); //reset pUP timer
					invis.isSpawned = 0; //prevent multi spawn
					invis.isActive = 1;

					//if player1 is the one who took the pUP
					if (ball.xVelocity > 0)
					{
						invis2 = 1; //make p2 frozen
						

					}
					//if player2 is the one who took the pUP
					else
					{
						invis1 = 1; //make p2 longer
						
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
			if (!invis1)
				window.draw(pad1.rect);
			if (!invis2)
				window.draw(pad2.rect);

			//only draw pUP if it's spawned

					//elongate
					if (longate.isSpawned == true)
					{
						window.draw(longate.circle);
					}
					//freeze
					if (freeze.isSpawned == true)
					{
						window.draw(freeze.circle);
					}
					//slow
					if (slow.isSpawned == true)
					{
						window.draw(slow.circle);
					}
					//invis
					if (invis.isSpawned == true)
					{
						window.draw(invis.circle);
					}
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
