#include "Menu.h"
///this for controling the properties of menu (size , position , size of font , color , fonts , sounds)
Menu::Menu(float width, float height)
{
	//sound of switching 
	switiching_sound.loadFromFile("resources/sfx/main_menu/switch.wav" );
	switching.setBuffer(switiching_sound);

	//font properties 
	if (!font.loadFromFile("resources/fonts/Daitengu DEMO.otf") || !font2.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf")) {
	}
	text[0].setFont(font);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("Play");
	text[0].setPosition(sf::Vector2f((width / 2) - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));


	text[1].setFont(font);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Options");
	text[1].setPosition(sf::Vector2f((width / 2) - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("LeaderBoard");
	text[2].setPosition(sf::Vector2f((width / 2) - 75, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::White);
	text[3].setString("Exit");
	text[3].setPosition(sf::Vector2f((width / 2) - 35, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	SelectedItemIndex = 0;

	//when opening the game 
	if (SelectedItemIndex == 0) {
		text[0].setFont(font2);
		text[0].setCharacterSize(40);
		text[0].setFillColor(sf::Color::Red);
	}

	



}

Menu::~Menu()
{
}

//function for displaying the menu on screen 
void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(text[i]);
		
	}
}


//function to update the index when move up
void Menu::MoveUp()
{
	if (SelectedItemIndex - 1 >= 0) {
		
		text[SelectedItemIndex].setFont(font);
		text[SelectedItemIndex].setCharacterSize(30);
		text[SelectedItemIndex].setFillColor(sf::Color::White);
		SelectedItemIndex--;
		text[SelectedItemIndex].setCharacterSize(40);
		text[SelectedItemIndex].setFont(font2);
		text[SelectedItemIndex].setFillColor(sf::Color::Red);
		switching.play();
	}
}

//function to update the index when move Down 
void Menu::MoveDown()
{
	if (SelectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
	
		text[SelectedItemIndex].setFont(font);
		text[SelectedItemIndex].setCharacterSize(30);
		text[SelectedItemIndex].setFillColor(sf::Color::White);
		SelectedItemIndex++;
		text[SelectedItemIndex].setCharacterSize(40);
		text[SelectedItemIndex].setFont(font2);
		text[SelectedItemIndex].setFillColor(sf::Color::Red);
		switching.play();
	}
}



