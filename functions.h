// Headers

#include <stdlib.h>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>

using namespace std;
using namespace sf;

const float padlengthSTD = 125;

// Defining some Constants

// for the screen
#define GAMEWIDTH 800
#define GAMEHEIGHT 600

// for the bounding the pads
#define PADDINGTOP 10
#define PADDINGBOTTOM 10

// ball Radius
#define ballRadius 10.f

// Defined here to be easily accessed by functions 
Event event;

// Structures
struct PAD
{
	// Width is constant
	const int width = 20;

	// Length will vary
	int length;

	RectangleShape rect;

	Texture texture;

	int velocity;

	bool isFrozen = 0;

	bool isInvis = 0;

	bool isSlow = 0;

	bool isReverse = 0;

	// Resets all variable pad attributes
	// Take a a pad's number (1 or 2) to set each pad's position correctly
	void ResetPad(int pad_number, char& mode)
	{
		// Set length of pad
		length = 125;
		if (mode != 't') {
			// Create the rectangle shape with given length and width
			rect.setSize(Vector2f(width, length));

			// Set the orgin
			rect.setOrigin(width / 2.f, length / 2.f);
		}
		// Set the position
		if (pad_number == 2)
			rect.setPosition(GAMEWIDTH - width -  /*the needed distance*/ 30, 300);
		else if (pad_number == 1)
			rect.setPosition(width + /*the needed distance*/ 30, 300);
		else if (pad_number == 3)
			rect.setPosition(250, 300);
		else
			rect.setPosition(500, 300);
		// This is done to return the pad's fill color back to normal if the game exits while it isn't
		rect.setFillColor(Color::White);
		
		isInvis = 0;
		isSlow = 0;
		isFrozen = 0;
		isReverse = 0;
	}

	// Takes states of buttons and returns a key representing how the pad should move
	// 0 = Don't move, +ve = Move up, -ve = Move down
	int Get_Movement(bool W, bool S)
	{
		// if the pad is currently slowed v = 3, else v = 10
		int v = isSlow ? 3 : 10;

		// Both or neither keys are pressed
		if ((W && S) || (!W && !S) || isFrozen)
		{
			return 0;
		}

		if (W)
		{
			return v;
		}

		if (S)
		{
			return -v;
		}

		return 0;
	}
	// Takes a reference to a pad, prevents it from getting out of bounds
	// to set the bounds change the constant PADDINGTOP & PADDINGBOTTOM
	bool boundcheck()
	{
		if (rect.getPosition().y - length / 2 < PADDINGTOP)
		{
			rect.move(0, -velocity);
			return true;
		}
		if (rect.getPosition().y + length / 2 > GAMEHEIGHT - PADDINGBOTTOM)
		{
			rect.move(0, -velocity);
			return true;
		}
		return false;

	}
};


struct BALL
{
	CircleShape circle;
	Texture texture;

	// Set default ball speed
	int xVelocity = -5,
		yVelocity = -5;

	// Multiplies by 2 every 5 seconds and resets when one of the players scores
	int added_velocity = 0;
	Clock clock;
	void gain_velocity(void)
	{
		Time t = clock.getElapsedTime();
		// Maximum gained velocity is 16 
		if (t.asSeconds() >= 5 && added_velocity < 16)
		{
			if (added_velocity == 0)
			{
				added_velocity++;
			}
			else
			{
				added_velocity *= 2;
			}
			clock.restart();
		}
	}


};


// Functions

// takes a key code, returns true if its pressed, false if not
bool isPressed(Keyboard::Key x)
{
	if (Keyboard::isKeyPressed(x))
	{
		return true;
	}
	return false;
}


