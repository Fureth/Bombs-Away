#include "Powerup.h"
#include "Game.h"

Powerup::Powerup(int powerupType)
{
	TheTextureManager::Instance()->load("../Assets/textures/items.png", "items", TheGame::Instance()->getRenderer());
	
	this->currentHealth = powerupType;
	
	glm::vec2 size = glm::vec2(64, 64);
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(POWERUP);
}

Powerup::~Powerup()
{
}

void Powerup::draw()
{
	if (!getCollected())
	{
		TheTextureManager::Instance()->drawFrame("items", getPosition().x, getPosition().y, 64, 64, this->currentHealth + 1, 0, TheGame::Instance()->getRenderer());
	}
}

void Powerup::update()
{
	if (getCollected())
	{
		switch (currentHealth)
		{
		case 0: // Health
			TheGame::Instance()->getPlayerObject()->changeHealth(true);
			break;
		case 1: // Key
			// Add some way to trigger door, maybe a boolean flag within class?
			break;
		default:
			break;
		}
	}
}

void Powerup::clean()
{
}

bool Powerup::getCollected()
{
	return isCollected;
}

void Powerup::setCollected()
{
	isCollected = true;
}
