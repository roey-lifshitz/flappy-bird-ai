#include "Pipe.h"

Pipe::Pipe(sf::Texture texture)
{
	this->x = WIDTH;
	this->width = PIPE_WIDTH * W_MULTIPLIER;
	this->height = PIPE_HEIGHT * H_MULTIPLIER;

	// load texture from argument
	this->texture = texture;
	this->shift();
}

void Pipe::shift()
{

	// flip top pipe
	this->top.setScale(W_MULTIPLIER, -H_MULTIPLIER);
	this->bottom.setScale(W_MULTIPLIER, H_MULTIPLIER);

	// the pipes will be drawn with a hole automatically because of the image size
	// to create "holes" in random location we can shift the position of each pipe
	int range = (BACKGROUND_HEIGHT - GROUND_HEIGHT) / 2 - PIPE_MINIMUM_HEIGHT;
	range = range * H_MULTIPLIER;
	range = range * 2;
	int shift = rand() % range - range / 2;

	// set position to the right
	// when we flipped up we also changes it origin to the bottom of the flipped image
	this->top.setPosition(WIDTH, this->height + shift);
	this->bottom.setPosition(WIDTH, HEIGHT - GROUND_HEIGHT * H_MULTIPLIER - this->height + shift);
}

void Pipe::move(float speed)
{
	this->x += speed;
	this->top.move(speed, 0);
	this->bottom.move(speed, 0);
}

sf::FloatRect Pipe::getHole()
{
	// top origin is the left, bottom
	// bottom orighin is left, top
	sf::Vector2f size = sf::Vector2f(this->width, this->bottom.getPosition().y - this->top.getPosition().y);
	sf::FloatRect rect = sf::FloatRect(this->top.getPosition(), size);
	return rect;
}

void Pipe::draw(sf::RenderWindow& window)
{
	this->top.setTexture(this->texture);
	this->bottom.setTexture(this->texture);
	window.draw(this->top);
	window.draw(this->bottom);
}