// takes a reference to a BALL, positions it in a random position in the middle
void RandomPos(BALL& ball,int mapnum,RectangleShape obstacle)
{
	int x, random = rand() % 2;
	
	//Prevent spawn at center due to pressence of an obstacle
	if (mapnum == 2)
	{
		//spawn right of obstacle
		if (random)
		{
			x = 400 + obstacle.getSize().x / 2 + ball.circle.getRadius() + 20;
		}
		//spawn left of obstacle
		else
		{
			x = 400 - obstacle.getSize().x / 2 - ball.circle.getRadius() - 20;
		}
	}
	//spawn at center
	else 
		x = 400;
	
	int y = 300;

	//Reset velocity to a sum of 8 to give players some kind of reset after a goal (the ball starts slow then speeds up after first contact with pad)
	ball.xVelocity = 6 + rand() % 2;
	ball.yVelocity = 8 - ball.xVelocity;
	// Random direction
	if (mapnum == 2)
	{
		//prevent ball from going towards obstacle if it's spawned at the left
		if (x < 400)
		{
			ball.xVelocity *= -1;
		}
	}
	else
	{
		if (rand() % 2 == 0)
			ball.xVelocity *= -1;
		if (rand() % 2 == 0)
			ball.yVelocity *= -1;

	}

	ball.circle.setPosition(x,y);
}




// Takes a reference to the ball, reverses velocity in the y direction when it hits a wall
// and brings it back to a random position in the middle when out of horizontal bounds

// changed return type to int to get a return key represeting what sound should be played 
int boundcheck_ball(BALL& ball,int mapnum,RectangleShape obstacle)
{
	// horizonal bounding
	if (ball.circle.getPosition().x + ballRadius < 0)
	{
		// left pad lost
		RandomPos(ball,mapnum,obstacle);
		return 1; // Score sound should be plated
	}
	if (ball.circle.getPosition().x - ballRadius > GAMEWIDTH)
	{
		// right pad lost
		RandomPos(ball, mapnum, obstacle);
		return 1;
	}

	//vertical bounding
	if (
		ball.circle.getPosition().y + ballRadius > GAMEHEIGHT
		||
		ball.circle.getPosition().y - ballRadius < 0
		)
	{
		ball.yVelocity *= -1;
		return 2; // Wall hit sound should be played
	}
	return 0; // nothing should be played
}





/*
	Collision functions takes the ball and the rectangleshape and apply collision mechanics
*/

// Collision form the left (for the Right pad only) >>|
bool isCollidingFromLeft(BALL& ball, RectangleShape& shape,bool up, bool down)
{
	bool return_value = false;
	if (
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().x + ballRadius > shape.getPosition().x - shape.getSize().x / 2
		&&
		// to check that the ball is at right side of the shape's orgin
		ball.circle.getPosition().x + ballRadius < shape.getPosition().x
		&&
		// to apply collision when only the ball or some of it is touching the left side of the shape
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		||
		ball.circle.getGlobalBounds().intersects(shape.getGlobalBounds())
		)
	{
		return_value = true;
		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x - ballRadius - shape.getSize().x / 2 - 0.1f, ball.circle.getPosition().y);

		

		//Dynamic Collison

		if (abs(ball.circle.getPosition().y - shape.getPosition().y) < 10) //if the ball hits near the mid it reflects in straight line
		{
			ball.xVelocity = 12 + ball.added_velocity;
			ball.yVelocity = 0;
		}
		//First 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y - (shape.getSize().y / 2 + 10)
			&&
			// bottom
			ball.circle.getPosition().y <= shape.getPosition().y - shape.getSize().y / 4
			)
		{

			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -8 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 8 + ball.added_velocity;
				}
				else
				{
					if (rand() % 2 == 0)
						ball.yVelocity = -8 - ball.added_velocity;
					else
						ball.yVelocity = 8 + ball.added_velocity;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8 + ball.added_velocity;

			}
			else
				ball.yVelocity = -8 - ball.added_velocity;
		}
		//Second 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y - shape.getSize().y / 4
			&&
			// bottom
			ball.circle.getPosition().y < shape.getPosition().y
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement 
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -6 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 6 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -6 - ball.added_velocity;
					else
						ball.yVelocity = 6 + ball.added_velocity;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6 + ball.added_velocity;
			}
			else
				ball.yVelocity = -6 - ball.added_velocity;
		}
		//Third 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y
			&&
			// bottom
			ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 4
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -6 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 6 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -6 - ball.added_velocity;
					else
						ball.yVelocity = 6 + ball.added_velocity;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6 + ball.added_velocity;
			}
			else
				ball.yVelocity = -6 - ball.added_velocity;
		}
		//Fourth 1/4
		else if (
			// top
			ball.circle.getPosition().y >= shape.getPosition().y + shape.getSize().y / 4
			&&
			// bottom
			ball.circle.getPosition().y <= shape.getPosition().y + (shape.getSize().y / 2 + 10)
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -8 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 8 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -8 - ball.added_velocity;
					else
						ball.yVelocity = 8 + ball.added_velocity;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8 + ball.added_velocity;
			}
			else
				ball.yVelocity = -8 - ball.added_velocity;
		}

		//relating two V's to a constant
		if (ball.xVelocity != 12 + ball.added_velocity)//if not reflecting straight
			ball.xVelocity = 15 + ball.added_velocity - abs(ball.yVelocity);

		ball.xVelocity *= -1;
	}
	
	return return_value;
}

