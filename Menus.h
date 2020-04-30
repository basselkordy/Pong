#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include<vector>

using namespace sf;
using namespace std;




//////////////////////////////Option menus//////////////////////////////
// Elements respectivly: Theme, Map, Mode
char USER_SETTINGS[3];
//indicate theme
char choosenTheme;
// to Control the height that theme goes to
#define PADDING 15.f
#define VOLRADIUS 20.f
// Size of The Themes
Vector2f Theme_size(100,100);

// To track The position of the Mouse
Vector2i pos_Mouse;

// scroll bar
	// the modifier
	RectangleShape vol_changer;
	Texture volCircleTex;
	// current Position of the vol_changers
	Vector2f pos_volumeChanger(550, 453);
	// the bar
	RectangleShape bar;
	Texture volBarTex;
	// Volume Value bar
	RectangleShape VolumeValueBar;
	

// Themes
	// Hell Theme
	RectangleShape hell_theme;
	Texture tex_hell;
	Vector2f pos_hell(100, 250);
	// Forest Theme
	RectangleShape forest_theme;
	Texture tex_forest;
	Vector2f pos_forest(300, 250);
	// Ice Theme
	RectangleShape ice_theme;
	Texture tex_ice;
	Vector2f pos_ice(500, 250);
	// Classic Theme
	RectangleShape classic_theme;
	Texture tex_classic;
	Vector2f pos_classic(700, 250);
	vector<RectangleShape> themes = { hell_theme,forest_theme,ice_theme, classic_theme};

	// variables

	// to store the Volume bar input
	float VolumeValue = 100;
	float diff;
	// To Check if the Mouse is over on of the Themes
	bool onHold[4] = {};
	// To move the Themes up and down
	int Steps[4] = { 1,1,1,1 };
	// to load the vfx on time only
	bool IsLoaded = true;
	// to hold the theme which the player choose
	bool isChoosen[4] = {};
	//  to make sure that we only call theme change one time after choosing one
	bool  done = false;
	// to track the choosen theme h = 0 , f = 1 , i  = 2 , c = 3
	int place = 3;
	// to make at least one theme choosen
	bool ThemeCheck = true;

//Texts

	//Option menu texts
	
	RectangleShape optionHeader, volumeHeader, themeHeader;
	Texture optionTex, volumeTex, themeTex;

	//Map menu texts
	
	RectangleShape playHeader, mapHeader, modeHeader;
	Texture playHeaderTex, mapHeaderTex, modeHeaderTex;


	RectangleShape choosing_arrow;
