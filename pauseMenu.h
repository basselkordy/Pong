#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

#define MAX_NUM_ITEMS 3;

class pauseMenu
{
public:
	pauseMenu(float width, float height);
	~pauseMenu();

	void DRAW(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPresseditem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	Font font;
	Text items[3];
	Sound switching;
	Sound switchingBuffer;
};

