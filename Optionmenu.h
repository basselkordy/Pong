#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#define Items_Of_Volume 6
#define numberofthemes 3
#define Number_of_index 2 


class Optionmenu
{
public:
	Optionmenu(float width, float height);
	~Optionmenu();

	void drawvolume(RenderWindow& windowvolume);
	void drawtheme(RenderWindow& windowvolume);
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	int GetVolumechange() { return SelectedVolumeLevel; }
	int GetThemechange() { return themechangeindex; }


private:
	Text Volumechange[Items_Of_Volume];
	Text themechange[numberofthemes];
	Font font;
	int SelectedVolumeLevel;
	int themechangeindex;
	int index_of_menu;
	SoundBuffer switiching_sound;
	Sound switching;

};