/*
		FUNCTIONS
*/
// Checks if the Mouse is in the shape Bounds
bool IsMouseIn(RectangleShape& Body)
{

	if
		((pos_Mouse.x >= Body.getPosition().x - Body.getSize().x / 2.f && pos_Mouse.x <= Body.getPosition().x +Body.getSize().x / 2.f)
			&&
			(pos_Mouse.y >= Body.getPosition().y - Body.getSize().y / 2.f && pos_Mouse.y <= Body.getPosition().y + Body.getSize().y / 2.f))
		return true;
	else
		return false;
}
// submit the theme selection
void SubmitTheme()
{

	themes[0] = hell_theme;
	themes[1] = forest_theme;
	themes[2] = ice_theme;
	themes[3] = classic_theme;
	for (int i = 0; i < themes.size(); i++)
	{
		if (Keyboard::isKeyPressed(Keyboard::Return) && Steps[place] == PADDING)
		{
			isChoosen[place] = true;
			for (int x = 0; x < themes.size(); x++)
			{
				if (x != place)
					isChoosen[x] = false;
			}
			done = false;
		}
		if (IsMouseIn(themes[i]) && Steps[i] == PADDING && Mouse::isButtonPressed(Mouse::Left))
		{
			isChoosen[i] = true;
			place = i;
			for (int x = 0; x < themes.size(); x++)
			{
				if (x != i)
					isChoosen[x] = false;
			}
			done = false;

		}

	}
}
// To Select the Theme after the left Mouse button is is Pressed
void SelectTheme(bool inPause)
{
	themes[0] = hell_theme;
	themes[1] = forest_theme;
	themes[2] = ice_theme;
	themes[3] = classic_theme;
	for (int i = 0; i < 4; i++)
	{
		if (IsMouseIn(themes[i]) && !inPause)
			onHold[i] = true;
		else
			onHold[i] = false;

		
		onHold[place] = true;

		// Checks if any theme is choosen in order not to choose or modify the position of the others
		if (!isChoosen[i])
		{
			if (onHold[i])
			{
				if (Steps[i] < PADDING)
				{
					themes[i].setPosition(themes[i].getPosition().x, themes[i].getPosition().y - 1.f);
					Steps[i]++;
				}
			}
			else if (Steps[i] > 0)
			{
				themes[i].setPosition(themes[i].getPosition().x, themes[i].getPosition().y + 1.f);
				Steps[i]--;
			}
			// make an outline when the theme is ready to be choosen
			if (Steps[i] == PADDING)
			{
				themes[i].setOutlineThickness(1);
				themes[i].setOutlineColor(Color::White);
				if (ThemeCheck)
				{
					isChoosen[i] = true;
					ThemeCheck = false;
				}
			}
			else
			{
				themes[i].setOutlineThickness(0);
			}

			// to store last position of modified theme for the drawing func
			switch (i)
			{
			case 0:
				pos_hell = themes[i].getPosition();
				hell_theme = themes[i];
				break;
			case 1:
				pos_forest = themes[i].getPosition();
				forest_theme = themes[i];
				break;
			case 2:
				pos_ice = themes[i].getPosition();
			    ice_theme = themes[i];
				break;
			case 3:
				pos_classic = themes[i].getPosition();
				classic_theme = themes[i];
				break;
			}
		}
	}
}
// To Draw Option Menu
void DrawOptionMenu(RenderWindow& window)
{

	if(IsLoaded)
	{
		tex_hell.loadFromFile("resources/vfx/hell/hellbackg.jpg");
		tex_ice.loadFromFile("resources/vfx/ice/icebackg.png");
		tex_forest.loadFromFile("resources/vfx/forest/forestbackg.png");
		tex_classic.loadFromFile("resources/vfx/classic/to_display_in_menu.png");

		// Setting the Textures
		hell_theme.setTexture(&tex_hell);
		forest_theme.setTexture(&tex_forest);
		ice_theme.setTexture(&tex_ice);
		classic_theme.setTexture(&tex_classic);

		// vol_changer Settings
		volCircleTex.loadFromFile("resources/menu tex/volumeCircle.png");
		vol_changer.setTexture(&volCircleTex);
		vol_changer.setSize(Vector2f(25, 75));
		vol_changer.setOrigin(vol_changer.getSize().x / 2.f, vol_changer.getSize().y / 2.f);

		//vol_changer.setFillColor(Color(232, 90, 4));
		//vol_changer.setRadius(VOLRADIUS);
		//vol_changer.setOrigin(VOLRADIUS, VOLRADIUS);

		///// bar Settings
		volBarTex.loadFromFile("resources/menu tex/volumeBar.png");
		bar.setTexture(&volBarTex);
		bar.setSize(Vector2f(400, 200));
		//bar.setFillColor(Color(95, 77, 55));
		bar.setOrigin(bar.getSize() / 2.f);
		bar.setPosition(400, 450);

		// volume Value bar Settings
		VolumeValueBar.setPosition(100, 450);
		VolumeValueBar.setFillColor(Color(232, 164, 31));
		VolumeValueBar.setOrigin(0, bar.getSize().y / 2.f);

		///// Setting the Size
		hell_theme.setSize(Theme_size);
		forest_theme.setSize(Theme_size);
		ice_theme.setSize(Theme_size);
		classic_theme.setSize(Theme_size);

		///// Setting the Origin
		hell_theme.setOrigin(Theme_size / 2.f);
		forest_theme.setOrigin(Theme_size / 2.f);
		ice_theme.setOrigin(Theme_size / 2.f);
		classic_theme.setOrigin(Theme_size / 2.f);
		IsLoaded= false;
	}

	///// To update the Position of the vol_changer
	vol_changer.setPosition(pos_volumeChanger);
	///// To update the Position of the Themes
	hell_theme.setPosition(pos_hell);
	forest_theme.setPosition(pos_forest);
	ice_theme.setPosition(pos_ice);
	classic_theme.setPosition(pos_classic);
	diff = VolumeValue * 6;
	VolumeValueBar.setSize(Vector2f(diff, bar.getSize().y));


	//Headers

	optionTex.loadFromFile("resources/menu tex/OptionButton.png");
	optionHeader.setTexture(&optionTex);
	optionHeader.setSize(Vector2f(200, 100));
	optionHeader.setOrigin(optionHeader.getSize().x / 2, optionHeader.getSize().y / 2);
	optionHeader.setPosition(GAMEWIDTH / 2, 50);

	themeTex.loadFromFile("resources/menu tex/themeButton.png");
	themeHeader.setTexture(&themeTex);
	themeHeader.setSize(Vector2f(100, 50));
	themeHeader.setOrigin(themeHeader.getSize().x / 2, themeHeader.getSize().y / 2);
	themeHeader.setPosition(GAMEWIDTH / 2, 140);

	volumeTex.loadFromFile("resources/menu tex/volumeButton.png");
	volumeHeader.setTexture(&volumeTex);
	volumeHeader.setSize(Vector2f(100, 50));
	volumeHeader.setOrigin(volumeHeader.getSize().x / 2, volumeHeader.getSize().y / 2);
	volumeHeader.setPosition(GAMEWIDTH / 2, 370);


	///// The Rendering part




	//window.clear();
	window.draw(hell_theme);
	window.draw(ice_theme);
	window.draw(forest_theme);
	window.draw(classic_theme);
	window.draw(bar);
	//window.draw(VolumeValueBar);
	window.draw(vol_changer);
	window.draw(volumeHeader);
	window.draw(themeHeader);
	window.draw(optionHeader);


}
// To Take The Mouse Input With The Volume Bar
void VolumeChanger(RenderWindow& window)
{
	pos_Mouse = Mouse::getPosition(window);
	if (
		pos_Mouse.y >= vol_changer.getPosition().y - VOLRADIUS - 20
		&&
		pos_Mouse.y <= vol_changer.getPosition().y + VOLRADIUS + 20
		&&
		pos_Mouse.x >= vol_changer.getPosition().x - VOLRADIUS - 20
		&&
		pos_Mouse.x <= vol_changer.getPosition().x + VOLRADIUS + 20
		&&
		Mouse::isButtonPressed(Mouse::Left)
		)
	{
		if (
			pos_Mouse.x <= bar.getPosition().x + bar.getSize().x / 2.f
			&&
			pos_Mouse.x >= bar.getPosition().x - bar.getSize().x / 2.f
			)
		{
			vol_changer.setPosition(pos_Mouse.x, vol_changer.getPosition().y);
		}
		else if (pos_Mouse.x > bar.getPosition().x + bar.getSize().x / 2.f)
		{
			vol_changer.setPosition(bar.getPosition().x + bar.getSize().x / 2.f, vol_changer.getPosition().y);
		}
		else if (pos_Mouse.x < bar.getPosition().x - bar.getSize().x / 2.f)
		{
			vol_changer.setPosition(bar.getPosition().x - bar.getSize().x / 2.f, vol_changer.getPosition().y);
		}
		VolumeValue = (vol_changer.getPosition().x - (bar.getPosition().x - bar.getSize().x / 2.f));
		VolumeValue /= 6;
		pos_volumeChanger = vol_changer.getPosition();
		window.draw(vol_changer);
	}
}
// To Change volume by clicking on any empty space in the volume bar
void ChangeVolumebyClick(RenderWindow& window)
{
	pos_Mouse = Mouse::getPosition(window);
	if (IsMouseIn(bar) && Mouse::isButtonPressed(Mouse::Left))
	{
		vol_changer.setPosition(pos_Mouse.x, vol_changer.getPosition().y);
		VolumeValue = (vol_changer.getPosition().x - (bar.getPosition().x - bar.getSize().x / 2.f));
		VolumeValue /= 6;
		pos_volumeChanger = vol_changer.getPosition();
		window.draw(vol_changer);
	}
}

