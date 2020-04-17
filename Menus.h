#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include<vector>

using namespace sf;
using namespace std;

// to Control the height that theme goes to
#define PADDING 15.f
#define VOLRADIUS 20.f
char c = 'f'; //indicate theme
// Size of The Themes
Vector2f Theme_size(100,100);

// To track The position of the Mouse
Vector2i pos_Mouse;

// scroll bar
	// the modifier
	CircleShape vol_changer;
	// current Position of the vol_changers
	Vector2f pos_volumeChanger(700, 350);
	// the bar
	RectangleShape bar;
	// Volume Value bar
	RectangleShape VolumeValueBar;


// Themes
	// Hell Theme
	RectangleShape hell_theme;
	Texture tex_hell;
	Vector2f pos_hell(100, 200);
	// Forest Theme
	RectangleShape forest_theme;
	Texture tex_forest;
	Vector2f pos_forest(300, 200);
	// Ice Theme
	RectangleShape ice_theme;
	Texture tex_ice;
	Vector2f pos_ice(500, 200);
	// Classic Theme
	RectangleShape classic_theme;
	Texture tex_classic;
	Vector2f pos_classic(700, 200);


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

	int place = 0;

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
void SelectTheme()
{
	themes[0] = hell_theme;
	themes[1] = forest_theme;
	themes[2] = ice_theme;
	themes[3] = classic_theme;
	for (int i = 0; i < 4; i++)
	{
		if (IsMouseIn(themes[i]))
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
			else
			{
				if (Steps[i] > 0)
				{
					themes[i].setPosition(themes[i].getPosition().x, themes[i].getPosition().y + 1.f);
					Steps[i]--;
				}
			}
			// make an outline when the theme is ready to be choosen
			if (Steps[i] == PADDING)
			{
				themes[i].setOutlineThickness(1);
				themes[i].setOutlineColor(Color::White);
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
		vol_changer.setFillColor(Color(232, 90, 4));
		vol_changer.setRadius(VOLRADIUS);
		vol_changer.setOrigin(VOLRADIUS, VOLRADIUS);
		///// bar Settings
		bar.setSize(Vector2f(600, 40));
		bar.setFillColor(Color(95, 77, 55));
		bar.setOrigin(bar.getSize() / 2.f);
		bar.setPosition(400, 350);
		// volume Value bar Settings
		VolumeValueBar.setPosition(100, 350);
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





	///// The Rendering part




	window.clear();
	window.draw(hell_theme);
	window.draw(ice_theme);
	window.draw(forest_theme);
	window.draw(classic_theme);
	window.draw(bar);
	window.draw(VolumeValueBar);
	window.draw(vol_changer);


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

//Set Pause Menu Items
void setPauseMenu(MENU& pauseMenu, RectangleShape text[], int width, int height)
{
	pauseMenu.switching.setBuffer(pauseMenu.switchingBuffer);
	pauseMenu.font.loadFromFile("resources/fonts/Daitengu DEMO.otf");

	texture_resume.loadFromFile("resources/menu tex/ResumeButton.png");
	text[0].setSize(Vector2f(100.0f, 50.0f));
	text[0].setTexture(&texture_resume);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 1));

	texture_option.loadFromFile("resources/menu tex/OptionButton.png");
	text[1].setSize(Vector2f(100.0f, 50.0f));
	text[1].setTexture(&texture_option);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 2));

	texture_menu.loadFromFile("resources/menu tex/ExitButton.png");
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

	//font properties
	if (!mainMenu.font.loadFromFile("resources/fonts/Daitengu DEMO.otf") || !mainMenu.font2.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf")) {
	}
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
	//if the selected item is after the the first item
	if (menu.selectedItemIndex - 1 >= 0)
	{
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
		text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
		menu.selectedItemIndex--;
		text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.75)));
		menu.switching.play();
	}

	//if the selected item is the first item and the user moves up select the last item
	else if (menu.selectedItemIndex - 1 < 0)
	{
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
		text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
		menu.selectedItemIndex = noOfItems - 1;
		text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.75)));
		menu.switching.play();
	}
}

void moveDown(MENU& menu, RectangleShape text[], int noOfItems, int no)
{
	//if the selected item is before the the last item
	if (menu.selectedItemIndex + 1 < noOfItems)
	{
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
		text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
		menu.selectedItemIndex++;
		text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.80)));
		menu.switching.play();
	}

	//if the selected item is the last item and the user moves down select the first item
	else if (menu.selectedItemIndex + 1 >= noOfItems)
	{
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
		text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
		menu.selectedItemIndex = 0;
		text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.80)));
		menu.switching.play();
	}

}

//////////////////////////// using mouse to navigate in menus ////////////////////////////////////
void mouse_navigator(MENU& menu, RectangleShape text[], double noIndex, Window& window, int no)
{

	/////////////// detection of position of mouse ////////////////////
	pos_Mouse = Mouse::getPosition(window);
	/////equation to detect the index+1 //////////////
	int texy = (pos_Mouse.y * (noIndex));
	/*
				 ...... index changer ................
																					 */
	if ((pos_Mouse.y >= 90 && pos_Mouse.y <= 510) && (pos_Mouse.x >= 300 && pos_Mouse.x <= 500)) {
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 50, 600 / (no) * (menu.selectedItemIndex + 1)));
		text[menu.selectedItemIndex].setSize(Vector2f(100, 50));
		menu.selectedItemIndex = texy - 1;
		text[menu.selectedItemIndex].setSize(Vector2f(150, 75));
		text[menu.selectedItemIndex].setPosition(sf::Vector2f((800 / 2) - 75, 600 / (no) * (menu.selectedItemIndex + 0.75)));
		menu.switching.play();
	}
}