//general collision overload
bool isCollidingFromLeft(BALL& ball, RectangleShape& shape)
{
	bool return_value = false;
	if (
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().x + ballRadius > shape.getPosition().x - shape.getSize().x / 2
		&&
		// to check that the ball is at right side of the shape's orgin
		ball.circle.getPosition().x + ballRadius < shape.getPosition().x
		&&
		// to apply collision when only the ball or some of it is touching the left side of the shape
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		)
	{
		return_value = true;
		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x - ballRadius - shape.getSize().x / 2 - 0.1f, ball.circle.getPosition().y);

		ball.xVelocity *= -1;
	}

	return return_value;
}


// Collision form the Right (for the left pad only) |<<
bool isCollidingFromRight(BALL& ball, RectangleShape& shape, bool up, bool down, char MODE)
{
	bool return_value = false;
	if (
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().x - ballRadius < shape.getPosition().x + shape.getSize().x / 2
		&&
		// to check that the ball is at left side of the shape's orgin
		ball.circle.getPosition().x - ballRadius > shape.getPosition().x
		&&
		// to apply collision when only the ball or some of it is touching the left side of the shape
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		||
		ball.circle.getGlobalBounds().intersects(shape.getGlobalBounds())

		)
	{
		return_value = true;
		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 + 0.1f, ball.circle.getPosition().y);

		//shape.setOrigin(0, 0);

		//Comments available at left collision
		if (abs(ball.circle.getPosition().y - shape.getPosition().y) < 10)
		{
			if (MODE == 'a')
			{
				ball.yVelocity = 0;
				//ball doesn't keep reflecting straight
				if (rand() % 2 == 0)
				{
					if (rand() % 2 == 0)
						ball.yVelocity = 2;
					else
						ball.yVelocity = -2;

				}
				ball.xVelocity = 12 - abs(ball.yVelocity) + ball.added_velocity;

			}
			else
			{
				ball.xVelocity = 12 + ball.added_velocity;
				ball.yVelocity = 0;
			}
			
		}
		//First 1/4
		else if (
			// top
			ball.circle.getPosition().y >= shape.getPosition().y - shape.getSize().y / 2
			&&
			// bottom
			ball.circle.getPosition().y <= shape.getPosition().y - shape.getSize().y / 4
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -8 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 8 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -8;
					else
						ball.yVelocity = 8;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8 + ball.added_velocity;

			}
			else
				ball.yVelocity = -8 - ball.added_velocity;
		}
		// Second 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y - shape.getSize().y / 4
			&&
			// bottom
			ball.circle.getPosition().y < shape.getPosition().y
			)
		{
			
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -6 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 6 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -6;
					else
						ball.yVelocity = 6;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6 + ball.added_velocity;
			}
			else
				ball.yVelocity = -6 - ball.added_velocity;
		}
		//Third 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y
			&&
			// bottom
			ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 4
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -6 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 6 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -6;
					else
						ball.yVelocity = 6;
				}
			}
			else if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6 + ball.added_velocity;
			}
			else
				ball.yVelocity = -6 - ball.added_velocity;
		}
		//Fourth 1/4
		else if (
			// top
			ball.circle.getPosition().y >= shape.getPosition().y + shape.getSize().y / 4
			&&
			// bottom
			ball.circle.getPosition().y <= shape.getPosition().y + shape.getSize().y / 2
			)
		{
			//if ball is coming straight the direction of reflection depends on  movement
			if (ball.yVelocity == 0)
			{
				if (up)
				{
					ball.yVelocity = -8 - ball.added_velocity;
				}
				else if (down)
				{
					ball.yVelocity = 8 + ball.added_velocity;
				}
				else
				{
					//if not moving reflects to a random direction
					if (rand() % 2 == 0)
						ball.yVelocity = -8;
					else
						ball.yVelocity = 8;
				}
			}
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8 + ball.added_velocity;
			}
			else
				ball.yVelocity = -8 - ball.added_velocity;
		}
		if (ball.xVelocity != 12 + ball.added_velocity)
			ball.xVelocity = 15 + ball.added_velocity - abs(ball.yVelocity);
	}
	
	return return_value;

}