/////////////////////////////////// maps menus ///////////////////////////////////
// for the position of the map
int mapNum = 1; // 0 : default map , 1 : top/bot obstacles , 2 : mid obstacle, 3 : bot pads
bool ltr_1[4] = {};
bool ltr_2[4] = {};
bool ltr_3[4] = {};
bool mtl[4] = {};
bool rtl_1[4] = {};
bool rtl_2[4] = {};
bool rtl_3[4] = {};
bool mtr[4] = {};
int  finished = 0;
// to load the resources once
bool isDone = false;
// positions of the maps
float poses[3] = {250,400,550};
// current positions of the maps
float currentpos_maps[4] ={250,400,550,400};
// the hidden maps
int back = 0;
int backback = 3;
// for the IsMouseIn function
int left_map = 0, right_map =2;
// the init scale for the rects
double scaleU[4] = { 1,1.75,1,.25 };
// tex_maps
Texture tex_maps[4];
// maps
RectangleShape maps_rect[4];
int times = 0;
bool dir = false;
void setSelectedMap()
{
	if (mapNum == 0)
	{
		times = 1;
		dir = true;
		back = 0;
	}
	else if (mapNum == 2)
	{
		times = 1;
		dir = false;
	}
	else if (mapNum == 3)
	{
		times = 2;
	}
}
// to set the Trans for the maps
void setState(RectangleShape& body,bool  dir,int i)
{
	if (dir)
	{
		if (body.getPosition().x == poses[0])
		{
			ltr_1[i] = true;
		}
		else if (body.getPosition().x == poses[1])
		{
			if (body.getScale().x == 1.75)
				ltr_2[i] = true;
			else
				mtl[i] = true;
		}
		else if (body.getPosition().x == poses[2])
		{
			ltr_3[i] = true;
		}

	}
	else
	{
		if (body.getPosition().x == poses[0])
		{
			rtl_1[i] = true;
		}
		else if (body.getPosition().x == poses[1])
		{
			if (body.getScale().x == 1.75)
				rtl_2[i] = true;
			else
				mtr[i] = true;
		}
		else if (body.getPosition().x == poses[2])
		{
			rtl_3[i] = true;
		}
	}
}
void Trans(RectangleShape& body,int i)
{

		if (ltr_1[i])
		{

			// right to mid
			body.move(10, 0);
			// scale 1 --> 1.75
			if (scaleU[i] < 1.75)
				scaleU[i] += .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x >= poses[1])
			{
				ltr_1[i] = false;
				finished++;
				mapNum = i;
			}


		}
		if (ltr_2[i])
		{
			// mid to right
			body.move(10, 0);
			// scale 1.75 --> 1
			if (scaleU[i] > 1)
				scaleU[i] -= .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x >= poses[2])
			{
				ltr_2[i] = false;
				finished++;
				right_map = i;
			}

		}
		else if (ltr_3[i])
		{
			back = i;
			if (body.getPosition().x > poses[1])
			{
				// left to mid
				body.move(-10, 0);
				// scale 1 --> .25
				if (scaleU[i] > .25)
				scaleU[i] -= .05;
				body.setScale(scaleU[i], scaleU[i]);

			}
			if (body.getPosition().x <= poses[1])
			{
				ltr_3[i] = false;
				finished++;
			}

		}
		if (mtl[i])
		{
			backback = i;
			// mid to left
			body.move(-10, 0);
			// scale .25 --> 1
			if (scaleU[i] < 1)
				scaleU[i] += .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x <= poses[0])
			{
				mtl[i] = false;
				left_map = i;
				finished++;
			}

		}


		if (rtl_3[i])
		{
			// left to mid
			body.move(-10, 0);
			// scale 1--> 1.75
			if (scaleU[i] < 1.75)
				scaleU[i] += .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x <= poses[1])
			{
				rtl_3[i] = false;
				finished++;
				mapNum = i;
			}

		}
		else if (rtl_2[i])
		{
			// mid to right
			body.move(-10, 0);
			// scale 1.75 --> 1
			if (scaleU[i] > 1)
				scaleU[i] -= .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x <= poses[0])
			{
				rtl_2[i] = false;
				finished++;
				left_map = i;
			}

		}
		if (rtl_1[i])
		{
			back = i;
			if (body.getPosition().x < poses[1])
			{
				// right to mid
				body.move(10, 0);
				// scale 1 --> .25
				if (scaleU[i] > .25)
				scaleU[i] -= .05;
				body.setScale(scaleU[i], scaleU[i]);
			}
			if (body.getPosition().x >= poses[1])
			{
				rtl_1[i] = false;
				finished++;

			}

		}
		if (mtr[i])
		{
			backback = i;
			// mid to left
			body.move(10, 0);
			// scale .25 --> 1
			if (scaleU[i] < 1)
				scaleU[i] += .05;
			body.setScale(scaleU[i], scaleU[i]);
			if (body.getPosition().x >= poses[2])
			{
				mtr[i] = false;
				finished++;
				right_map = i;
			}
		}
}

