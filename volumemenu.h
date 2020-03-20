#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#define Items_Of_Volume 6

class volumemenu
{
public:
	volumemenu(float width, float height);
	~volumemenu();

	void drawvolume(RenderWindow& windowvolume);
	void MoveRight();
	void MoveLeft();
	int GetVolumechange() { return SelectedVolumeLevel; }


private:
	Text Volumechange[Items_Of_Volume];
	Font font;
	int SelectedVolumeLevel;
	SoundBuffer switiching_sound;
	Sound switching;

};

