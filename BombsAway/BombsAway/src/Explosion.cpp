#include "Game.h"
#include "Explosion.h"

Explosion::Explosion()
{
	TheTextureManager::Instance()->load("../Assets/textures/explosion.png", "explosion", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(0, 0));

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("explosion");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(EXPLOSION);
}

Explosion::~Explosion()
{
}

void Explosion::draw()
{
	if (getExplosion())
	{
		TheTextureManager::Instance()->draw("explosion", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), false);
	}
}

void Explosion::update()
{
	if (getExplosion())
	{
		if (explosionTimer < explosionTimerMax)
		{
			explosionTimer++;
		}
		else
		{
			explosionTimer = 0;
			setExplosion(false);
		}
	}
}

void Explosion::clean()
{
}

bool Explosion::getExplosion()
{
	return activeExplosion;
}

void Explosion::setExplosion(bool boom)
{
	activeExplosion = boom;
}
