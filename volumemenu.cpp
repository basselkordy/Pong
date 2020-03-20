#include "volumemenu.h"

volumemenu::volumemenu(float width, float height)
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

}

volumemenu::~volumemenu()
{
}

void volumemenu::drawvolume(RenderWindow& windowvolume)
{
	
		for (int j = 0 ; j < 5 ; ++j)
		{
			windowvolume.draw(Volumechange[j]);
		}

}

void volumemenu::MoveRight()
{
	if (SelectedVolumeLevel +1  < 5 ) {
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::White);
		SelectedVolumeLevel++;
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::Red);
		switching.play();
	}
}

void volumemenu::MoveLeft()
{
	if (SelectedVolumeLevel - 1 >= 0) {
		Volumechange[SelectedVolumeLevel].setFont(font);
		Volumechange[SelectedVolumeLevel].setCharacterSize(30);
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::White);
		SelectedVolumeLevel--;
		Volumechange[SelectedVolumeLevel].setFillColor(sf::Color::Red);
		switching.play();
	}
}
