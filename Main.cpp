// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
#include "leaderboard.h"
#include "Menu.h"
#include "Optionmenu.h"
#include "pauseMenu.h"
#include "powerups.h"
#include <sstream>

using namespace sf;
int main(void)
{
	bool themePlaying = true;

	//MODE(t for training, 2 for 2 player , a for ai)
	char MODE ;

	// THEMES //

	bool hell = false, ice = false, forest = false; //still no use but could be helpful when switching ingame
	char c = 'f'; //indicate theme
	Texture backgT; //background
	RectangleShape backg; 
	backg.setSize(Vector2f(800.0, 600.0));
	
	// Sounds

	// Set to true/false to activate or mute
	
	bool musicSwitch = true;
	bool sfxSwitch = true;

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




	// Sound 

	// Score
	SoundBuffer scor;
	Sound score_sound;
	score_sound.setBuffer(scor);

	// Wall hit
	SoundBuffer wall;
	Sound wall_hit;
	wall_hit.setBuffer(wall);

	// Pad hit
	SoundBuffer pad;
	Sound pad_hit;
	pad_hit.setBuffer(pad);


	// Background
	SoundBuffer background_bfr;
	Sound background;
	background.setBuffer(background_bfr);
	background.setLoop(true);

	// Powerups sound buffers
	SoundBuffer Elon_bfr;
	Elon_bfr.loadFromFile("resources/sfx/powerups/elongate.wav");

	SoundBuffer frz_bfr;
	frz_bfr.loadFromFile("resources/sfx/powerups/freeze.wav");

	SoundBuffer slow_bfr;
	slow_bfr.loadFromFile("resources/sfx/powerups/slow.wav");

	SoundBuffer dspr_bfr;
	dspr_bfr.loadFromFile("resources/sfx/powerups/dissapear.wav");




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
	pad1.ResetPad(1);

	PAD pad2;
	pad2.ResetPad(2);

	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(ballRadius);

	// Set the positon and orgin
	ball.circle.setPosition(400, 300);
	ball.circle.setOrigin(ballRadius, ballRadius);



	// Declaration of powersups and setting their textures and radii
	pUp longate;
	pUp freeze;
	pUp slow;
	pUp invis;
	initialize_powerups(longate, freeze, slow, invis, Elon_bfr, frz_bfr, slow_bfr, dspr_bfr);



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
	///// switch fo switching up and down /////
	bool switcher = true;
	//lvl of volume in game 
	Optionmenu Level_of_volume(window.getSize().x, window.getSize().y);
	//theme changer/////////
    Optionmenu change_the_theme(window.getSize().x, window.getSize().y);

	//pause menu
	bool pause = false;
	pauseMenu pMenu(window.getSize().x, window.getSize().y);


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

	//////////Player Info and Leaderboard///////////
	sf::Text playerText;
	bool getPlayerName = false;
	string playerName;
	string playerUser1;
	playerText.setFont(font);
	playerText.setCharacterSize(40);
	playerText.setPosition(200.f, 425.f);
	playerText.setFillColor(Color::White);
	sf::Text messagePlayerText;
	messagePlayerText.setFont(font);
	messagePlayerText.setCharacterSize(40);
	messagePlayerText.setPosition(100.f, 100.f);
	messagePlayerText.setFillColor(Color::White);
	messagePlayerText.setString("Please enter thy name!");
	bool leader = false;


	////theme test
	set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, c);




	////////////////////////////////////////////////// GAME LOOP ///////////////////////////////////////////////////////////////////////////
	


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

			//pause menu events
			if (pause)
			{
				if (event.type == Event::KeyReleased)
				{
					switch (event.key.code)
					{
						case Keyboard::Up:
							pMenu.moveUp();
							whenreturn_detector.play();
							break;

						case Keyboard::Down:
							pMenu.moveDown();
							whenreturn_detector.play();
							break;

						case Keyboard::Return:
							switch (pMenu.getPresseditem())
							{
								//resume
							case 0:
								if (pause)
								{
									pause = false;
									whenpressed_detector.play();
									break;
								}
								//open option menu
							case 1:
								opt = true;
								pause = false;
								whenpressed_detector.play();
								break;
								//exit
							case 2:
								whenpressed_detector.play();
								getPlayerName = false;
								play = false;
								pause = false;
								men = true;
								if (musicSwitch)
								{
									background.stop();
									theme.play();

								}
								break;
							}
					
						break;
					}
					break;
					
				}
			}
	

			/////volume changer ///////
			////volume change event //////////
			if (opt) {
				
				if (event.type == Event::KeyReleased) {
					switch (event.key.code)
					{
					case Keyboard::Right:
						if (switcher)
							Level_of_volume.MoveRight();
						else
							change_the_theme.MoveRight();
						break;

					case Keyboard::Left:
						if (switcher)
							Level_of_volume.MoveLeft();
						else
							change_the_theme.MoveLeft();
					
						break;
				
					case Keyboard::Up:
						Level_of_volume.MoveUp();
						change_the_theme.MoveUp();
						switcher = true;
						break;

					case Keyboard::Down:
						Level_of_volume.MoveDown();
						change_the_theme.MoveDown();
						switcher = false;
						break;
					case sf::Keyboard::Return:

						///volume changer /////////
						if (switcher)	/// this for switching up and down 
						{
							switch (Level_of_volume.GetVolumechange())
							{
							case 0:
								theme.setVolume(0);
								background.setVolume(0);

								break;
							case 1:
								theme.setVolume(25);
								background.setVolume(25);

								break;

							case 2:
								theme.setVolume(50);
								background.setVolume(50);
								break;

							case 3:
								theme.setVolume(75);
								background.setVolume(75);

								break;

							case 4:
								theme.setVolume(100);
								background.setVolume(100);
								break;
							}

						}

						// theme changer
						
						else
						{
							switch (change_the_theme.GetThemechange())
							{
							case 0:

								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'h');
								c = 'h';
								break;
							case 1:
								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'i');
								c = 'i';
								break;

							case 2:
								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'f');
								c = 'f';
								break;

							}

						}

						break;
					}
                     break;
				}
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
								if (musicSwitch)
								{
									theme.pause();
									background.play();
								}
								getPlayerName = true;
								play = false;
								men = false;
								whenpressed_detector.play();
								MODE = 'a';

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
							if (!leader)
							{
								leader = true;
								men = false;
								whenpressed_detector.play();
							}
							break;

						case 3:
							whenpressed_detector.play();
							play = true;
							if (musicSwitch)
							{
								theme.pause();
								background.play();
							}
							MODE = 't';
							break;

						case 4:
							whenpressed_detector.play();
							window.close();
							break;
						}
						break;
					}
					break;
				}

		
			}
			if (getPlayerName)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b')
					{
						if (!playerName.empty())
						{
							playerName.erase(playerName.size() - 1);
							playerText.setString(playerName);
						}
					}
					else
					{
						playerName += event.text.unicode;
						playerText.setString(playerName);
					}
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					addPlayers(playerName);
					getPlayerName = false;
					playerText.setString("");
					play = true;
				}
			}
			//the way that leads to main menu (dos backspace htrg3 llmenu mn ay 7eta)
			if (isPressed(Keyboard::BackSpace) && !getPlayerName)
			{
				leader = false;
				opt = false;
				getPlayerName = false;
				if (!play)
				{
					men = true;
					if (!themePlaying)
					{
						background.stop();
						theme.play();
						themePlaying = true;
					}
				}
				else
					pause = true;

				p1win_detector = 0;
				p2win_detector = 0;
				
				//when you press return sound......
				whenreturn_detector.play();
			}

			//pause
			if (isPressed(Keyboard::P)) {
				pause = true;
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

		/////reset the game after close /////////////////////
		if (men)
		{
			if (!playerName.empty())
			{
				playerName.erase();
				playerText.setString("");
			}
		}
		if (!play)
		{
			RandomPos(ball);
			pad1.ResetPad(1);
			pad2.ResetPad(2);

			////reseting power ups /////////////
			longate.isSpawned = 0; longate.isActive == 1;
			freeze.isSpawned = 0;  freeze.isActive == 1;
			slow.isSpawned = 0;    slow.isActive == 1;
			invis.isActive = 0;    invis.isActive == 1;			
		}

		if (play && !pause && !opt)
		{


			// Pad1 Movement
			//depends on the mode
			Modes(pad1, ball, MODE, pad1.isFrozen, pad1.isSlow, W, S);


			// Pad2 Movement
			pad2.velocity = pad2.Get_Movement(Down, Up);
			pad2.rect.move(0, pad2.velocity);
			pad2.boundcheck();
			

			// Ball Movement
			ball.circle.move(ball.xVelocity, ball.yVelocity);
			
			// Ball hit wall sound
			if (boundcheck_ball(ball))
			{
				if (sfxSwitch)
				{
					wall_hit.play();
				}
			}

			// Ball hit pad sound
			if (isCollidingFromLeft(ball, pad2.rect) || isCollidingFromRight(ball, pad1.rect))
			{
				if (sfxSwitch)
				{
					pad_hit.play();
				}
			}


			// PowerUPS

			// Spawn
			SpawnPowerups(longate, freeze, slow, invis, MODE);

			// Activate
			isTakenPowerup(longate, freeze, slow, invis, ball, pad1, pad2, sfxSwitch);

			// Deactivate the effect of pUP after it's time is up by tracing how long it has been activated
			DeactivatePowerups(longate, freeze, slow, invis, pad1, pad2);


			// Check collisions between the ball and the screen with x axis // score of player 1
				/*
						USE THE BALL RADIUS DON'T USE OTHER VALUES
				*/
			if (ball.circle.getPosition().x - ballRadius < 0.f)
			{
				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep2++;
				ssScorep2.str("");
				ssScorep2 << scorep2;
				lblscorep2.setString(ssScorep2.str());
				// handles the bug of counting more than one point
				RandomPos(ball);
			}


			if (ball.circle.getPosition().x + ballRadius > GAMEWIDTH)
			{
				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep1++;
				ssScorep1.str("");
				ssScorep1 << scorep1;
				lblscorep1.setString(ssScorep1.str());
				// handle the bug of counting more than one point
				RandomPos(ball);
			}
		}

		//Determing the end point of game
		if (scorep1 == 10)
		{
			p2win_detector = 1;
			play = false;
			themePlaying = false;

		}
		else if (scorep2 == 10)
		{
			p1win_detector = 1;
			gameOver(playerName);
			playerName.clear();
			play = false;
			themePlaying = false;
		}

		// reset the score of p1 and p2 
		if (!play) {
			scorep1 = 0;
			ssScorep1.str("");
			ssScorep1 << scorep1;
			lblscorep1.setString(ssScorep1.str());


			scorep2 = 0;
			ssScorep2.str("");
			ssScorep2 << scorep2;
			lblscorep2.setString(ssScorep2.str());
		}

		// RENDERING

		window.clear(Color::Black);

		if (getPlayerName)
		{
			window.draw(messagePlayerText);
			window.draw(playerText);
		}

		 if (play)
		 {
			 DrawGame(window, backg, pad1, pad2, ball, lblscorep1, lblscorep2);
			 DrawPowerups(window, longate, freeze, slow, invis);
			 men = false;

			//rendering pause window(draw pause window if option window is not opened)
			if (pause && !opt)
				pMenu.DRAW(window);

			if (opt) {
				window.draw(option);
				men = false;
				Level_of_volume.drawvolume(window);
				change_the_theme.drawtheme(window);
			}
		}


		else 
		{
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
				Level_of_volume.drawvolume(window);
				change_the_theme.drawtheme(window);
			}
			// Rendering main menu 
			if (men) {
				menu.Draw(window);

			}
			if (leader)
			{
				viewLeaderboard(window);
			}

		}

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}
