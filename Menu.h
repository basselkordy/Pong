#pragma once
#include <sfml/Graphics.hpp>
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width , float height);
	~Menu();

	void Draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPresseditem() { return SelectedItemIndex; }

private:
	int SelectedItemIndex;
	Font font;
	Font font2;
	Text text[MAX_NUMBER_OF_ITEMS];

};

