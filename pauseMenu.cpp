#include "pauseMenu.h"

//Properties of menu items
pauseMenu::pauseMenu(float width, float height)
{
	if (!font.loadFromFile("resources/fonts/Daitengu DEMO.otf") )
	{
	}

	items[0].setFont(font);
	items[0].setFillColor(Color::White);
	items[0].setString("Resume");
	items[0].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 1));

	items[1].setFont(font);
	items[1].setFillColor(Color::White);
	items[1].setString("Option");
	items[1].setPosition(sf::Vector2f((width / 2) - 50, height / (3 + 1) * 2));

	items[2].setFont(font);
	items[2].setFillColor(Color::White);
	items[2].setString("Menu");
	items[2].setPosition(Vector2f((width / 2) - 50, height / (3 + 1) * 3));

	selectedItemIndex = 0;

	if (selectedItemIndex == 0)
	{
		items[0].setFont(font);
		items[0].setFillColor(Color::Red);
	}
}

pauseMenu::~pauseMenu()
{
}

void pauseMenu::DRAW(RenderWindow & pauseWindow)
{
	for (int i = 0; i < 3; i++)
	{
		pauseWindow.draw(items[i]);
	}
}

//to update selected item when moving up
void pauseMenu::moveUp()
{
	//if the selected item is after the the first item
	if (selectedItemIndex - 1 >= 0)
	{
		items[selectedItemIndex].setFillColor(Color::White);
		items[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex--;
		items[selectedItemIndex].setFillColor(Color::Red);
		items[selectedItemIndex].setCharacterSize(40);
		switching.play();

	}

	//if the selected item is the first item and the user moves up select the last item
	else if (selectedItemIndex - 1 < 0)
	{
		items[selectedItemIndex].setFillColor(Color::White);
		items[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex = 2;
		items[selectedItemIndex].setFillColor(Color::Red);
		items[selectedItemIndex].setCharacterSize(40);
	}
}

//to update selected item when moving up
void pauseMenu::moveDown()
{
	//if the selected item is before the the last item
	if (selectedItemIndex + 1 < 3)
	{
		items[selectedItemIndex].setFillColor(Color::White);
		items[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex++;
		items[selectedItemIndex].setFillColor(Color::Red);
		items[selectedItemIndex].setCharacterSize(40);
		switching.play();
	}

	//if the selected item is the last item and the user moves down select the first item
	else if (selectedItemIndex + 1 >= 3)
	{
		items[selectedItemIndex].setFillColor(Color::White);
		items[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex = 0;
		items[selectedItemIndex].setFillColor(Color::Red);
		items[selectedItemIndex].setCharacterSize(40);
	}

}
