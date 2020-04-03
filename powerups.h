
//struct containing powerup attributes
struct pUp
{
	CircleShape circle; //pUp shape
	Texture texture; // pUp texture
	Clock clock; //clock decleration to work a timer later for how long the powerup stays
	bool isSpawned = false; // Bool to check if the pUP on the screen aka "spawned"
	bool isActive = false; // bool to check if the a player has picked the pUP and it's working on him now
	Sound sound;

};

//elongate function takes a pad and a bool to return longer length if it's activated or normal length if it's deactivated
//the pad part is not crucial but it's for code's flexability 
void elongate(PAD& pad1, PAD& pad2, bool active, char c)
{
	if (active)
	{
		if (c == '1')
		{
			int len = padlengthSTD * 2;
			pad1.rect.setSize(Vector2f(pad1.width, len)); //make p1 longer
			pad1.length = len;
			pad1.rect.setOrigin(pad1.width / 2.f, pad1.length / 2.f);

			if (pad1.rect.getPosition().y + len / 2.f > 600)
			{
				pad1.rect.setPosition(pad1.rect.getPosition().x, GAMEHEIGHT - pad1.length / 2.f);
			}
			else if (pad1.rect.getPosition().y - len / 2.f < 0)
			{
				pad1.rect.setPosition(pad1.rect.getPosition().x, pad1.length / 2.f);
			}
		}
		else
		{
			int len = padlengthSTD * 2;
			pad2.rect.setSize(Vector2f(pad2.width, len)); //make p2 longer
			pad2.length = len;
			pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);

			//if the pad after elongated is out of screen return it in
			if (pad2.rect.getPosition().y + len / 2.f > 600)
			{
				pad2.rect.setPosition(pad2.rect.getPosition().x, GAMEHEIGHT - pad2.length / 2.f);
			}
			else if (pad2.rect.getPosition().y - len / 2.f < 0)
			{
				pad2.rect.setPosition(pad2.rect.getPosition().x, pad2.length / 2.f);
			}
		}

	}
	else
	{
		if (pad1.rect.getSize().y != padlengthSTD) //if the player that has the pUp is p1  (logic could be changed later)
		{
			int len = padlengthSTD; //variable for the sake of code readability
			pad1.rect.setSize(Vector2f(pad1.width, len)); // return size of p1 to normal
			pad1.length = len;
			pad1.rect.setOrigin(pad2.width / 2.f, pad1.length / 2.f);
		}
		else  //if the player that has the pUp is p2  (logic could be changed later)
		{
			int len = padlengthSTD;  //variable for the sake of code readability
			pad2.rect.setSize(Vector2f(pad2.width, len)); // return size of p1 to normal
			pad2.length = len;
			pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
		}
	}

}

// Takes references to all powerups and sets their textures, radii and sounds
void initialize_powerups(pUp& reverse,pUp& longate, pUp& freeze, pUp& slow, pUp& invis,
						SoundBuffer& lngbfr, SoundBuffer& frzbfr, SoundBuffer& slowbfr, SoundBuffer& invsbfr)
{
	////longate
	longate.circle.setFillColor(Color::Red); //pUp color
	longate.circle.setRadius(10); //pUp size
	longate.sound.setBuffer(lngbfr);


	////freeze 
	freeze.circle.setFillColor(Color::Blue); //pUp color
	freeze.circle.setRadius(10); //pUp size	
	freeze.sound.setBuffer(frzbfr);

	////slow
	slow.circle.setFillColor(Color::Green); //pUp color
	slow.circle.setRadius(10); //pUp size
	slow.sound.setBuffer(slowbfr);

	////Invisibility
	invis.circle.setFillColor(Color::Magenta); //pUp color
	invis.circle.setRadius(10); //pUp size
	invis.sound.setBuffer(invsbfr);

	//Reverse
	/*invis.circle.setFillColor(Color::Black); //pUp color
	invis.circle.setRadius(10);*/
}


