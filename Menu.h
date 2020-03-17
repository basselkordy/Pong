#pragma once
#include <sfml/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width , float height);
	~Menu();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPresseditem() { return SelectedItemIndex; }

private:
	int SelectedItemIndex;
	sf::Font font;
	sf::Font font2;
	sf::Text text[MAX_NUMBER_OF_ITEMS];

};

