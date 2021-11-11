#include "GameManager.h"
#include <stdlib.h>

GameManager::GameManager()
{
	// create window
	this->window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "FlappyBird");
	this->window->setFramerateLimit(FPS);

	this->amountLeft = BIRD_GEN_SIZE;
	this->distOfBestWeights = 0;
	this->elapsedTime = 0;
	this->score = 0;
	this->bestScore = 0;
	this->updateScore = true;
	this->nGenaration = 0;
	srand((unsigned) time(NULL));
	
}

void GameManager::loadTextures()
{
	// load all files from assets folder
	if (!this->backgroundTexture.loadFromFile("Assets/background-day.png") ||
		!this->baseTexture.loadFromFile("Assets/base.png") ||
		!this->birdTexture.loadFromFile("Assets/yellowbird-midflap.png") ||
		!this->pipeTexture.loadFromFile("Assets/pipe-green.png") ||	
		!this->font.loadFromFile("Assets/Comfortaa-Bold.ttf")) {
		std::cout << "Could not load texture" << std::endl;
	}
	// create background and foreground sprite
	this->background.setTexture(this->backgroundTexture);
	this->background.scale(W_MULTIPLIER, H_MULTIPLIER);
	this->base.setTexture(this->baseTexture);
	this->base.scale(W_MULTIPLIER, H_MULTIPLIER);
	this->base.setPosition(0, (HEIGHT - GROUND_HEIGHT * H_MULTIPLIER));

	// update text objects
	this->scoreText.setFont(this->font);
	this->scoreText.setScale(W_MULTIPLIER, H_MULTIPLIER);
	this->scoreText.setPosition(WIDTH / 2 - 16, HEIGHT - HEIGHT / 10);
	this->scoreText.setCharacterSize(24);

	this->aiDataText.setFont(this->font);
	this->aiDataText.setScale(W_MULTIPLIER, H_MULTIPLIER);
	this->aiDataText.setCharacterSize(10);
}

void GameManager::start()
{
	// load textures of gameObjects
	this->loadTextures();
	// initiallize birds
	for (int i = 0; i < BIRD_GEN_SIZE; i++)
	{
		this->birds[i] = Bird(this->birdTexture, 100, 100);
	}
	// initiallize pipe
	this->pipeHandler = PipeHandler(this->pipeTexture);
	pipeHandler.addPipe();
}

void GameManager::update(float dt)
{
	this->handleEvents();

	// handle time related events
	this->elapsedTime += dt;
	if (this->elapsedTime >= PIPE_GENERATION_COOLDOWN)
	{
		pipeHandler.addPipe();
		this->elapsedTime = 0;
	}

	// handle position related events
	sf::FloatRect nextPipeRect = pipeHandler.getNext();
	// loop through birds
	for (int i = 0; i < this->amountLeft; i++)
	{
		if (this->birds[i].hit(nextPipeRect))
		{
			// puts the bird in last position of alived birds in current index then subtracts one from amount of living birds
			this->birds[i] = this->birds[this->amountLeft - 1];
			this->amountLeft--;
		}
	}
	// all birds are on the same position on x axis, so this->birds[0] represnets all birds when doing calculation on x axis
	sf::FloatRect birdRect = this->birds[0].getRect();
	// if right of bird passed left of next pipe (do inside if loop once until next pipe is updated)
	if (birdRect.left + birdRect.width > nextPipeRect.left && this->updateScore)
	{
		this->score++;
		this->updateScore = false;
	}
	// if left of bird passed right of next pipe
	if (nextPipeRect.left + nextPipeRect.width < birdRect.left)
	{
		pipeHandler.updateNext();
		this->updateScore = true;
	}

	// handle movements
	pipeHandler.moveAll(dt);
	for (int i = 0; i < this->amountLeft; i++)
	{
		this->birds[i].update(dt);
		// useBrain decides if bird will jump or not according to given data using a neuralNetwork
		this->birds[i].useBrain(nextPipeRect);
	}

	// handle text
	this->scoreText.setString(to_string(score));
	string s = "Generation Number: " + to_string(this->nGenaration) + "\nBirds Per Generation: " + to_string(BIRD_GEN_SIZE) + "\nBest Score: " + to_string(this->bestScore);
	this->aiDataText.setString(s);
}

bool GameManager::isRunning()
{
	return this->window->isOpen();
}

void GameManager::handleEvents()
{
	// Process events
	sf::Event event;
	// loop through all SFML events
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				printf("Saving best weight of last generation to a file named: weights.dat\n");
				this->saveWeightToFile(string("weights.dat"), this->bestWeights);
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				printf("Loading weight from file weights.dat\n");
				this->loadWeightfromFile(string("weights.dat"));
			}
		}
	}
}


void GameManager::drawScreen()
{
	// draws only alive birds
	for (int i = 1; i < this->amountLeft; i++)
	{
		this->birds[i].draw(*this->window);
	}
	this->birds[0].draw(*this->window);

	this->pipeHandler.drawAll(*this->window);
	this->window->draw(this->base);
	this->window->draw(this->aiDataText);
	this->window->draw(this->scoreText);

	window->display();
}


void GameManager::clearScreen()
{
	this->window->clear();
	this->window->draw(this->background);
}


int GameManager::birdsLeft()
{
	return this->amountLeft;
}

void GameManager::saveBestWeight()
{
	// save in allTimeBestWeights the weightMap of bird that passed the most distance
	if (this->birds[0].getDistance() > this->distOfBestWeights)
		this->allTimeBestWeights = this->birds[0].brain.getWeight();
	this->bestWeights = this->birds[0].brain.getWeight();
}

void GameManager::runNewGen()
{
	this->pipeHandler.restart();
	this->amountLeft = BIRD_GEN_SIZE;
	this->elapsedTime = 0;
	this->nGenaration++;
	for (int i = 0; i < amountLeft; i++)
	{
		this->birds[i].reset(100, WIDTH / 2);
	}
	// save best score out of all generations
	if (this->score > this->bestScore) this->bestScore = this->score;
	this->score = 0;
	this->updateScore = true;
}

void GameManager::mutate()
{
	// make half the birds in next generation mutations of the best bird in current generation
	for (int i = 0; i < BIRD_GEN_SIZE / 2; i++)
	{
		this->birds[i].brain.mutate(this->bestWeights, MUTATION_PERCENT);
	}
	// make other half mutations of the best bird in all generation
	for (int i = BIRD_GEN_SIZE / 2; i < BIRD_GEN_SIZE; i++)
	{
		this->birds[i].brain.mutate(this->allTimeBestWeights, MUTATION_PERCENT);
	}
}

void GameManager::saveWeightToFile(string filename, vector<double>& weightMap)
{
	// open binray file for writing
	FILE* fp = fopen(filename.data(), "wb");
	int size = weightMap.size();
	// loop through weightMap
	for (int i = 0; i < size; i++)
	{
		// write to file
		fwrite(&weightMap[i], sizeof(double), 1, fp);
	}
	fclose(fp);
}

void GameManager::loadWeightfromFile(string filename)
{
	this->distOfBestWeights = 0;
	this->nGenaration = 0;
	// open binary file to read
	FILE* fp = fopen(filename.data(), "rb");
	int size = this->bestWeights.size();
	// loop through weightMap
	for (int i = 0; i < size; i++)
	{
		// read form file
		double tmp;
		fread(&tmp, sizeof(double), 1, fp);
		this->bestWeights[i] = tmp;
		this->allTimeBestWeights[i] = tmp;
	}

	// create a new generation
	this->mutate();
	this->runNewGen();
	fclose(fp);
}