#pragma once
#include "Globals.h"
#include "NeuralNetwork.h"

class Bird
{
public:
	Bird() {};
	Bird(sf::Texture& texture, float x, float y);

	//-----------------------------------------------------------------------------
	// GetRect()
	// ---------
	//
	// General : Gets a rectangle representing the sprite
	// 
	//
	// Parameters :
	// None
	//
	// Return Value : sf::Float(x, y, width, height)
	//
	//-----------------------------------------------------------------------------
	sf::FloatRect getRect();

	//-----------------------------------------------------------------------------
	// GetDistance()
	// ---------
	//
	// General : Gets the distance the bird passed
	//
	// Parameters :
	// None
	//
	// Return Value : float
	//
	//-----------------------------------------------------------------------------
	float getDistance();

	//-----------------------------------------------------------------------------
	// jump()
	// ---------
	//
	// General : Updates birds jumpDuration so it could jump in the update function
	//
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void jump();

	//-----------------------------------------------------------------------------
	// hit()
	// ---------
	//
	// General : Checks collision of sprite with Pipes and screen boundaries
	//
	// Parameters :
	// sf::FloatRect holeRect(in)- The hole between next pipe
	//
	// Return Value : if bird hits collided or not
	//
	//-----------------------------------------------------------------------------
	bool hit(sf::FloatRect holeRect);

	//-----------------------------------------------------------------------------
	// update()
	// ---------
	//
	// General : handles the bird movement 
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void update(float dt);

	//-----------------------------------------------------------------------------
	// reset()
	// ---------
	//
	// General : resets bird to a starting position
	//
	// 
	// Parameters :
	// float x(in) - x position
	// float y(in) - y position
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void reset(float x, float y);

	//-----------------------------------------------------------------------------
	// draw()
	// ---------
	//
	// General : Draws sprite on given window
	//
	// 
	// Parameters :
	// sf::RenderWindow &window(in)- refrence to window
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void draw(sf::RenderWindow &window);

	//-----------------------------------------------------------------------------
	// useBrain()
	// ---------
	//
	// General : Updates the inputLayer in the birds NeuralNetwork(brain)
	//  according the given rect
	//
	// 
	// Parameters :
	// sf::FloatRect holeRect- the rect of hole bird needs to pass
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void useBrain(sf::FloatRect holeRect);

	NeuralNetwork brain;
	
private:
	
	// sprite rect variables
	float x; 
	float y;
	int width;
	int height;

	// bird only moves on y axis so velocity is one-dimensional
	float velocity;

	// counter for amount of frame bird jumped
	int jumpDuration;

	float distance;

	sf::Sprite sprite;

	// private function, applies gravity on the bird
	void applyGravity(float dt);	
};

