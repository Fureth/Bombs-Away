#include "Game.h"
#include "Wall.h"

Wall::Wall()
{
    TheTextureManager::Instance()->load("../Assets/textures/wall.png", "wall", TheGame::Instance()->getRenderer());

    glm::vec2 size = TheTextureManager::Instance()->getTextureSize("wall");
    setWidth(size.x);
    setHeight(size.y);
    setIsColliding(false);
    setType(GameObjectType::WALL);
}

Wall::Wall(int xPos, int yPos)
{
	TheTextureManager::Instance()->load("../Assets/textures/wall.png", "wall", TheGame::Instance()->getRenderer());

	this->xPos = xPos;
	this->yPos = yPos;
	
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("wall");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::WALL);
}

Wall::~Wall()
{
}

void Wall::draw()
{
	if (!isDestroyed)
	{
		TheTextureManager::Instance()->draw("wall", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), false);
	}
}

void Wall::update()
{
	if (getIsColliding())
	{
		setIsColliding(false);
		setDestruction(true);
	}
}

void Wall::clean()
{
}

void Wall::setDestruction(bool status)
{
	isDestroyed = status;
}

bool Wall::getDestruction()
{
	return isDestroyed;
}

int Wall::getX()
{
	return xPos;
}

int Wall::getY()
{
	return yPos;
}