// Draws powerups if they are spawned
void DrawPowerups(RenderWindow& window, pUp& longate, pUp& freeze, pUp& slow, pUp& invis, pUp& reverse)
{

	//elongate
	if (longate.isSpawned == true)
	{
		window.draw(longate.circle);
	}
	//freeze
	if (freeze.isSpawned == true)
	{
		window.draw(freeze.circle);
	}
	//slow
	if (slow.isSpawned == true)
	{
		window.draw(slow.circle);
	}
	//invis
	if (invis.isSpawned == true)
	{
		window.draw(invis.circle);
	}
	//Reverse
	/*if (reverse.isSpawned == true)
	{
		window.draw(reverse.circle);
	}*/

}



//check for collision with ball and pUp and only do so if it's already spawned on screen
// and activates powerups if they are taken 
void isTakenPowerup(pUp& reverse,pUp& longate, pUp& freeze, pUp& slow, pUp& invis, BALL ball, PAD& pad1, PAD& pad2, bool sfxSwitch)
{

	//elongate
	if (longate.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(longate.circle.getGlobalBounds()))
	{
		if (sfxSwitch)
		{
			longate.sound.play();
		}
		longate.clock.restart(); //reset pUP timer
		longate.isSpawned = 0; //prevent multi spawn
		longate.isActive = 1;

		//if player1 is the one who took the pUP
		if (ball.xVelocity > 0)
		{
			elongate(pad1, pad2, true, '1');
		}
		//if player2 is the one who took the pUP
		else
		{
			elongate(pad1, pad2, true, '2');
		}
	}

	//Freeze
	if (freeze.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(freeze.circle.getGlobalBounds()))
	{
		if (sfxSwitch)
		{
			freeze.sound.play();
		}
		freeze.clock.restart(); //reset pUP timer
		freeze.isSpawned = 0; //prevent multi spawn
		freeze.isActive = 1;

		//if player1 is the one who took the pUP
		if (ball.xVelocity > 0)
		{
			pad2.isFrozen = 1; //make p2 frozen
			pad2.rect.setFillColor(Color::Blue);
		}
		//if player2 is the one who took the pUP
		else
		{
			pad1.isFrozen = 1; //make p2 frozen
			pad1.rect.setFillColor(Color::White);
			pad1.rect.setFillColor(Color::Blue);
		}
	}

	//Slow
	if (slow.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(slow.circle.getGlobalBounds()))
	{
		if (sfxSwitch)
		{
			slow.sound.play();
		}
		slow.clock.restart(); //reset pUP timer
		slow.isSpawned = 0; //prevent multi spawn
		slow.isActive = 1;

		//if player1 is the one who took the pUP
		if (ball.xVelocity > 0)
		{
			pad2.isSlow = 1; //make p2 frozen
			pad2.rect.setFillColor(Color::Red);

		}
		//if player2 is the one who took the pUP
		else
		{
			pad1.isSlow = 1; //make p2 longer
			pad1.rect.setFillColor(Color::Red);
		}
	}

	//Invis 
	if (invis.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(invis.circle.getGlobalBounds()))
	{
		if (sfxSwitch)
		{
			invis.sound.play();
		}
		invis.clock.restart(); //reset pUP timer
		invis.isSpawned = 0; //prevent multi spawn
		invis.isActive = 1;

		//if player1 is the one who took the pUP
		if (ball.xVelocity > 0)
		{
			pad2.isInvis = 1; //make p2 frozen

		}
		//if player2 is the one who took the pUP
		else
		{
			pad1.isInvis = 1; //make p2 longer

		}
	}
	/*if (reverse.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(reverse.circle.getGlobalBounds()))
	{
		if (sfxSwitch)
		{
			reverse.sound.play();
		}
		reverse.clock.restart(); //reset pUP timer
		reverse.isSpawned = 0; //prevent multi spawn
		reverse.isActive = 1;

		//if player1 is the one who took the pUP
		if (ball.xVelocity > 0)
		{
			pad2.isReverse = 1; //make p2 frozen
			pad2.rect.setFillColor(Color::Black);

		}
		//if player2 is the one who took the pUP
		else
		{
			pad1.isReverse = 1; //make p2 longer
			pad1.rect.setFillColor(Color::Black);
		}
	}*/
}