//general collision overload
bool isCollidingFromRight(BALL& ball, RectangleShape& shape)
{
	bool return_value = false;
	if (
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().x - ballRadius < shape.getPosition().x + shape.getSize().x / 2
		&&
		// to check that the ball is at left side of the shape's orgin
		ball.circle.getPosition().x - ballRadius > shape.getPosition().x
		&&
		// to apply collision when only the ball or some of it is touching the left side of the shape
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		)
	{
		return_value = true;
		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 + 0.1f, ball.circle.getPosition().y);

		ball.xVelocity *= -1;
	}

	return return_value;

}





// A general Collision detection (Disabled for now) to be used with other objects
bool isColliding(BALL& ball, RectangleShape& shape)
{
	 //this collison is disabled for the pads//
	bool return_value = false;
	// From top
	if (
		// to apply collision when only the ball or some of it is touching the upper side of the shape
		ball.circle.getPosition().x +ballRadius  >= shape.getPosition().x - shape.getSize().x/2.f 
		&&
		ball.circle.getPosition().x - ballRadius <= shape.getPosition().x + shape.getSize().x/2.f
		&&
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y /2.f
		&& 
		// to check that the ball is at upper side of the shape's orgin
		ball.circle.getPosition().y + ballRadius < shape.getPosition().y
		)
	{
		ball.circle.setPosition(ball.circle.getPosition().x ,shape.getPosition().y - ballRadius - shape.getSize().y / 2 - 0.5f);
		cout << "TOP" << endl;
		ball.yVelocity *= -1;
		return_value = true;
	}
	// From Bottom
	if (
		// to apply collision when only the ball or some of it is touching the down side of the shape
		ball.circle.getPosition().x + ballRadius >= shape.getPosition().x - shape.getSize().x / 2.f
		&&
		ball.circle.getPosition().x - ballRadius <= shape.getPosition().x + shape.getSize().x / 2.f
		&&
		// to check if the ball has gone into the shape after moving
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2.f
		&&
		// to check that the ball is at down side of the shape's orgin
		ball.circle.getPosition().y - ballRadius > shape.getPosition().y
		)
	{
		
		ball.circle.setPosition(ball.circle.getPosition().x, shape.getPosition().y + ballRadius + shape.getSize().y / 2 + 0.5f);
		cout << "BOT" << endl;
		ball.yVelocity *= -1;
		return_value = true;
	}
	
	return return_value;
}