// to draw the map menu
void DrawMapMenu(RenderWindow& window)
{
	if(!isDone)
	{
		tex_maps[0].loadFromFile("resources/vfx/maps/_1.jpg");
		
		tex_maps[1].loadFromFile("resources/vfx/maps/_2.jpg");
		tex_maps[2].loadFromFile("resources/vfx/maps/_3.jpg");
		tex_maps[3].loadFromFile("resources/vfx/maps/_4.jpg");

		for (int i = 0; i < 4; i++)
		{
			maps_rect[i].setPosition(currentpos_maps[i], 280);
			maps_rect[i].setSize(Vector2f(100, 100));
			maps_rect[i].setOrigin(maps_rect[i].getSize() / 2.f);
			maps_rect[i].setTexture(&tex_maps[i]);
			maps_rect[i].setScale(scaleU[i], scaleU[i]);
	
		}
		isDone =true;
		
	}
	
	//window.clear(Color(150,150,150));
    window.draw(playHeader);
	window.draw(mapHeader);
	window.draw(modeHeader);
	window.draw(choosing_arrow);
	window.draw(maps_rect[back]);
	window.draw(maps_rect[backback]);

	for (int i = 0; i < 4; i++)
	{
		if(back != i && backback != i)
		window.draw(maps_rect[i]);
	}

}

