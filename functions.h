// Headers
//NEW
#include <stdlib.h>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

};


struct BALL
{
	CircleShape circle;
	Texture texture;

	// Set default ball speed
	int xVelocity = -5,
		yVelocity = -5;


};

//struct containing powerup attributes

struct pUp
{
	CircleShape circle; //pUp shape
	Texture texture; // pUp texture
	bool isSpawned; // Bool to check if the pUP on the screen aka "spawned"
	bool isActive; // bool to check if the a player has picked the pUP and it's working on him now

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
void RandomPos(BALL& ball)
{
	
	//spawn at centre
	int x = 400;
	
	int y = 300;

	//Reset velocity to a sum of 8 to give players some kind of reset after a goal (the ball starts slow then speeds up after first contact with pad)
	ball.xVelocity = 6 + rand() % 2;
	ball.yVelocity = 8 - ball.xVelocity;
	// Random direction
	if (rand() % 2 == 0)
		ball.xVelocity *= -1;
	if (rand() % 2 == 0)
		ball.yVelocity *= -1;

	ball.circle.setPosition(x,y);
}


// Takes states of buttons and returns a key representing how the pad should move
// 0 = Don't move, 1 = Move up, -1 = Move down
int Get_Movement(bool W, bool S)
{
	// Both or neither keys are pressed
	if ((W && S) || (!W && !S))
	{
		return 0;
	}

	if (W)
	{
		return 1;
	}

	if (S)
	{
		return -1;
	}

	return 0;
}

// Takes a reference to a pad, prevents it from getting out of bounds
// to set the bounds change the constant PADDINGTOP & PADDINGBOTTOM
void boundcheck(PAD& pad)
{
	if (pad.rect.getPosition().y - pad.length / 2 < PADDINGTOP)
	{
		pad.rect.move(0, -pad.velocity);
	}
	if (pad.rect.getPosition().y + pad.length / 2 > GAMEHEIGHT - PADDINGBOTTOM)
	{
		pad.rect.move(0, -pad.velocity);
	}

}


// Takes a reference to the ball, reverses velocity in the y direction when it hits a wall
// and brings it back to a random position in the middle when out of horizontal bounds

// changed return type to int to get a return key represeting what sound should be played 
int boundcheck_ball(BALL& ball)
{
	// horizonal bounding
	if (ball.circle.getPosition().x + ballRadius < 0)
	{
		// left pad lost
		RandomPos(ball);
		return 1; // Score sound should be plated
	}
	if (ball.circle.getPosition().x - ballRadius > GAMEWIDTH)
	{
		// right pad lost
		RandomPos(ball);
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

		

		//Dynamic Collison

		if (abs(ball.circle.getPosition().y - shape.getPosition().y) < 20) //if the ball hits near the mid it reflects in straight line
		{
			ball.xVelocity = 10;
			ball.yVelocity = 0;
		}
		//First 1/4
		else if (
			// top
			ball.circle.getPosition().y > shape.getPosition().y - shape.getSize().y / 2
			&&
			// bottom
			ball.circle.getPosition().y <= shape.getPosition().y - shape.getSize().y / 4
			)
		{


			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8;

			}
			else
				ball.yVelocity = -8;
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

			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
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

			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
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
			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8;
			}
			else
				ball.yVelocity = -8;
		}

		//relating two V's to a constant
		if (ball.xVelocity != 12)//if not reflecting straight
			ball.xVelocity = 15 - abs(ball.yVelocity);

		ball.xVelocity *= -1;
	}
	
	return return_value;
}
// Collision form the Right (for the left pad only) |<<
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

		//shape.setOrigin(0, 0);

		//Comments available at left collision
		if (abs(ball.circle.getPosition().y - shape.getPosition().y) < 20)
		{
			ball.xVelocity = 12;
			ball.yVelocity = 0;
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

			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8;

			}
			else
				ball.yVelocity = -8;
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
			

			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
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
			
			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
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
			
			
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 8;
			}
			else
				ball.yVelocity = -8;
		}
		if (ball.xVelocity != 12)
			ball.xVelocity = 15 - abs(ball.yVelocity);
	}
	
	return return_value;

}





