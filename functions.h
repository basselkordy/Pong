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
	
	// Random x  300 -> 500
	int x = 300 + rand() % 200;
	// Random y  100 ->300
	int y = 100 + rand() % 200;
	// Random direction
	if (x % 2 == 0)
		ball.xVelocity *= -1;
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
void boundcheck_ball(BALL& ball)
{
	// horizonal bounding
	if (ball.circle.getPosition().x + ballRadius < 0)
	{
		// left pad lost
		RandomPos(ball);
	}
	if (ball.circle.getPosition().x - ballRadius > GAMEWIDTH)
	{
		// right pad lost
		RandomPos(ball);
	}

	//vertical bounding
	if (
		ball.circle.getPosition().y + ballRadius > GAMEHEIGHT
		||
		ball.circle.getPosition().y - ballRadius < 0
		)
	{
		ball.yVelocity *= -1;
	}
}


/*
	Collision functions takes the ball and the rectangleshape and apply collision mechanics
*/

// Collision form the left (for the Right pad only) >>|
void isCollidingFromLeft(BALL& ball, RectangleShape& shape)
{
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

		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x - ballRadius - shape.getSize().x / 2 - 0.1f, ball.circle.getPosition().y);

		shape.setOrigin(0, 0);

		//Dynamic Collison

		if (abs(ball.circle.getPosition().y - shape.getPosition().y) < 20) //if the ball hits near the mid it reflects in straight line
		{
			ball.xVelocity = 12;
			ball.yVelocity = 0;
		}
		if (ball.circle.getPosition().y > shape.getPosition().y&& ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 4) //ball hits near end of pad
		{


			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;

			}
			else
				ball.yVelocity = -6;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + shape.getSize().y / 4 && ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 2) //ball hits near top first quarter of pad
		{

			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 9;
			}
			else
				ball.yVelocity = -9;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + shape.getSize().y / 2 && ball.circle.getPosition().y < shape.getPosition().y + 3 * shape.getSize().y / 4) //ball hits near botttom first quarter of pad
		{

			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 9;
			}
			else
				ball.yVelocity = -9;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + 3 * shape.getSize().y / 4 && ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y) //ball hits near end of pad
		{
			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
		}

		//relating two V's to a constant
		if (ball.xVelocity != 12)//if not reflecting straight
			ball.xVelocity = 15 - abs(ball.yVelocity);

			ball.xVelocity *= -1;
	}
	shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
}
// Collision form the Right (for the left pad only) |<<
void isCollidingFromRight(BALL& ball, RectangleShape& shape)
{
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
		// to make the ball bounce back after the collision
		ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 + 0.1f, ball.circle.getPosition().y);

		shape.setOrigin(0, 0);

		//Comments available at left collision
		if ( abs(ball.circle.getPosition().y - shape.getPosition().y ) < 20)
		{
			ball.xVelocity = 12;
			ball.yVelocity = 0;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y&& ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 4)
		{


			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;

			}
			else
				ball.yVelocity = -6;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + shape.getSize().y / 4 && ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y / 2)
		{

			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 9;
			}
			else
				ball.yVelocity = -9;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + shape.getSize().y / 2 && ball.circle.getPosition().y < shape.getPosition().y + 3 * shape.getSize().y / 4)
		{

			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 9;
			}
			else
				ball.yVelocity = -9;
		}
		else if (ball.circle.getPosition().y > shape.getPosition().y + 3 * shape.getSize().y / 4 && ball.circle.getPosition().y < shape.getPosition().y + shape.getSize().y)
		{

			//ball.xVelocity *= -1;
			if (ball.yVelocity > 0)
			{
				ball.yVelocity = 6;
			}
			else
				ball.yVelocity = -6;
		}
		if (ball.xVelocity != 12)
			ball.xVelocity = 15 - abs(ball.yVelocity);

		shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);

	}
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



///////////// POWER UPS  ///////////////

//elongate function takes a pad and a bool to return longer length if it's activated or normal length if it's deactivated
//the pad part is not crucial but it's for code's flexability 
int elongate(PAD pad, bool active)
{
	if (active == true)
	{
		return pad.length *= 2;
	}
	else
	{
		return pad.length = padlengthSTD;
	}



}