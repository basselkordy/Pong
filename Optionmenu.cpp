#include "Optionmenu.h"

Optionmenu::Optionmenu(float width, float height)
{
	//sound of switching 
	switiching_sound.loadFromFile("resources/sfx/main_menu/switch.wav");
	switching.setBuffer(switiching_sound);

	//font properties 
	if (!font.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf")) {
	}

	///volume changer /////
	Volumechange[0].setFont(font);
	Volumechange[0].setFillColor(sf::Color::White);
	Volumechange[0].setString("0");
	Volumechange[0].setPosition(sf::Vector2f(((width / Items_Of_Volume)) * 1, height - 400));

	Volumechange[1].setFont(font);
	Volumechange[1].setFillColor(sf::Color::White);
	Volumechange[1].setString("25");
	Volumechange[1].setPosition(sf::Vector2f(((width / Items_Of_Volume)) * 2, (height - 400)));

	Volumechange[2].setFont(font);
	Volumechange[2].setFillColor(sf::Color::White);
	Volumechange[2].setString("50");
	Volumechange[2].setPosition(sf::Vector2f(((width / Items_Of_Volume)) * 3, (height - 400)));

	Volumechange[3].setFont(font);
	Volumechange[3].setFillColor(sf::Color::White);
	Volumechange[3].setString("75");
	Volumechange[3].setPosition(sf::Vector2f(((width / Items_Of_Volume)) * 4, (height - 400)));

	Volumechange[4].setFont(font);
	Volumechange[4].setFillColor(sf::Color::White);
	Volumechange[4].setString("100");
	Volumechange[4].setPosition(sf::Vector2f(((width / Items_Of_Volume)) * 5, (height - 400)));

	SelectedVolumeLevel = 0;

	if (SelectedVolumeLevel == 0) {
		Volumechange[0].setFont(font);
		Volumechange[0].setFillColor(sf::Color::Red);
	}




	//sound of switching of themes
	switiching_sound.loadFromFile("resources/sfx/main_menu/switch.wav");
	switching.setBuffer(switiching_sound);

	//font properties of themes
	if (!font.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf")) {
	}


	/////theme menu in option /////////////
	themechange[0].setFont(font);
	themechange[0].setFillColor(sf::Color::White);
	themechange[0].setString("Hell");
	themechange[0].setPosition(sf::Vector2f(((width / 6)) * 1, height - 300));

	themechange[1].setFont(font);
	themechange[1].setFillColor(sf::Color::White);
	themechange[1].setString("Ice");
	themechange[1].setPosition(sf::Vector2f(((width / 6)) * 2, height - 300));

	themechange[2].setFont(font);
	themechange[2].setFillColor(sf::Color::White);
	themechange[2].setString("Forest");
	themechange[2].setPosition(sf::Vector2f(((width / 6)) * 3, height - 300));


	themechangeindex = 0;

	index_of_menu = 0;
	
}

Optionmenu::~Optionmenu()
{
}


/// drawing of volume 
void Optionmenu::drawvolume(RenderWindow& windowvolume)
{

	for (int j = 0; j < 5; ++j)
	{
		windowvolume.draw(Volumechange[j]);
	}

}


//// drawing of themes 
void Optionmenu::drawtheme(RenderWindow& windowvolume)
{

	for (int i = 0; i < numberofthemes; i++)
	{
		windowvolume.draw(themechange[i]);
	}

}

/////moving right for themes and volume 
void Optionmenu::MoveRight()
{
	if (SelectedVolumeLevel + 1 < 5) {
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::White);
		SelectedVolumeLevel++;
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::Red);
		switching.play();
	}

    if (themechangeindex + 1 < numberofthemes) {
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::White);
		themechangeindex++;
		themechange[themechangeindex].setFillColor(sf::Color::Red);
		switching.play();
	}
	
}
/////moving left for themes and volume 
void Optionmenu::MoveLeft()
{
	if (SelectedVolumeLevel - 1 >= 0) {
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::White);
		SelectedVolumeLevel--;
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::Red);
		switching.play();

	}

    if (themechangeindex - 1 >= 0) {
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::White);
		themechangeindex--;
		themechange[themechangeindex].setFillColor(sf::Color::Red);
		switching.play();
	}
	
}
////////// moving up for switching between volume and themes////////////
void Optionmenu::MoveUp()
{
	Text changer[Number_of_index];
	if (index_of_menu - 1 >= 0) {
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::White);
		index_of_menu--;
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::Red);
	}
}
////////// moving Down for switching between volume and themes////////////
void Optionmenu::MoveDown()
{
	Text changer[Number_of_index];
	if (index_of_menu + 1 < Number_of_index) {
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::White);
		index_of_menu++;
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::Red);
	}
}