/////////////////////////MAIN MENU & PAUSE MENU////////////////////////

//MENU STRUCT
struct MENU
{
	int selectedItemIndex;
	Font font;
	Font font2;
	Sound switching;
	SoundBuffer switchingBuffer;
};

//////////////main buttons texture ////////////////
Texture texture_play;
Texture texture_opt;
Texture texture_lead;
Texture texture_train;
Texture texture_exit;
///////// pause button texture /////////////
Texture texture_resume;
Texture texture_option;
Texture texture_menu;
/////texture for modes ////////
Texture texture_single;
Texture texture_multi;

//Set Pause Menu Items
void setPauseMenu(MENU& pauseMenu, RectangleShape text[], int width, int height)
{
	pauseMenu.switching.setBuffer(pauseMenu.switchingBuffer);

	texture_resume.loadFromFile("resources/menu tex/ResumeButton.png");
	text[0].setSize(Vector2f(100.0f, 50.0f));
	text[0].setTexture(&texture_resume);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 1));

	texture_option.loadFromFile("resources/menu tex/PauseOptionButton.png");
	text[1].setSize(Vector2f(100.0f, 50.0f));
	text[1].setTexture(&texture_option);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 2));

	texture_menu.loadFromFile("resources/menu tex/PauseExitButton.png");
	text[2].setSize(Vector2f(100.0f, 50.0f));
	text[2].setTexture(&texture_menu);
	text[2].setFillColor(sf::Color::White);
	text[2].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 3));

	pauseMenu.selectedItemIndex = 0;

	if (pauseMenu.selectedItemIndex == 0) {
		text[0].setSize(Vector2f(150, 75));
		text[0].setPosition(sf::Vector2f((width / 2) - 80, height / (3 + 1) * (0.75)));
	}
}

//Set Main Menu Items
void setMainMenu(MENU& mainMenu, RectangleShape text[], int width, int height)
{
	//sound of switching
	mainMenu.switchingBuffer.loadFromFile("resources/sfx/main_menu/switch.wav");
	mainMenu.switching.setBuffer(mainMenu.switchingBuffer);

	texture_play.loadFromFile("resources/menu tex/PlayButton.png");
	text[0].setSize(Vector2f(100.0f, 50.0f));
	text[0].setTexture(&texture_play);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition(sf::Vector2f((width / 2) - 50, height / (6 + 1) * 1));

	texture_opt.loadFromFile("resources/menu tex/OptionButton.png");
	text[1].setSize(Vector2f(100.0f, 50.0f));
	text[1].setTexture(&texture_opt);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(sf::Vector2f((width / 2) - 50, height / (6 + 1) * 2));

	texture_lead.loadFromFile("resources/menu tex/LeadButton.png");
	text[2].setSize(Vector2f(100.0f, 50.0f));
	text[2].setTexture(&texture_lead);
	text[2].setFillColor(sf::Color::White);
	text[2].setPosition(sf::Vector2f((width / 2) - 50, height / (6 + 1) * 3));

	texture_train.loadFromFile("resources/menu tex/TrainingButton.png");
	text[3].setSize(Vector2f(100.0f, 50.0f));
	text[3].setTexture(&texture_train);
	text[3].setFillColor(sf::Color::White);
	text[3].setPosition(sf::Vector2f((width / 2) - 50, height / (6 + 1) * 4));

	texture_exit.loadFromFile("resources/menu tex/ExitButton.png");
	text[4].setSize(Vector2f(100.0f, 50.0f));
	text[4].setTexture(&texture_exit);
	text[4].setFillColor(sf::Color::White);
	text[4].setPosition(sf::Vector2f((width / 2) - 50, height / (6 + 1) * 5));

	mainMenu.selectedItemIndex = 0;

	////when opening the game
	if (mainMenu.selectedItemIndex == 0) {
		text[0].setSize(Vector2f(150, 75));
		text[0].setPosition(sf::Vector2f((width / 2) - 80, height / (6 + 1) * (0.75)));
	}
}