// A general Collision detection (Disabled for now) to be used with other objects
void isColliding(BALL& ball, RectangleShape& shape)
{
	// this collison is disabled for the pads//
	//
	// From top
	//if (
	//	ball.circle.getPosition().y + ballRadius > shape.getPosition().y - shape.getSize().y / 2
	//	&&
	//	ball.circle.getPosition().y + ballRadius < shape.getPosition().y
	//	&&
	//	ball.circle.getPosition().x - ballRadius <= shape.getPosition().x + shape.getSize().x / 2
	//	&&
	//	ball.circle.getPosition().x + ballRadius >= shape.getPosition().x - shape.getSize().x / 2
	//	)
	//{
	//	ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 + 0.1f, ball.circle.getPosition().y);
	//	ball.yVelocity *= -1;
	//}
	//// From Bottom
	//if (
	//	ball.circle.getPosition().y - ballRadius < shape.getPosition().y + shape.getSize().y / 2
	//	&&
	//	ball.circle.getPosition().y - ballRadius > shape.getPosition().y
	//	&&
	//	ball.circle.getPosition().x - ballRadius <= shape.getPosition().x + shape.getSize().x / 2
	//	&&
	//	ball.circle.getPosition().x + ballRadius >= shape.getPosition().x - shape.getSize().x / 2
	//	)
	//{
	//	ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 - 0.1f, ball.circle.getPosition().y);
	//	ball.yVelocity *= -1;
	//}
	//
}

// the function checks wether the ball is below or above the pad and moves the pad accordingly
int ai_move(PAD& pad, BALL& ball)
{
	//ball going towards pad       ball above pad
	if (ball.xVelocity < 0 && pad.rect.getPosition().y - ball.circle.getPosition().y >= 10)
	{
		return -1; //move it up
		

	}
	//ball going towards pad       ball below pad
	else if (ball.xVelocity < 0 && pad.rect.getPosition().y - ball.circle.getPosition().y < 10)
	{
		return 1; //move it down
	}
}

///////////// POWER UPS  ///////////////

//elongate function takes a pad and a bool to return longer length if it's activated or normal length if it's deactivated
//the pad part is not crucial but it's for code's flexability 
void elongate(PAD& pad1,PAD& pad2, bool active,char c)
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

//////////////  THEMES ////////////////

//Control themes functions , takes char indicating selected theme and switches all elements accordingly
void set_theme (PAD& pad1,PAD& pad2,BALL& ball,Texture& backgT,RectangleShape& backg,char c)
{
	//Hell
	if (c == 'h')
	{
		//Load files
		pad1.texture.loadFromFile("resources/vfx/hell/hellpadleft.png");
		

		pad2.texture.loadFromFile("resources/vfx/hell/hellpadright.png");
		

		ball.texture.loadFromFile("resources/vfx/hell/hellball.png");
		

		backgT.loadFromFile("resources/vfx/hell/hellbackg.jpg");
		

	}
	//Ice
	else if (c == 'i')
	{
		pad1.texture.loadFromFile("resources/vfx/ice/icepadleft.png");


		pad2.texture.loadFromFile("resources/vfx/ice/icepadright.png");


		ball.texture.loadFromFile("resources/vfx/ice/iceball.png");


		backgT.loadFromFile("resources/vfx/ice/icebackg.png");
	}
	//Forest
	else if (c == 'f')
	{
		pad1.texture.loadFromFile("resources/vfx/forest/forestpadleft.png");


		pad2.texture.loadFromFile("resources/vfx/forest/forestpadright.png");


		ball.texture.loadFromFile("resources/vfx/forest/forestball.png");


		backgT.loadFromFile("resources/vfx/forest/forestbackg.png");
	}

	//Set files
	backg.setTexture(&backgT);
	ball.circle.setTexture(&ball.texture);
	pad1.rect.setTexture(&pad1.texture);
	pad2.rect.setTexture(&pad2.texture);

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
			pad.length = 125.0f;
			pad.rect.move(0, pad.velocity);
			boundcheck(pad);
			

		}
	}

	//two player mode
	if (c == '2')
	{
		if (!froze) //it can only take input if not frozen
		{

			if (slow) //changing speed depending if slowed or not
			{
				pad.velocity = Get_Movement(S, W) * 3;
			}
			else
				pad.velocity = Get_Movement(S, W) * 10;

			pad.rect.move(0, pad.velocity);
			boundcheck(pad);

		}
	}

	//trainig mode
	if (c == 't')
	{
		pad.length = GAMEHEIGHT;
		pad.rect.setSize(Vector2f(pad.width, pad.length));
		pad.rect.setOrigin(pad.width / 2.f, pad.length / 2.f);
		pad.rect.setPosition(pad.width + /*the needed distance*/ 30, 300);
		pad.velocity = Get_Movement(false, false);
	}

}

