// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
#include "leaderboard.h"
#include "Menus.h"
#include "powerups.h"
#include <sstream>
#include "menus options.h"
#include "log.h"

using namespace sf;
using namespace std;

int main(void)
{
	bool themePlaying = true;

	//MODE(t for training, 2 for 2 player , a for ai)
	char MODE ;

	/// SFX ///
	//searchSound

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



	// Main Window
	//searchMainWindow

	// Create the main window
	RenderWindow window(VideoMode(GAMEWIDTH, GAMEHEIGHT), "Pong");

	// Limit FPS to 60
	window.setFramerateLimit(60);

	// Game loop bool
	bool play = false;


	/// Menus ///
	//searchMenus

	//Options
	//option selection
	bool opt = false;

	//option font
	Font font;
	if (!font.loadFromFile("resources/fonts/Pacifico.ttf"))
		return EXIT_FAILURE;

	//option message
	Text option;
	textInit(option,font);


	//Main Menu
	MENU mainMenu;
	Text menuItems[5];
	setMainMenu(mainMenu, menuItems, GAMEWIDTH, GAMEHEIGHT);
	bool men = true;

	///// switch fo switching up and down /////
	bool switcher = true;



	//Pause Menu
	bool pause = false;
	MENU pMenu;
	Text pauseItems[3];
	setPauseMenu(pMenu, pauseItems, GAMEWIDTH, GAMEHEIGHT);


	//Scores / Win lose
	//Score
	//font of score
	sf::Font scorefont;
	scorefont.loadFromFile("resources/fonts/Pacifico.ttf");

	// score of players
	float scorep1 = 0;
	float scorep2 = 0;

	ostringstream ssScorep1;
	ostringstream ssScorep2;

	ssScorep1 << scorep1;
	ssScorep2 << scorep2;

	//label of score of players
	sf::Text lblscorep2;
	sf::Text lblscorep1;

	textInit(lblscorep1, scorefont, ssScorep1, 1);
	textInit(lblscorep2, scorefont, ssScorep2, 2);



	//Win lose
	//losing/wining message
	//lw_font
	Font lw_font;
	lw_font.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf");
	//p1 winning message
	Text pWin;
	textInit(pWin, lw_font,'W');
	//in losing/wining bools
	bool p1win_detector = 0;
	bool p2win_detector = 0;


	/// Game Components ///
	//searchGameComp

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

	//Powerups
	// Declaration of powersups and setting their textures and radii
	pUp longate;
	pUp freeze;
	pUp slow;
	pUp invis;
	pUp reverse;
	initialize_powerups(reverse,longate, freeze, slow, invis, Elon_bfr, frz_bfr, slow_bfr, dspr_bfr);


	///Leaderboard ///
	//searchLeaderboard

	//////////Player Info and Leaderboard///////////
	Text playerText;
	Text messagePlayerText;

	string playerName1;
	string playerName2;

	bool getPlayerName = false;
	bool leader = false;
	bool savePlayer1 = false;
	bool savePlayer2 = false;


	//Themes
	//searchTheme
	char c = 'h'; //indicate theme
	Texture backgT; //background
	RectangleShape backg;
	backg.setSize(Vector2f(800.0, 600.0));

   set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, c);


	// States

	// Keyboard buttons
	bool W = false, S = false;
	bool Up = false, Down = false;


	////////////////////////////////////////////////// GAME LOOP ///////////////////////////////////////////////////////////////////////////



	while (window.isOpen())
	{

		// EVENTS
		//searchEvents
		while (window.pollEvent(event))
		{
			//Close game
			if (event.type == Event::Closed || isPressed(Keyboard::Escape))
			{
				play = false;
				window.close();
				return 0;
			}
			if (opt)
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					place++;
					place %= 3;
					cout << place << '\n';
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					if (!place)
						place = 3;
					place--;
					cout << place << '\n';
				}
				ChangeVolumebyClick(window);
				SubmitTheme();
			}
			
			
			
			

			//Menus
			//searchMenus
			//searchSound

			//Pause Menu Events/Sound
			if (pause)
			{
				/////// to navigate in pause menu 
				mouse_navigator(pMenu, pauseItems,0.0067, window);
				if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased)
				{
					//function contains switch statment
					pauseEvents(event, pMenu, pauseItems, whenreturn_detector, whenpressed_detector, background, theme, pause, opt, getPlayerName, play, men, musicSwitch);
					break;
				}
			}

			//Options Menu Events/Sound
			if (opt)
			{
				
				VolumeChanger(window);
				theme.setVolume(VolumeValue);
			}

			//Main Menu Events/Sound
			if (men) {
				//// to navigate in main menu   
				mouse_navigator(mainMenu, menuItems,0.01, window);
				//Event
				cout << pos_Mouse.y - pos_Mouse.x << endl;
				if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased) {
					//Navigation
					//function contains switch statment
					mainmenuEvents(mainMenu, menuItems, play, musicSwitch, theme, background, getPlayerName, men, whenpressed_detector, MODE, opt, leader, window);
					break;
				}


			}

			//Name input
			if (getPlayerName)
			{
				if (MODE == 'a')
				{
					if (!savePlayer1)
					{
						playerName1 = "AI";
						playerText.setString(playerName1);
						savePlayer1 = true;
					}
					else if (!savePlayer2)
					{
						nameInput(event, playerName2, getPlayerName, playerText, play, 2, savePlayer2);
					}
				}
				else if (MODE == '2')
				{
					cout << savePlayer1 << savePlayer2 << endl;
					if (!savePlayer1)
					{
						nameInput(event, playerName1, getPlayerName, playerText, play, 1, savePlayer1);
					}
					else if (!savePlayer2)
					{
						nameInput(event, playerName2, getPlayerName, playerText, play, 2, savePlayer2);
						cout << playerName1 << playerName2 << endl;
					}
				}
			}

			//the way that leads to main menu (dos backspace htrg3 llmenu mn ay 7eta)
			if (isPressed(Keyboard::BackSpace) && !getPlayerName)
			{
				menuReturn(leader, opt, getPlayerName, play, men, themePlaying, background, theme, pause, p1win_detector, p2win_detector, whenpressed_detector);
			}

			//pause

		}


		/// LOGIC ///
		//Handling player naming
		if (!savePlayer1)
		{
			textInit(playerText, messagePlayerText, font, 1);
		}
		else if (!savePlayer2)
		{
			if (MODE == 'a')
			{
				textInit(playerText, messagePlayerText, font, 1);
			}
			else
			{
				textInit(playerText, messagePlayerText, font, 2);
			}
		}

		//Movement
		//searchGameComp
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

		/////reset the game after close /////

		//Menu
		if (men)
		{
			savePlayer1 = false;
			savePlayer2 = false;
			if (!playerName1.empty())
			{
				playerName1.erase();
				playerText.setString("");
			}
			if (!playerName2.empty())
			{
				playerName2.erase();
				playerText.setString("");
			}
		}

		//Reset Components
		//searchGameComp
		if (!play)
		{
			RandomPos(ball);
			pad1.ResetPad(1);
			pad2.ResetPad(2);

			////reseting power ups /////////////
			longate.isSpawned = 0; longate.isActive = 0;
			freeze.isSpawned = 0;  freeze.isActive = 0;
			slow.isSpawned = 0;    slow.isActive = 0;
			invis.isSpawned = 0;    invis.isActive = 0;
			//reverse.isSpawned = 0;    reverse.isActive = 0;
		}

		//Game Mechanics
		//searchGameMechanics (Movement - Sound / Collision - Powerups)
		//searchSound
		if (play && !pause && !opt)
		{
			//Movement
			// Pad1 Movement
			//depends on the mode
			Modes(pad1, ball, MODE, pad1.isFrozen, pad1.isSlow, W, S);


			// Pad2 Movement
			if (pad2.isReverse)
			{
				pad2.velocity = pad2.Get_Movement(Up, Down);
			}
			else
			{
				pad2.velocity = pad2.Get_Movement(Down, Up);
			}

			pad2.rect.move(0, pad2.velocity);
			pad2.boundcheck();


			// Ball Movement
			ball.circle.move(ball.xVelocity, ball.yVelocity);

			//Sound / Collisions
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


			// PowerUP
			// Spawn
			SpawnPowerups(reverse, longate, freeze, slow, invis, MODE);

			// Activate
			isTakenPowerup(reverse, longate, freeze, slow, invis, ball, pad1, pad2, sfxSwitch);

			// Deactivate the effect of pUP after it's time is up by tracing how long it has been activated
			DeactivatePowerups(reverse, longate, freeze, slow, invis, pad1, pad2);


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
		if (scorep1 == 1)
		{
			p1win_detector = 1;
			gameOver(playerName1);
			addToLog(playerName1, playerName2);
			play = false;
			themePlaying = false;

		}
		else if (scorep2 == 1)
		{
			p2win_detector = 1;
			gameOver(playerName2);
			addToLog(playerName2, playerName1);
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
		//searchRender
		window.clear(Color::Black);

		if (getPlayerName)
		{
			window.draw(messagePlayerText);
			window.draw(playerText);
		}

		if (play)
		{
			 DrawGame(window, backg, pad1, pad2, ball, lblscorep1, lblscorep2);
			 DrawPowerups(window, longate, freeze, slow, invis, reverse);
			 men = false;

			//rendering pause window(draw pause window if option window is not opened)
			 if (pause && !opt)
				 drawMenu(window, pauseItems, 3);

			if (opt) {
				DrawOptionMenu(window);
				men = false;
				window.draw(option);

			}
		}
		else
		{
			//rendering winning message
			//p1 win
			if (p1win_detector) {
				pWin.setString(playerName1 + " wins");
				cout << playerName1 << endl;
				window.draw(pWin);
				window.draw(option);

			}
			//p2 win
			if (p2win_detector) {
				pWin.setString(playerName2 + " wins");
				cout << playerName2 << endl;
				window.draw(pWin);
				window.draw(option);
			}


			//render option window
			//searchMenus
			if (opt) {
				DrawOptionMenu(window);
				men = false;
				window.draw(option);

			}

			// Rendering main menu
			if (men) {
				drawMenu(window, menuItems, 5);

			}
			if (leader)
			{
				viewLeaderboard(window);
			}

		}

		if (opt)
		{
			SelectTheme();
			// To See which of the themes is choosen
			for (int x = 0; x < 3; x++)
			{
				if (Steps[x] == PADDING && isChoosen[x] && !done)
				{
					themeChange(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, c, scor, background_bfr,x);
				}
			}

		}

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}