void modes_display(MENU& mode, RectangleShape text[], int width, int height)
{
	//sound of switching
	mode.switchingBuffer.loadFromFile("resources/sfx/main_menu/switch.wav");
	mode.switching.setBuffer(mode.switchingBuffer);

	font.loadFromFile("resources/fonts/ARCADECLASSIC.ttf");

	playHeaderTex.loadFromFile("resources/menu tex/playButton.png");
	playHeader.setTexture(&playHeaderTex);
	playHeader.setSize(Vector2f(200, 100));
	playHeader.setOrigin(playHeader.getSize().x / 2, playHeader.getSize().y / 2);
	playHeader.setPosition(GAMEWIDTH / 2, 50);

	mapHeaderTex.loadFromFile("resources/menu tex/mapButton.png");
	mapHeader.setTexture(&mapHeaderTex);
	mapHeader.setSize(Vector2f(100, 50));
	mapHeader.setOrigin(mapHeader.getSize().x / 2, mapHeader.getSize().y / 2);
	mapHeader.setPosition(GAMEWIDTH / 2, 140);

	modeHeaderTex.loadFromFile("resources/menu tex/modeButton.png");
	modeHeader.setTexture(&modeHeaderTex);
	modeHeader.setSize(Vector2f(100, 50));
	modeHeader.setOrigin(modeHeader.getSize().x / 2, modeHeader.getSize().y / 2);
	modeHeader.setPosition(GAMEWIDTH / 2, 440);

	choosing_arrow.setSize(Vector2f(50, 10));
	choosing_arrow.setFillColor(Color::White);

	
	texture_single.loadFromFile("resources/menu tex/singleButton.png");
	text[0].setSize(Vector2f(100.0f, 50.0f));
	text[0].setTexture(&texture_single);
	text[0].setFillColor(Color(92, 92, 92));
	text[0].setPosition(sf::Vector2f((width / (2+1)*1)-50, height -100));

	texture_multi.loadFromFile("resources/menu tex/multiButton.png");
	text[1].setSize(Vector2f(100.0f, 50.0f));
	text[1].setTexture(&texture_multi);
	text[1].setFillColor(Color(92,92,92));
	text[1].setPosition(sf::Vector2f((width / (2+1)*2)-50, height - 100));

	mode.selectedItemIndex = 0;

	////when opening the game
	if (mode.selectedItemIndex == 0) {
		text[0].setFillColor(sf::Color::White);
		
	}
	
}

//Menu Drawing
void drawMenu(RenderWindow& menuWindow, RectangleShape text[], int noOfItems)
{
	for (int i = 0; i < noOfItems; i++)
	{
		menuWindow.draw(text[i]);
	}
	
}

void moveUp(MENU& menu, int noOfItems, RectangleShape text[], int no)
{
	text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
	text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
	if (!menu.selectedItemIndex)
		menu.selectedItemIndex = noOfItems;
	menu.selectedItemIndex--;
	text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
	text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.75)));
	menu.switching.play();
	
}

void moveDown(MENU& menu, RectangleShape text[], int noOfItems, int no)
{
	
	text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
	text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
	menu.selectedItemIndex++;
	menu.selectedItemIndex %= noOfItems;
	text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
	text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.80)));
	menu.switching.play();
	
}

void moveleft(MENU& menu, int noOfItems, RectangleShape text[])
{
	
	if (menu.selectedItemIndex - 1 >= 0)
	{

		text[menu.selectedItemIndex].setFillColor(Color(92, 92, 92));
		menu.selectedItemIndex--;
		text[menu.selectedItemIndex].setFillColor(Color::White);
	    menu.switching.play();
		
	}
	

}

void moveright(MENU& menu, RectangleShape text[], int noOfItems)
{
	if (menu.selectedItemIndex + 1 < noOfItems)
	{
		text[menu.selectedItemIndex].setFillColor(Color(92, 92, 92));
		menu.selectedItemIndex++;
	    text[menu.selectedItemIndex].setFillColor(sf::Color::White);
	    menu.switching.play();
	}

	

}