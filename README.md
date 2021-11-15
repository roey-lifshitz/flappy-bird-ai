# flappy-bird-ai
Flappy bird AI with SFML in C++/C

Introduction:
======== 

This Project is my first attempt of creating an AI using a Neural Network. The purpose of the project is to begin studying Machine Learning.
Although it is slower, the Network was created with Vectors instead of Matrixes to simplify the ideas and maths behind it.
Currently, all hidden layers need to have the same amount of neurons. 

How Does the AI Learn?:
========
A generation of birds is created with random weights at the start of the game.
Every time a generation dies, the game "mutates" the weights of the best in generation by a given percent.
That means that every generation is an evolution of the generation beforehand.
Theoretically, each evolution could ruin the birds progress. To bypass this problem, every generation also consits of
mutations of the best bird in all generations.


https://user-images.githubusercontent.com/45150099/141296960-237669bd-8c4c-49bf-8d64-68d73f804e6c.mov