// spawns only if no player has the pUp ,
//it's not yet spawned (prevent multi spawn) and depends on a random number generated (controls spawn rate)
void SpawnPowerups(pUp& reverse,pUp& longate, pUp& freeze, pUp& slow, pUp& invis, char MODE)
{

	if (longate.isActive == false && longate.isSpawned == false && rand() % 100 > 96 && MODE != 't')
	{
		longate.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
		longate.isSpawned = 1; //change spawned state
	}

	if (freeze.isActive == false && freeze.isSpawned == false && rand() % 1000 > 998 && MODE != 't')
	{
		freeze.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
		freeze.isSpawned = 1; //change spawned state
	}

	if (slow.isActive == false && slow.isSpawned == false && rand() % 1000 > 900 && MODE != 't')
	{
		slow.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
		slow.isSpawned = 1; //change spawned state
	}

	if (invis.isActive == false && invis.isSpawned == false && rand() % 1000 > 998 && MODE != 't')
	{
		invis.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
		invis.isSpawned = 1; //change spawned state
	}
	/*if (reverse.isActive == false && reverse.isSpawned == false && rand() % 1000 > 998 && MODE != 't')
	{
		reverse.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
		reverse.isSpawned = 1; //change spawned state
	}*/

}


void DeactivatePowerups(pUp& reverse, pUp& longate, pUp& freeze, pUp& slow, pUp& invis, PAD& pad1, PAD& pad2)
{
	//ELONGATE
	if (longate.isActive == true && longate.clock.getElapsedTime() > seconds(6))
	{
		elongate(pad1, pad2, false, '1');
		longate.isActive = 0; //pUp is no longer active
	}

	//FREEZE
	if (freeze.isActive == true && freeze.clock.getElapsedTime() > seconds(2))
	{

		if (pad1.isFrozen) //if the player that has the pUp is p1  (logic could be changed later)
		{
			pad1.isFrozen = 0;
			pad1.rect.setFillColor(Color::White);
		}
		else  //if the player that has the pUp is p2  (logic could be changed later)
		{
			pad2.isFrozen = 0;
			pad2.rect.setFillColor(Color::White);
		}

		freeze.isActive = 0; //pUp is no longer active
	}

	//SLOW
	if (slow.isActive == true && slow.clock.getElapsedTime() > seconds(3))
	{

		if (pad1.isSlow) //if the player that has the pUp is p1  (logic could be changed later)
		{
			pad1.isSlow = 0;
			pad1.rect.setFillColor(Color::White);
		}
		else  //if the player that has the pUp is p2  (logic could be changed later)
		{
			pad2.isSlow = 0;
			pad2.rect.setFillColor(Color::White);
		}


		slow.isActive = 0; //pUp is no longer active
	}

	//INVIS
	if (invis.isActive == true && invis.clock.getElapsedTime() > seconds(1))
	{

		if (pad1.isInvis) //if the player that has the pUp is p1  (logic could be changed later)
		{
			pad1.isInvis = 0;

		}
		else  //if the player that has the pUp is p2  (logic could be changed later)
		{
			pad2.isInvis = 0;

		}

		invis.isActive = 0; //pUp is no longer active
	}
	
	//Reverse
	/*if (reverse.isActive == true && reverse.clock.getElapsedTime() > seconds(1))
	{

		if (pad1.isReverse) //if the player that has the pUp is p1  (logic could be changed later)
		{
			pad1.isReverse = 0;

		}
		else  //if the player that has the pUp is p2  (logic could be changed later)
		{
			pad2.isReverse = 0;

		}

		reverse.isActive = 0; //pUp is no longer active
	}*/

}