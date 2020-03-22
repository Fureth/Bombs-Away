#include "Game.h"
#include "Bomb.h"

Bomb::Bomb()
{
    TheTextureManager::Instance()->load("../Assets/textures/bomb.png", "bomb", TheGame::Instance()->getRenderer());
    setPosition(glm::vec2(0, 0));

    glm::vec2 size = TheTextureManager::Instance()->getTextureSize("bomb");
    setWidth(size.x);
    setHeight(size.y);
    setIsColliding(false);
    setType(GameObjectType::BOMB);
}

Bomb::~Bomb()
{
}

void Bomb::draw()
{
	if (isSet)
	{
		TheTextureManager::Instance()->draw("bomb", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), false);
		//std::cout << "Bomb is set\n";
	}
}

void Bomb::update()
{
    if (getBomb())
    {
		if (getToss())
		{
			bombTossMove++;
			switch (thrownFrom)
			{
			case NORTH:
				setPosition(glm::vec2(getPosition().x, getPosition().y - 64));
				break;
			case SOUTH:
				setPosition(glm::vec2(getPosition().x, getPosition().y + 64));
				break;
			case WEST:
				setPosition(glm::vec2(getPosition().x - 64, getPosition().y));
				break;
			case EAST:
				setPosition(glm::vec2(getPosition().x + 64, getPosition().y));
				break;
			}
			if (bombTossMove >= bombTossMoveMax)
			{
				bombTossMove = 0;
				setToss(false);
			}
		}
    	
        if (bombTimer < bombTimerMax)
        {
            bombTimer++;
        }
        else
        {
            bombTimer = 0;
			// setExplode(true);
        	if (TheGame::Instance()->getExplosionObject() != nullptr)
        	{
				TheGame::Instance()->getExplosionObject()->setPosition(glm::vec2(this->getPosition().x - this->getWidth() * 0.5, this->getPosition().y - this->getHeight() * 0.5));
				TheGame::Instance()->getExplosionObject()->setExplosion(true);
        	}
            setBomb(false);
        }
    }
}

void Bomb::clean()
{
}

void Bomb::setBomb(bool set)
{
    isSet = set;
}

bool Bomb::getBomb()
{
    return isSet;
}

void Bomb::setExplode(bool expl)
{
	hasExploded = expl;
}

bool Bomb::getExplode()
{
	return hasExploded;
}

void Bomb::setToss(bool toss)
{
	beenTossed = toss;
}

bool Bomb::getToss()
{
	return beenTossed;
}

Direction Bomb::getThrownFrom()
{
	return thrownFrom;
}

void Bomb::setThrownFrom(Direction thrown)
{
	thrownFrom = thrown;
}
