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

// Health indicates wall types: 0 = door, 1 = unbreakable, 2 = breakable
Wall::Wall(int xPos, int yPos, int wallType)
{
	TheTextureManager::Instance()->load("../Assets/textures/wallsanddoor.png", "wallsanddoor", TheGame::Instance()->getRenderer());

	this->xPos = xPos;
	this->yPos = yPos;
	this->currentHealth = wallType;
	
	glm::vec2 size = glm::vec2(64, 64);
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
		TheTextureManager::Instance()->drawFrame("wallsanddoor", getPosition().x, getPosition().y, 64, 64, this->currentHealth + 1, 0, TheGame::Instance()->getRenderer());
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
