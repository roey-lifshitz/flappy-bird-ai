#include "PipeHandler.h"

PipeHandler::PipeHandler(sf::Texture &texture)
{
	this->speed = -PIPE_MOVEMENT_SPEED;
	this->texture = texture;
}

void PipeHandler::moveAll(float dt)
{
	for (auto it = this->next.begin(); it != this->next.end(); ++it) {
		it->move(this->speed * dt * FPS);
	}
	for (auto it = this->passed.begin(); it != this->passed.end(); ++it) {
		it->move(this->speed * dt * FPS);
	}
}

void PipeHandler::addPipe()
{
	Pipe pipe = Pipe(this->texture);
	pipe.shift();
	this->next.push_back(pipe);
}


void PipeHandler::removePipe()
{
	sf::FloatRect holeRect = this->passed.front().getHole();
	int rightOfPipe = holeRect.left + holeRect.width;
	if (rightOfPipe < 0)
	{
		this->passed.pop_front();
	}
}

sf::FloatRect PipeHandler::getNext()
{
	return this->next.begin()->getHole();
}

void PipeHandler::updateNext()
{
	if (this->next.empty()) return;
	this->passed.push_back(this->next.front());
	this->next.pop_front();
}

void PipeHandler::drawAll(sf::RenderWindow &window)
{
	for (auto it = this->next.begin(); it != this->next.end(); ++it) {
		it->draw(window);
	}
	for (auto it = this->passed.begin(); it != this->passed.end(); ++it) {
		it->draw(window);
	}
}

void PipeHandler::restart()
{
	this->passed.resize(0);
	this->next.resize(0);
	this->addPipe();
}