// the function checks wether the ball is below or above the pad and moves the pad accordingly
int ai_move(PAD& pad, BALL& ball)
{	
	
	
	int error = 10;
	if (rand() % 10000 > 9995) //chance for changing error (prevents shaky movement)
	{
		error = rand() % 100;
	}
	float diff = pad.rect.getPosition().y - ball.circle.getPosition().y;

	//ball going towards pad       ball above pad
	if (ball.xVelocity < 0 && diff >= -error && diff <= error)
	{
		return 0;
	}
	if (ball.xVelocity < 0 && diff > error)
	{
		return -1; //move it up
	}
	//ball going towards pad       ball below pad
	else if (ball.xVelocity < 0 && diff < error )
	{
		return 1; //move it down
	}
}



//////////////  THEMES ////////////////

//Control themes functions , takes char indicating selected theme and switches all elements accordingly
void set_theme(PAD& pad1, PAD& pad2, BALL& ball, Texture& backgT, RectangleShape& backg,
	SoundBuffer& pad, SoundBuffer& wall, SoundBuffer& score, SoundBuffer& background, char c, RectangleShape& obsTop, RectangleShape& obsBot , Texture& obsTopTex, Texture& obsBotTex)
{
	//Hell
	if (c == 'h')
	{
		//Load files

			// vfx
		pad1.texture.loadFromFile("resources/vfx/hell/hellpadleft.png");


		pad2.texture.loadFromFile("resources/vfx/hell/hellpadright.png");


		ball.texture.loadFromFile("resources/vfx/hell/hellball.png");


		backgT.loadFromFile("resources/vfx/hell/hellbackg3.png");

		obsTopTex.loadFromFile("resources/vfx/hell/fireMapTexture.png");
		obsBotTex.loadFromFile("resources/vfx/hell/fireMapTexture.png");


		// sfx
		pad.loadFromFile("resources/sfx/fire/pad.wav");
		wall.loadFromFile("resources/sfx/fire/wall.wav");
		score.loadFromFile("resources/sfx/fire/score.wav");
		background.loadFromFile("resources/sfx/fire/background.ogg");

	
	}
	//Ice
	else if (c == 'i')
	{
		pad1.texture.loadFromFile("resources/vfx/ice/icepadleft2.png");


		pad2.texture.loadFromFile("resources/vfx/ice/icepadright2.png");


		ball.texture.loadFromFile("resources/vfx/ice/iceball.png");


		backgT.loadFromFile("resources/vfx/ice/icebackglight.png");



		// sfx
		pad.loadFromFile("resources/sfx/ice/pad.wav");
		wall.loadFromFile("resources/sfx/ice/wall.wav");
		score.loadFromFile("resources/sfx/ice/score.wav");
		background.loadFromFile("resources/sfx/ice/background.wav");

	}
	//Forest
	else if (c == 'f')
	{
		pad1.texture.loadFromFile("resources/vfx/forest/forestpadleft.png");


		pad2.texture.loadFromFile("resources/vfx/forest/forestpadright.png");


		ball.texture.loadFromFile("resources/vfx/forest/forestball.png");


		backgT.loadFromFile("resources/vfx/forest/forestbackg.png");



		pad.loadFromFile("resources/sfx/forest/pad.wav");
		wall.loadFromFile("resources/sfx/forest/wall.wav");
		score.loadFromFile("resources/sfx/forest/score.wav");
		background.loadFromFile("resources/sfx/forest/background.wav");

	}
	else if (c == 'c')
	{
		backgT.loadFromFile("resources/vfx/classic/classicbackg.png");

		pad1.texture.loadFromFile("resources/vfx/classic/classicpad.png");


		pad2.texture.loadFromFile("resources/vfx/classic/classicpad.png");


		ball.texture.loadFromFile("resources/vfx/classic/classicball.png");

		

		pad.loadFromFile("resources/sfx/classic/pad.wav");
		wall.loadFromFile("resources/sfx/classic/wall.wav");
		score.loadFromFile("resources/sfx/classic/score.wav");

	}

	//Set files
	backg.setTexture(&backgT);
	ball.circle.setTexture(&ball.texture);
	pad1.rect.setTexture(&pad1.texture);
	pad2.rect.setTexture(&pad2.texture);
	obsTop.setTexture(&obsTopTex);
	obsBot.setTexture(&obsBotTex);

}
////////// MODES /////////



