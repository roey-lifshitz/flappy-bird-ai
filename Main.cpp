#pragma once
#include "Bird.h"
#include "PipeHandler.h"
#include "NeuralNetwork.h"
#include "GameManager.h"

int main()
{
	printf("RUNNING\n");
	GameManager gameManager = GameManager();
	sf::Clock clock;
	float elapsedTime = 0;
	gameManager.start();

	while (gameManager.isRunning())
	{
		float dt = clock.restart().asSeconds();
		elapsedTime += dt;
		gameManager.clearScreen();
		if (gameManager.birdsLeft() == 1)
		{
			gameManager.saveBestWeight();
		}
		if (gameManager.birdsLeft() == 0)
		{
			gameManager.mutate();
			gameManager.runNewGen();
		}

		gameManager.update(dt);
		gameManager.drawScreen();	
	}
	return 0;
}

