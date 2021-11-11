#pragma once
#include "Globals.h"
#include "PipeHandler.h"
#include "Bird.h"

class GameManager
{
public:
	GameManager();

	//-----------------------------------------------------------------------------
	// loadTextures()
	// ---------
	//
	// General : Loads all sfml texture and prepares background, foreground
	// and text objects
	//
	// 
	// Parameters :
	// Nonde
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void loadTextures();

	//-----------------------------------------------------------------------------
	// isRunning()
	// ---------
	//
	// General : Checks if window is still running
	// and text objects
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : bool - if running
	//
	//-----------------------------------------------------------------------------
	bool isRunning();

	//-----------------------------------------------------------------------------
	// start()
	// ---------
	//
	// General : Calls the loadTexture function, and constructs the pipe handler and first
	// bird generation
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void start();

	//-----------------------------------------------------------------------------
	// handleEvents()
	// ---------
	//
	// General : Handles all SFML related events such as
	// user inputs and closing of the screen
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void handleEvents();

	//-----------------------------------------------------------------------------
	// clearScreen()
	// ---------
	//
	// General : Clears the window and redraws the background
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void clearScreen();

	//-----------------------------------------------------------------------------
	// drawScreen()
	// ---------
	//
	// General : Draws all game objects and text on screen
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void drawScreen();

	//-----------------------------------------------------------------------------
	// drawScreen()
	// ---------
	//
	// General : Returns the amount of birds alive in current genaration
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : int
	//
	//-----------------------------------------------------------------------------
	int birdsLeft();

	//-----------------------------------------------------------------------------
	// saveBestWeight()
	// ---------
	//
	// General : Saves the best weight of current genration, and the best weight of all genrations
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void saveBestWeight();

	//-----------------------------------------------------------------------------
	// runNewGen()
	// ---------
	//
	// General : Runs a new Generation of birds
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void runNewGen();

	//-----------------------------------------------------------------------------
	// mutate()
	// ---------
	//
	// General : Mutates current genration weights for next generation
	// half the birds are mutations of the best bird of current generation
	// other half are mutations of all time best bird incase there is a unexpected
	// problem with current generation
	//
	// 
	// Parameters :
	// None
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void mutate();

	//-----------------------------------------------------------------------------
	// update()
	// ---------
	//
	// General : Updates a frame of the game loop
	// this is the "heart" of the game-> handles movements, collsions, ai...
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
	// saveWeightToFile()
	// ---------
	//
	// General : Saves a given weightMap into a .dat file 
	// this function is unsafe, only save to files you trust
	// 
	// Parameters :
	// string filename(in)
	// vector<double> weightMap(in)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void saveWeightToFile(string fileName, vector<double>& weightMap);

	//-----------------------------------------------------------------------------
	// loadWeightToFile()
	// ---------
	//
	// General : loads a given weightMap from a .dat file
	// this function is unsafe, only load files you trust
	// 
	// Parameters :
	// string filename(in)
	//
	// Return Value : None
	//
	//-----------------------------------------------------------------------------
	void loadWeightfromFile(string fileName);

private:
	// Sprites for constants
	sf::Texture backgroundTexture;
	sf::Texture baseTexture;
	sf::Texture birdTexture;
	sf::Texture pipeTexture;

	sf::Sprite background;
	sf::Sprite base;

	int distOfBestWeights;
	vector<double> bestWeights;
	vector<double> allTimeBestWeights;

	// SFML objects
	sf::RenderWindow *window;

	float elapsedTime;
	int amountLeft;
	int nGenaration;
	int score;
	int bestScore;
	bool updateScore;

	Bird birds[BIRD_GEN_SIZE];
	PipeHandler pipeHandler;

	// text
	sf::Font font;
	sf::Text scoreText;
	sf::Text aiDataText;

};