void Modes(PAD& pad, BALL& ball, char c, bool froze, bool slow, bool& W, bool& S)
{
	//AI player mode
	if (c == 'a')
	{
		if (!froze) //it can only take input if not frozen
		{
			
			
			if (slow) //changing speed depending if slowed or not
			{
				pad.velocity = ai_move(pad, ball) * 4;
			}
			else
				pad.velocity = ai_move(pad, ball) * 10;
			
			pad.rect.move(0, pad.velocity);
			pad.boundcheck();
			

		}
	}

	//two player mode
	if (c == '2')
	{
			//it can only take input if not frozen
		

			if (slow) //changing speed depending if slowed or not
			{
				pad.velocity = pad.Get_Movement(S, W);
			}
			else if (pad.isReverse)
			{
				pad.velocity = pad.Get_Movement(W, S);
			}
			else
				pad.velocity = pad.Get_Movement(S, W);

			pad.rect.move(0, pad.velocity);
			pad.boundcheck();

		
	}

	//trainig mode
	if (c == 't')
	{
		pad.length = GAMEHEIGHT;
		pad.rect.setSize(Vector2f(pad.width, GAMEHEIGHT));
		pad.rect.setOrigin(pad.width / 2.f, pad.length / 2.f);
		pad.rect.setPosition(pad.width + /*the needed distance*/ 30, 300);
		pad.velocity = pad.Get_Movement(false, false);
	}

}

// Takes references to everything drawn in game and handles their drawing conditions
void DrawGame(RenderWindow& window,RectangleShape& backg, PAD& pad1, PAD& pad2, PAD& pad3, PAD& pad4, BALL& ball, Text& lblscorep1, Text& lblscorep2, RectangleShape& obsTop, RectangleShape& obsBot, int mapnum)
{

	// Background
	window.draw(backg);

	// Ball
	window.draw(ball.circle);

	// Pads
	if (!pad1.isInvis)
		window.draw(pad1.rect);
	if (!pad2.isInvis)
		window.draw(pad2.rect);

	//Draw map components
	if (mapnum == 1)
	{
		window.draw(obsTop);
		window.draw(obsBot);
	}
	else if (mapnum == 2)
	{
		window.draw(obsTop);
	}
	else if (mapnum == 3)
	{
		window.draw(pad3.rect);
		window.draw(pad4.rect);
	}
	//draw score of player 1 
	window.draw(lblscorep1);

	//draw score of player 2
	window.draw(lblscorep2);

}

//Maps
char mode;
//Takes reference to map components and handles their initilization 
void set_map(RectangleShape& obsTop, RectangleShape& obsBot, PAD& pad3, PAD& pad4, int mapnum)
{
	if (mapnum == 1)
	{
		obsTop.setSize(Vector2f(200, 150));
		obsTop.setOrigin(Vector2f(obsTop.getSize().x / 2, obsTop.getSize().y / 2));
		obsTop.setPosition(Vector2f(400, (obsTop.getSize().y / 2)));
		//obsTop.setFillColor(Color::Red);
		

		obsBot.setSize(Vector2f(200, 150));
		obsBot.setOrigin(Vector2f(obsBot.getSize().x / 2, obsBot.getSize().y / 2));
		obsBot.setPosition(Vector2f(400, (600 - obsBot.getSize().y / 2)));
		//obsBot.setFillColor(Color::Yellow);
		
	}
	else if (mapnum == 2)
	{
		obsTop.setSize(Vector2f(50, 150));
		obsTop.setOrigin(Vector2f(obsTop.getSize().x / 2, obsTop.getSize().y / 2));
		obsTop.setPosition(Vector2f(400, 300));
		obsTop.setFillColor(Color::Red);
	}
	else if (mapnum == 3)
	{
		pad3.ResetPad(3,mode);
		pad3.velocity = 5;
		pad4.ResetPad(4,mode);
		pad4.velocity = -5;
	}
}

