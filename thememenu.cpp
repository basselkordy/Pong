#include "thememenu.h"

thememenu::thememenu(float width, float height)
{
	//sound of switching 
	switiching_sound.loadFromFile("resources/sfx/main_menu/switch.wav");
	switching.setBuffer(switiching_sound);

	//font properties 
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

	if (themechangeindex == 0) {
		themechange[0].setFont(font);
		themechange[0].setFillColor(sf::Color::Red);
	}
}

thememenu::~thememenu()
{
}

void thememenu::drawtheme(RenderWindow& windowvolume)
{

	for (int i = 0; i < numberofthemes; i++)
	{
		windowvolume.draw(themechange[i]);
	}

}

void thememenu::Move_A() //////move to left till now ////////////
{
	if (themechangeindex - 1 >= 0) {
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::White);
		themechangeindex--;
		themechange[themechangeindex].setFillColor(sf::Color::Red);
		switching.play();
	}
}

void thememenu::Move_D() ///////////move to right till now //////////////////////
{
	if (themechangeindex + 1 < numberofthemes) {
		themechange[themechangeindex].setFont(font);
		themechange[themechangeindex].setCharacterSize(30);
		themechange[themechangeindex].setFillColor(sf::Color::White);
		themechangeindex++;
		themechange[themechangeindex].setFillColor(sf::Color::Red);
		switching.play();
	}
}
