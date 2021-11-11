#pragma once
#include "Globals.h"

class Pipe
{
public:

	Pipe() {};
	Pipe(sf::Texture textrue);

	//-----------------------------------------------------------------------------
	// shift()
	// ---------
	//
	// General : shifts the pipe on y axis by random number to create a hole
	// in random postions
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void shift();

	//-----------------------------------------------------------------------------
	// move()
	// ---------
	//
	// General : moves the pipe by given speed on x axis
	//
	// 
	// Parameters :
	// float speed(in)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void move(float speed);

	//-----------------------------------------------------------------------------
	// update()
	// ---------
	//
	// General : Gets the rect("hitbox") of hole between top and bottom pipe 
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : sf::FloatRect(x, y, width, height)
	//
	//-----------------------------------------------------------------------------
	sf::FloatRect getHole();

	//-----------------------------------------------------------------------------
	// draw()
	// ---------
	//
	// General : draws top and bottom sprites on given window
	//
	// 
	// Parameters :
	// sf::RenderWindow& window(in)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void draw(sf::RenderWindow& window);

private:
	float x;
	int width;
	int height;
	sf::Texture texture;
	sf::Sprite top;
	sf::Sprite bottom;
};

