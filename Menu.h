#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void Draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPresseditem() { return SelectedItemIndex; }
	
private:
	int SelectedItemIndex;
	Font font;
	Font font2;
	Text text[MAX_NUMBER_OF_ITEMS];
	SoundBuffer switiching_sound;
	Sound switching;
    
};

