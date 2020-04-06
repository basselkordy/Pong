#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
// to Control the height that theme goes to
#define PADDING 15.f
#define VOLRADIUS 20.f
char c = 'f'; //indicate theme
// Size of The Themes
Vector2f Theme_size(200,200);

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
	Vector2f pos_hell(150, 200);
	// Forest Theme
	RectangleShape forest_theme;
	Texture tex_forest;
	Vector2f pos_forest(370, 200);
	// Ice Theme
	RectangleShape ice_theme;
	Texture tex_ice;
	Vector2f pos_ice(590, 200);


	vector<RectangleShape> themes = { hell_theme,forest_theme,ice_theme };

	// variables

	// to store the Volume bar input
	float VolumeValue = 100;
	float diff;
	// To Check if the Mouse is over on of the Themes
	bool onHold[3] = {};

	// To move the Themes up and down
	int Steps[3] = { 1,1,1 };

	// to load the vfx on time only
	bool IsLoaded = true;

	// to hold the theme which the player choose
	bool isChoosen[3] = {};

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
	for (int i = 0; i < 3; i++)
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
		// Setting the Textures
		hell_theme.setTexture(&tex_hell);
		forest_theme.setTexture(&tex_forest);
		ice_theme.setTexture(&tex_ice);
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
		///// Setting the Origin
		hell_theme.setOrigin(Theme_size / 2.f);
		forest_theme.setOrigin(Theme_size / 2.f);
		ice_theme.setOrigin(Theme_size / 2.f);
		IsLoaded= false;
	}

	///// To update the Position of the vol_changer
	vol_changer.setPosition(pos_volumeChanger);
	///// To update the Position of the Themes
	hell_theme.setPosition(pos_hell);
	forest_theme.setPosition(pos_forest);
	ice_theme.setPosition(pos_ice);

	diff = VolumeValue * 6;
	VolumeValueBar.setSize(Vector2f(diff, bar.getSize().y));





	///// The Rendering part




	window.clear();
	window.draw(hell_theme);
	window.draw(ice_theme);
	window.draw(forest_theme);
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
