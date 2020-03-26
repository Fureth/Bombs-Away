#include "Game.h"
#include "Explosion.h"

Explosion::Explosion()
{
	TheTextureManager::Instance()->load("../Assets/textures/explosion sprite.png", "explosion", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(0, 0));

	glm::vec2 size = glm::vec2(128, 128);
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
		int frameSelector = explosionTimer / 6;
		switch (frameSelector)
		{
		case 0:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 1, 0, TheGame::Instance()->getRenderer());
			break;
		case 1:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 1, 1, TheGame::Instance()->getRenderer());
			//Bomb sound effect
			TheSoundManager::Instance()->load("../Assets/audios/8bit_bomb_explosion.wav", "explosion", sound_type::SOUND_SFX);
			TheSoundManager::Instance()->playSound("explosion", 0);
			break;
		case 2:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 1, 2, TheGame::Instance()->getRenderer());
			break;
		case 3:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 2, 0, TheGame::Instance()->getRenderer());
			break;
		case 4:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 2, 1, TheGame::Instance()->getRenderer());
			break;
		case 5:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 2, 2, TheGame::Instance()->getRenderer());
			break;
		case 6:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 3, 0, TheGame::Instance()->getRenderer());
			break;
		case 7:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 3, 1, TheGame::Instance()->getRenderer());
			break;
		case 8:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 3, 2, TheGame::Instance()->getRenderer());
			break;
		case 9:
			TheTextureManager::Instance()->drawFrame("explosion", getPosition().x, getPosition().y, 128, 128, 4, 0, TheGame::Instance()->getRenderer());
			break;
		default:
			break;
		}
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
