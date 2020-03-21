#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#define numberofthemes 3

class thememenu
{
public:
	thememenu(float width, float height);
	~thememenu();


	void drawtheme(RenderWindow& windowvolume);
	void Move_A();
	void Move_D();
	int GetThemechange() { return themechangeindex; }

private:
	Text themechange[numberofthemes];
	Font font;
	int themechangeindex;
	SoundBuffer switiching_sound;
	Sound switching;

};