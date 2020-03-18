// Headers
#include <stdlib.h>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

// Defining some Constants
// for the screen
#define GAMEWIDTH 800
#define GAMEHEIGHT 600
// for the bounding the pads
#define PADDINGTOP 10
#define PADDINGBOTTOM 10
// ball Radius
#define ballRadius 15.f
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

	ball.circle.setPosition(x, y);
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


// Takes references to all three components (no idea why references to pads but we might need it) and reverses velocity in the x direction
// if colliding with either of the pads
void isColliding(BALL& ball, RectangleShape& shape)
{
	//Collison with an object
	// From right  |<
	if (
		ball.circle.getPosition().x - ballRadius < shape.getPosition().x + shape.getSize().x / 2
		&&
		ball.circle.getPosition().x - ballRadius > shape.getPosition().x
		&&
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		)
	{
		ball.circle.setPosition(shape.getPosition().x + ballRadius + shape.getSize().x / 2 + 0.1f, ball.circle.getPosition().y);
		ball.xVelocity *= -1;
	}


	// From left >|
	if (
		ball.circle.getPosition().x + ballRadius > shape.getPosition().x - shape.getSize().x / 2
		&&
		ball.circle.getPosition().x + ballRadius < shape.getPosition().x
		&&
		ball.circle.getPosition().y + ballRadius >= shape.getPosition().y - shape.getSize().y / 2
		&&
		ball.circle.getPosition().y - ballRadius <= shape.getPosition().y + shape.getSize().y / 2
		)
	{

		ball.circle.setPosition(shape.getPosition().x - ballRadius - shape.getSize().x / 2 - 0.1f, ball.circle.getPosition().y);
		ball.xVelocity *= -1;
	}



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