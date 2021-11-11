#pragma once
#define _CRT_SECURE_NO_WARNINGS
// SFML Libraries
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

// Addition Libraries
#include <iostream>
#include <list>
#include <time.h>


// Game Global Variables
#define WIDTH 576 
#define HEIGHT 1024 

// Image sizes
#define BACKGROUND_WIDTH 288
#define BACKGROUND_HEIGHT 512
#define GROUND_WIDTH 336
#define GROUND_HEIGHT 112
#define BIRD_WIDTH 34
#define BIRD_HEIGHT 24
#define PIPE_WIDTH 52
#define PIPE_HEIGHT 140

// constants
#define W_MULTIPLIER WIDTH / BACKGROUND_WIDTH
#define H_MULTIPLIER HEIGHT / BACKGROUND_HEIGHT
#define FPS 60

// Bird Global Constants
#define JUMP_FORCE 10
#define GRAVITY_FORCE 0.5
#define VELOCITY_CAP 10
#define JUMP_DURATION 3
#define ROTATE_ANGLE 1.1
#define JUMP_ROTATION_ANGLE 325

// Pipes Global Constants
#define PIPE_GENERATION_COOLDOWN 1.2 * (60 / FPS)
#define PIPE_MINIMUM_HEIGHT 100
#define PIPE_MOVEMENT_SPEED 5;

// NeuralNetwork Global Constants
#define BIRD_GEN_SIZE 30
#define INPUT_LAYER_SIZE 5
#define OUTPUT_LAYER_SIZE 2
#define HIDDEN_LAYER_SIZE 8
#define HIDDEN_LAYER_NUM 2
#define MUTATION_PERCENT 15

