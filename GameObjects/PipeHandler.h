#pragma once
#include "Globals.h"
#include "Pipe.h"

class PipeHandler
{
public:
	// Constructor function
	PipeHandler() {};
	PipeHandler(sf::Texture &texture);

	//-----------------------------------------------------------------------------
	// moveAll()
	// ---------
	//
	// General : Move all Pipes created by this class
	//
	// 
	// Parameters :
	// float dt- deltaTime
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void moveAll(float dt);
	
	//-----------------------------------------------------------------------------
	// addPipe()
	// ---------
	//
	// General : Creates a new set of Pipes at the right of the window
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void addPipe();

	//-----------------------------------------------------------------------------
	// removePipe()
	// ---------
	//
	// General : Removes the last pipe from passed list (front of list) 
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void removePipe();

	//-----------------------------------------------------------------------------
	// getNext()
	// ---------
	//
	// General : Gets the rect representing the hole of the next pipe to be passed 
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : sf::floatRect(x, y, width, height)
	//-----------------------------------------------------------------------------
	sf::FloatRect getNext();

	//-----------------------------------------------------------------------------
	// updateNext()
	// ---------
	//
	// General : This function updates the next pipe the birds are about to pass
	// to save the next pipe we have two lists. one for next pipes and
	// other for passed pipes. When a birds passed a pipe, it pushes to passed pipes list
	// the front of next pipes list and removes the front from next pipes list.
	// thats how the next pipe about to be passed is always the front of next pipes list
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void updateNext();

	//-----------------------------------------------------------------------------
	// restart()
	// ---------
	//
	// General : Removes all Pipes, and starts creating new ones
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void restart();

	//-----------------------------------------------------------------------------
	// drawAll()
	// ---------
	//
	// General : Draws all pipes from both lists on screen
	//
	// 
	// Parameters :
	// sf::RenderWindow& window
	//
	// Return Value : None
	//-----------------------------------------------------------------------------
	void drawAll(sf::RenderWindow &window);
private:
	float speed;
	sf::Texture texture;
	// Pipes bird is about to pass
	std::list<Pipe> next;
	// Pipes bird has passed
	std::list<Pipe> passed;
};

