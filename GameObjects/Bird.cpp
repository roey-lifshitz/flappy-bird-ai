#include "Bird.h"

Bird::Bird(sf::Texture& texture, float x, float y)
{
	this->x = x;
	this->y = y;
	this->width = BIRD_WIDTH * W_MULTIPLIER;
	this->height = BIRD_HEIGHT * H_MULTIPLIER;

	// bird only moves on y axis so velocity is one-dimensional
	this->velocity = 0;
	this->jumpDuration = 0;
	this->distance = 0;

	// create sprite from texture
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x, y);
	this->sprite.setScale(W_MULTIPLIER, H_MULTIPLIER);
	
	// initialize AI for bird
	this->brain = NeuralNetwork();
	this->brain.init();
}

sf::FloatRect Bird::getRect()
{
	return sf::FloatRect(this->x, this->y, this->width, this->height);
}

float Bird::getDistance()
{
	return this->distance;
}

void Bird::jump()
{
	// bird will jump in update function if jumpDuration is bigger than 0
	// that means that jumpDuration is the amount of frames bird will jump
	if (this->jumpDuration == 0)
		this->jumpDuration = JUMP_DURATION;
}

bool Bird::hit(sf::FloatRect holeRect)
{
	sf::Vector2f pos = this->sprite.getPosition();

	// hit floor or ceiling
	if (pos.y <= 0 || pos.y + this->height >= HEIGHT - GROUND_HEIGHT * H_MULTIPLIER) return true;

	// instead of checking if it hits the pipe, we check if it passed through the hole
	// if bird is between hole on the x axis
	if (pos.x < holeRect.left + holeRect.width &&
		pos.x + this->width > holeRect.left)
	{
		// if bird touches one of pipes
		if (pos.y <= holeRect.top || pos.y + this->height >= holeRect.top + holeRect.height)
			return true;
	}
	return false;
}

void Bird::update(float dt)
{
	if (this->jumpDuration > 0)
	{
		// handle jump movement
		this->velocity = -JUMP_FORCE * dt * FPS;
		this->y += velocity * dt * FPS;
		this->jumpDuration--;
		this->sprite.setRotation(JUMP_ROTATION_ANGLE);
	}
	else
	{
		// handle falling movement
		this->applyGravity(dt);
		this->sprite.setRotation(this->sprite.getRotation() + ROTATE_ANGLE);
	}

	// update sprite position
	this->distance += FPS * dt * PIPE_MOVEMENT_SPEED;
	this->sprite.setPosition(this->x, this->y);
}

void Bird::reset(float x, float y)
{
	this->x = x;
	this->y = y;
	this->sprite.setPosition(x, y);
	this->sprite.setRotation(360);
	this->distance = 0;
}

void Bird::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Bird::useBrain(sf::FloatRect holeRect)
{
	// data for inputLayer in NeuralNetwork
	double x_dist_from_hole = ((double)holeRect.left + holeRect.width) - (double)this->x;
	double y_dist_from_top = holeRect.top - (double)this->y;
	double y_dist_from_bottom = ((double)this->y + this->height) - ((double)holeRect.top + holeRect.height);
	double bird_height = this->height;
	double speed = PIPE_MOVEMENT_SPEED;
	double data[5] =
	{
		x_dist_from_hole, y_dist_from_top, y_dist_from_bottom, bird_height, speed
	};

	int toJump = this->brain.calculate(data);
	if (toJump) this->jump();
}

void Bird::applyGravity(float dt)
{
	// limit velocity
	if (this->velocity <= VELOCITY_CAP * dt * FPS)
	{
		this->velocity += GRAVITY_FORCE * dt * FPS;
	}

	this->y += this->velocity * dt * FPS;
}