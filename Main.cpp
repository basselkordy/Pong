// Headers containing custom functions, includes, structs definitons, and the Event object
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
	LOAD_USER_SETTINGS(USER_SETTINGS);	
	choosenTheme = USER_SETTINGS[0];
	switch (choosenTheme)
	{
	case 'h':
		place = 0;
		break;
	case 'f':
		place = 1;
		break;
	case 'i':
		place = 2;
		break;
	case 'c':
		place = 3;
		break;
	}
	bool themePlaying = true;
	//MODE(t for training, 2 for 2 player , a for ai)
	char MODE = 'a';

	/// SFX ///
	//searchSound

	// Set to true/false to activate or mute

	bool musicSwitch = 1;
	bool sfxSwitch = 1;

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

	SoundBuffer rvrs_bfr;
	rvrs_bfr.loadFromFile("resources/sfx/powerups/reverse.wav");

	SoundBuffer shrt_bfr;
	shrt_bfr.loadFromFile("resources/sfx/powerups/shorten.wav");

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

	///////////// main menu background ////////////////
	Texture menu_back;
	menu_back.loadFromFile("resources/Menu Background.png");

	RectangleShape menub;
	menub.setSize(Vector2f(800, 600));
	menub.setTexture(&menu_back);

	Texture menu_back2;
	menu_back2.loadFromFile("resources/Menu.png");

	RectangleShape menu2;
	menu2.setSize(Vector2f(800, 600));
	menu2.setTexture(&menu_back2);
	Clock time;
	////////////////////////////////////////////////////

	//Options
	//option selection
	bool opt = false;

	//option font
	Font font;
	if (!font.loadFromFile("resources/fonts/ARCADECLASSIC.ttf"))
		return EXIT_FAILURE;

	//option message
	Text option;
	textInit(option,font);


	//Main Menu
	MENU mainMenu;
	RectangleShape menuItems[5];
	setMainMenu(mainMenu, menuItems, GAMEWIDTH, GAMEHEIGHT);
	bool men = true;

	// modes 
	MENU modes_s;
	RectangleShape modesItems[2];
	modes_display(modes_s, modesItems, GAMEWIDTH, GAMEHEIGHT);
	bool mode_is = false ;

	///// switch fo switching up and down /////
	bool switcher = true;

	//////////// bool asked by badr /////////////
	bool maps = false;


	//Pause Menu
	bool pause = false;
	MENU pMenu;
	RectangleShape pauseItems[3];
	setPauseMenu(pMenu, pauseItems, GAMEWIDTH, GAMEHEIGHT);


	//Scores / Win lose
	//Score
	//font of score
	sf::Font scorefont;
	scorefont.loadFromFile("resources/fonts/ARCADECLASSIC.ttf");

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
	lw_font.loadFromFile("resources/fonts/ARCADECLASSIC.ttf");
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
	pad1.ResetPad(1,MODE);

	PAD pad2;
	pad2.ResetPad(2,MODE);

	PAD pad3, pad4;

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
	pUp shorten;
	initialize_powerups(reverse, longate, freeze, slow, invis, shorten, Elon_bfr, frz_bfr, slow_bfr, dspr_bfr, rvrs_bfr, shrt_bfr);


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
	char c = USER_SETTINGS[0]; //indicate theme
	Texture backgT; //background
	RectangleShape backg;
	backg.setSize(Vector2f(800.0, 600.0));

  


	// States
   bool mapKeys = true;
 
	// Keyboard buttons
	bool W = false, S = false;
	bool Up = false, Down = false;


	//Map
	RectangleShape obstacleTop, obstacleBot;
	Texture obsTopTex,obsBotTex;
	

	mapNum = USER_SETTINGS[1];
	setSelectedMap();

	set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, c, obstacleTop, obstacleBot , obsTopTex, obsBotTex);
	
	choosing_arrow.setPosition(40, 280);
	////////////////////////////////////////////////// GAME LOOP ///////////////////////////////////////////////////////////////////////////



	while (window.isOpen())
	{

	
		pos_Mouse = Mouse::getPosition(window);
		// EVENTS
		//searchEvents
		while (window.pollEvent(event))
		{
			//Close game
			if (event.type == Event::Closed || isPressed(Keyboard::Escape))
			{
				SAVE_USER_SETTINGS(USER_SETTINGS);
				play = false;
				window.close();
				return 0;
			}

			if (opt && !play)
			{
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					place++;
					place %= 4;
					//cout << place << '\n';
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
				if (!place)
					place = 4;
				place--;
					//cout << place << '\n';
				}
			
				SubmitTheme();
			}

			//Menus
			//searchMenus
			//searchSound

			//Pause Menu Events/Sound
			if (pause)
			{
				
				if (event.type == Event::KeyReleased)
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
				ChangeVolumebyClick(window);
				theme.setVolume(VolumeValue);
			}
			
			///// maps Events ////////////
			if (maps) {
				

				if (Keyboard::isKeyPressed(Keyboard::Up) && !mapKeys)
					mapKeys = true;
				if (Keyboard::isKeyPressed(Keyboard::Down) && mapKeys)
					mapKeys = false;

				if (mapKeys)
				{
					choosing_arrow.setPosition(40, 280);
					

					
				}
				else
				{
					choosing_arrow.setPosition(40, GAMEHEIGHT - 80);
					
					
				}
				
				/// here you will but the events function and other related functions "badr"  as the following wa as you like brdo ////////
				if (
					(Mouse::isButtonPressed(Mouse::Left) && IsMouseIn(maps_rect[right_map]))
					||
					(Keyboard::isKeyPressed(Keyboard::Right) &&mapKeys)
					)
				{
					for (int i = 0; i < 4; i++)
						setState(maps_rect[i], true, i);
					
					
				}
				else if (
					(Mouse::isButtonPressed(Mouse::Left) && IsMouseIn(maps_rect[left_map]))
					||
					(Keyboard::isKeyPressed(Keyboard::Left) && mapKeys)
					)
				{
					for (int i = 0; i < 4; i++)
						setState(maps_rect[i], false, i);
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					getPlayerName = true;
					maps = false;
					set_map(obstacleTop, obstacleBot, pad3, pad4, mapNum);
				}
				
			}
			if (mode_is && !mapKeys) {
				if (event.type == Event::KeyReleased) {
					modesEvents(modes_s, modesItems, play, musicSwitch, theme, background, whenpressed_detector, MODE, window);
				}
			}

			//Main Menu Events/Sound
			if (men) {
				//Event
				if (event.type == Event::KeyReleased) {
					//Navigation
					//function contains switch statment
					mainmenuEvents(mainMenu, menuItems, mode_is,maps,play, musicSwitch, theme, background, getPlayerName, men, whenpressed_detector, MODE, opt, leader, window, USER_SETTINGS);
					break;
				}

			}

			//Name input
			if (getPlayerName)
			{
				if (MODE == 'a')
				{
					getNameBoxTex.loadFromFile("resources/menu tex/getPlayerName.png");
					getNameBox.setTexture(&getNameBoxTex);
					getNameBox.setSize(Vector2f(700, 100));
					getNameBox.setOrigin(getNameBox.getSize().x / 2, getNameBox.getSize().y / 2);
					getNameBox.setPosition(GAMEWIDTH / 2, 110);

					textBoxTex.loadFromFile("resources/menu tex/textBox.png");
					textBox.setTexture(&textBoxTex);
					textBox.setSize(Vector2f(700, 105));
					textBox.setOrigin(textBox.getSize().x / 2, textBox.getSize().y / 2);
					textBox.setPosition(GAMEWIDTH / 2, 315);

					if (!savePlayer1)
					{
						playerName1 = "AI";
						playerText.setString(playerName1);
						playerText.setOrigin(playerText.getGlobalBounds().width / 2, playerText.getGlobalBounds().height / 2);
						playerText.setPosition(GAMEWIDTH / 2, -10);
						playerText.setFillColor(Color::White);
						savePlayer1 = true;
						
					}
					else if (!savePlayer2)
					{
						nameInput(event, playerName2, getPlayerName, playerText, play, 2, savePlayer2);
					}
				}
				else if (MODE == '2')
				{
					//cout << savePlayer1 << savePlayer2 << endl;
					if (!savePlayer1)
					{
						nameInput(event, playerName1, getPlayerName, playerText, play, 1, savePlayer1);
					}
					else if (!savePlayer2)
					{
						nameInput(event, playerName2, getPlayerName, playerText, play, 2, savePlayer2);
						//cout << playerName1 << playerName2 << endl;
					}
				}
				
			}

			//the way that leads to main menu (dos backspace htrg3 llmenu mn ay 7eta)
			if (isPressed(Keyboard::BackSpace) && !getPlayerName)
			{
				menuReturn(maps,leader, opt, getPlayerName, play, men, themePlaying, background, theme, pause, p1win_detector, p2win_detector, whenpressed_detector, musicSwitch);
			}

			//pause

		}
		/// LOGIC ///


		

		//cout << maps_rect[0].getPosition().x << endl;
		if (times)
		{
			for (int i = 0; i < 4; i++)
				setState(maps_rect[i], dir, i);

			for (int i = 0; i < 4; i++)
			{
				Trans(maps_rect[i], i);
			}
			if (finished == 4)
			{
				times--;
				finished = 0;
			}
		}
		

		if (maps)
		{

			for (int i = 0; i < 4; i++)
			{
				Trans(maps_rect[i], i);
			}
			USER_SETTINGS[1] = mapNum;
			
		}

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
			RandomPos(ball,mapNum,obstacleTop);
			pad1.ResetPad(1,MODE);
			pad2.ResetPad(2,MODE);

			////reseting power ups /////////////
			longate.isSpawned = 0; longate.isActive = 0;
			freeze.isSpawned = 0;  freeze.isActive = 0;
			slow.isSpawned = 0;    slow.isActive = 0;
			invis.isSpawned = 0;    invis.isActive = 0;
			reverse.isSpawned = 0;    reverse.isActive = 0;
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
			if (mapNum == 0 || MODE == 't')
				ball.gain_velocity();

			//Sound / Collisions
			// Ball hit wall sound
			if (boundcheck_ball(ball,mapNum, obstacleTop))
			{
				if (sfxSwitch)
				{
					wall_hit.play();
				}
			}

			// Ball hit pad sound
			if (isCollidingFromLeft(ball, pad2.rect,Up,Down) || isCollidingFromRight(ball, pad1.rect,W,S,MODE))
			{
				if (sfxSwitch)
				{
					pad_hit.play();
				}
			}





			if (mapNum == 1)
			{
				map_collision(ball, obstacleTop, obstacleBot, pad3, pad4, 1);
			}
			else if (mapNum == 2)
			{
				map_collision(ball, obstacleTop, obstacleBot, pad3, pad4, 2);
			}
			else if (mapNum == 3)
			{
				map_collision(ball, obstacleBot, obstacleTop, pad3, pad4, 3);
			}


			// PowerUP
			// Spawn
			SpawnPowerups(reverse, longate, freeze, slow, invis, shorten, MODE, mapNum,obstacleTop);

			// Activate
			isTakenPowerup(reverse, longate, freeze, slow, invis, shorten, ball, pad1, pad2, sfxSwitch);

			// Deactivate the effect of pUP after it's time is up by tracing how long it has been activated
			DeactivatePowerups(reverse, longate, freeze, slow, invis, shorten, pad1, pad2);


			// Check collisions between the ball and the screen with x axis // score of player 1
				/*
						USE THE BALL RADIUS DON'T USE OTHER VALUES
				*/
			Clock resetClock;
			if (ball.circle.getPosition().x - ballRadius < 0.f)
			{
				ball.clock.restart();
				ball.added_velocity = 0;
				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep2++;
				ssScorep2.str("");
				ssScorep2 << scorep2;
				lblscorep2.setString(ssScorep2.str());
				// handles the bug of counting more than one point


				RandomPos(ball, mapNum, obstacleTop);
				pad1.ResetPad(1,MODE);
				pad2.ResetPad(2,MODE);

				//add a slight pause when a point is scored
				resetClock.restart();
				while (resetClock.getElapsedTime() < milliseconds(250))
				{
					window.clear(Color::Black);
					DrawGame(window, backg, pad1, pad2, pad3, pad4, ball, lblscorep1, lblscorep2, obstacleTop, obstacleBot, mapNum);
					DrawPowerups(window, longate, freeze, slow, invis, reverse, shorten);
					window.display();
					play = false;
				}
				play = true;

			}


			if (ball.circle.getPosition().x + ballRadius > GAMEWIDTH)
			{
				ball.clock.restart();
				ball.added_velocity = 0;

				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep1++;
				ssScorep1.str("");
				ssScorep1 << scorep1;
				lblscorep1.setString(ssScorep1.str());
				// handle the bug of counting more than one point
				resetClock.restart();


				RandomPos(ball, mapNum, obstacleTop);
				pad1.ResetPad(1,MODE);
				pad2.ResetPad(2,MODE);

				//add a slight pause when a point is scored
				resetClock.restart();
				while (resetClock.getElapsedTime() < milliseconds(250))
				{
					window.clear(Color::Black);
					DrawGame(window, backg, pad1, pad2, pad3, pad4, ball, lblscorep1, lblscorep2, obstacleTop, obstacleBot, mapNum);
					DrawPowerups(window, longate, freeze, slow, invis, reverse, shorten);
					window.display();
					play = false;
				}
				play = true;
			}
		}

		//Determing the end point of game
		if (scorep1 == 10)
		{
			p1win_detector = 1;
			gameOver(playerName1);
			addToLog(playerName1, playerName2);
			play = false;
			themePlaying = false;

		}
		else if (scorep2 == 10)
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
		
		if (play)
		{
			 DrawGame(window, backg, pad1, pad2, pad3, pad4, ball, lblscorep1, lblscorep2,obstacleTop,obstacleBot,mapNum);
			 DrawPowerups(window, longate, freeze, slow, invis, reverse, shorten);
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
			////////// menu background texture ///////////////////
			
			window.draw(menub);
			
			


		if (getPlayerName)
		{
			window.draw(textBox);
			window.draw(getNameBox);
			window.draw(messagePlayerText);
			window.draw(playerText);
		}


            ////////////// condition for maps ////////////
			if (maps) {
				//TODO
				DrawMapMenu(window);
				//window.clear();
				drawMenu(window, modesItems, 2);
				
			}
			
			//rendering winning message
			//p1 win
			if (p1win_detector) {
				pWin.setString(playerName1 + "   wins");

				window.draw(pWin);
				window.draw(option);

			}
			//p2 win
			if (p2win_detector) {
				pWin.setString(playerName2 + " wins");

				window.draw(pWin);
				window.draw(option);
			}
			//sets origin of text to center for easy positioning (placed here because the string can't be empty for it to function properly)
			pWin.setOrigin(pWin.getLocalBounds().width / 2.f, pWin.getLocalBounds().height / 2.f);
			pWin.setPosition(GAMEWIDTH / 2, 200);


			//render option window
			//searchMenus
			if (opt) {
				window.draw(option);
				DrawOptionMenu(window);
				men = false;

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
			SelectTheme(play);
			// To See which of the themes is choosen
			for (int x = 0; x < 4; x++)
			{
				if (Steps[x] == PADDING && isChoosen[x] && !done)
				{
					themeChange(pad1, pad2, ball, backgT, backg, obstacleTop, obstacleBot, obsTopTex, obsBotTex, pad, wall, scor, background_bfr, c, scor, background_bfr,x, USER_SETTINGS);
				}
			}

		}

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}
