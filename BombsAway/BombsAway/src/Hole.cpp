#include "Game.h"
#include "Hole.h"

Hole::Hole(int xPos, int yPos)
{
	TheTextureManager::Instance()->load("../Assets/textures/floor.png", "floor", TheGame::Instance()->getRenderer());

	this->xPos = xPos;
	this->yPos = yPos;

	glm::vec2 size = glm::vec2(64, 64);
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(HOLE);
}

Hole::~Hole()
{
}

void Hole::draw()
{
	TheTextureManager::Instance()->drawFrame("floor", getPosition().x, getPosition().y, 64, 64, 1, 1, TheGame::Instance()->getRenderer());
}

void Hole::update()
{
	
}

void Hole::clean()
{
}


int Hole::getX()
{
	return xPos;
}

int Hole::getY()
{
	return yPos;
}