//Takes reference to map components and handels their collisions
void map_collision(BALL& ball, RectangleShape& obsTop, RectangleShape& obsBot, PAD& pad3, PAD& pad4, int mapnum)
{
	if (mapnum == 1)
	{
		//BOTTOM OBSTACLE
		if ((ball.circle.getPosition().y + ball.circle.getRadius()) >= (obsBot.getPosition().y - (obsBot.getSize().y / 2) )) //Ball collided with bottom obstacle
		{
			//Ball collided with the top of the bottom obstacle
			if (ball.circle.getPosition().x >= (obsBot.getPosition().x - (obsBot.getSize().x / 2)) && ball.circle.getPosition().x <= (obsBot.getPosition().x + (obsBot.getSize().x / 2)))
			{
				
				ball.yVelocity *= -1;
			}
			//ball collided with it's side
			else
			{
				isCollidingFromLeft(ball, obsBot);
				isCollidingFromRight(ball, obsBot);

			}
		}

		//TOP OBSTACLE
		if ((ball.circle.getPosition().y - ball.circle.getRadius()) <= (obsTop.getPosition().y + (obsTop.getSize().y / 2))) //Ball collided with top obstacle
		{
			//Ball collided with the bottom of the toop obstacle
			if (ball.circle.getPosition().x >= (obsTop.getPosition().x - (obsTop.getSize().x / 2)) && ball.circle.getPosition().x <= (obsTop.getPosition().x + (obsTop.getSize().x / 2)))
			{
				
				ball.yVelocity *= -1;
			}
			//ball collided with it's side
			else
			{
				isCollidingFromLeft(ball, obsTop);
				isCollidingFromRight(ball, obsTop);

			}
		}
		
		
		
	
	}
	else if (mapnum == 2)
	{
		//ball beside obstacle
		if (ball.circle.getPosition().y > obsTop.getPosition().y - obsTop.getSize().y / 2 && ball.circle.getPosition().y < obsTop.getPosition().y + obsTop.getSize().y /2 ) 
		{
			isCollidingFromLeft(ball, obsTop);
			isCollidingFromRight(ball, obsTop);
		}
		else
		{
			isColliding(ball, obsTop);
		}
		
	}
	else if (mapnum == 3)
	{
		pad3.rect.move(0, pad3.velocity);
		if (pad3.boundcheck())
		{
			pad3.velocity *= -1;
		}
		pad4.rect.move(0, pad4.velocity);
		if (pad4.boundcheck())
		{
			pad4.velocity *= -1;
		}
		if (!isCollidingFromLeft(ball, pad3.rect) && !isCollidingFromRight(ball, pad3.rect))
		{
			isColliding(ball, pad3.rect);
		}
		if (!isCollidingFromLeft(ball, pad4.rect) && !isCollidingFromRight(ball, pad4.rect))
		{
			isColliding(ball, pad4.rect);
		}
	}
}

void LOAD_USER_SETTINGS(char SETTINGS[])
{
	ifstream Infile;
	Infile.open("user_settings.txt");

	string s;
	getline(Infile, s);
	for (int i = 0; i < 4; i++)
	{
		SETTINGS[i] = s[i];
	}
}

void SAVE_USER_SETTINGS(char SETTINGS[4])
{
	ofstream Outfile;
	Outfile.open("user_settings.txt");
	
	for (int i = 0; i < 4; i++)
	{
		Outfile << SETTINGS[i];
	}
	Outfile.close();

}