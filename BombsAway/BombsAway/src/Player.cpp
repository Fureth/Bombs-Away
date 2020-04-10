#include "Player.h"
#include "Game.h"

Player::Player(int p)
{
	playertype = p;
	if (playertype == 1)
		TheTextureManager::Instance()->load("../Assets/textures/p1fw.png", "player", TheGame::Instance()->getRenderer());
	if (playertype == 2)
		TheTextureManager::Instance()->load("../Assets/textures/p2fw.png", "player2", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(0, 0));
	setVelocity(glm::vec2(m_iPlayerSpeed, m_iPlayerSpeed));


	glm::vec2 size = glm::vec2(64, 64);
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);
	currentHealth = 3;
}

Player::~Player()
{
}

void Player::draw()
{
	if (getIsActive())
	{

		if (!isInvul || invFrame % 60 > 10 && playertype == 2)
		{
			int frameSelector = walkTimer / 10;
			switch (frameSelector)
			{
			case 0:
				TheTextureManager::Instance()->drawFrame("player", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
				break;
			case 1:
				TheTextureManager::Instance()->drawFrame("player", getPosition().x, getPosition().y, 64, 64, 1, 1, TheGame::Instance()->getRenderer());
				break;
			case 2:
				TheTextureManager::Instance()->drawFrame("player", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
				break;
			case 3:
				TheTextureManager::Instance()->drawFrame("player", getPosition().x, getPosition().y, 64, 64, 2, 1, TheGame::Instance()->getRenderer());
				break;
			case 4:
				TheTextureManager::Instance()->drawFrame("player", getPosition().x, getPosition().y, 64, 64, 3, 0, TheGame::Instance()->getRenderer());
				break;
			default:
				break;
			}
		}
	}
}

void Player::draw2()
{
	if (getIsActive())
	{

		if (!isInvul || invFrame % 60 > 10 && playertype == 2)
		{
			int frameSelector = walkTimer / 10;
			switch (frameSelector)
			{
			case 0:
				TheTextureManager::Instance()->drawFrame("player2", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
				break;
			case 1:
				TheTextureManager::Instance()->drawFrame("player2", getPosition().x, getPosition().y, 64, 64, 1, 1, TheGame::Instance()->getRenderer());
				break;
			case 2:
				TheTextureManager::Instance()->drawFrame("player2", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
				break;
			case 3:
				TheTextureManager::Instance()->drawFrame("player2", getPosition().x, getPosition().y, 64, 64, 2, 1, TheGame::Instance()->getRenderer());
				break;
			case 4:
				TheTextureManager::Instance()->drawFrame("player2", getPosition().x, getPosition().y, 64, 64, 3, 0, TheGame::Instance()->getRenderer());
				break;
			default:
				break;
			}
		}
	}
}

void Player::update()
{
	if (getIsActive())
	{
		// Set pre-movement position to its previous position
		setPreviousPosition(getPosition());
		// Check if a movement key is pressed, also includes boundary checks
		// y-movement
		if (playertype == 1 && playertype != 2)
		{
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_W))
			{
				playerFacing = NORTH;
				TheTextureManager::Instance()->load("../Assets/textures/p1bw.png", "player", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x, getPosition().y - getVelocity().y));
				if (getPosition().y <= 210) // Top of screen
				{
					setPosition(glm::vec2(getPosition().x, 210));
				}
			}
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_S))
			{
				playerFacing = SOUTH;
				TheTextureManager::Instance()->load("../Assets/textures/p1fw.png", "player", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x, getPosition().y + getVelocity().y));
				if (getPosition().y >= (978 - getHeight())) // Bottom of screen minus player height
				{
					setPosition(glm::vec2(getPosition().x, (978 - getHeight())));
				}
			}
			// x-movement
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_A))
			{
				playerFacing = WEST;
				TheTextureManager::Instance()->load("../Assets/textures/p1lw.png", "player", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x - getVelocity().x, getPosition().y));
				if (getPosition().x <= 0) // Left side of screen
				{
					setPosition(glm::vec2(0, getPosition().y));
				}
			}
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_D))
			{
				playerFacing = EAST;
				TheTextureManager::Instance()->load("../Assets/textures/p1rw.png", "player", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y));
				if (getPosition().x >= (1280 - getWidth())) // Right side of screen minus player width
				{
					setPosition(glm::vec2((1280 - getWidth()), getPosition().y));
				}
			}
		}
		if (playertype == 2 && playertype != 1)
		{
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_I))
			{
				playerFacing = NORTH;
				TheTextureManager::Instance()->load("../Assets/textures/p2bw.png", "player2", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x, getPosition().y - getVelocity().y));
				if (getPosition().y <= 210) // Top of screen
				{
					setPosition(glm::vec2(getPosition().x, 210));
				}
			}
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_K))
			{
				playerFacing = SOUTH;
				TheTextureManager::Instance()->load("../Assets/textures/p2fw.png", "player2", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x, getPosition().y + getVelocity().y));
				if (getPosition().y >= (978 - getHeight())) // Bottom of screen minus player height
				{
					setPosition(glm::vec2(getPosition().x, (978 - getHeight())));
				}
			}
			// x-movement
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_J))
			{
				playerFacing = WEST;
				TheTextureManager::Instance()->load("../Assets/textures/p2lw.png", "player2", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x - getVelocity().x, getPosition().y));
				if (getPosition().x <= 0) // Left side of screen
				{
					setPosition(glm::vec2(0, getPosition().y));
				}
			}
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_L))
			{
				playerFacing = EAST;
				TheTextureManager::Instance()->load("../Assets/textures/p2rw.png", "player2", TheGame::Instance()->getRenderer());
				setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y));
				if (getPosition().x >= (1280 - getWidth())) // Right side of screen minus player width
				{
					setPosition(glm::vec2((1280 - getWidth()), getPosition().y));
				}
			}
		}
		// Check if key to lay bomb is pressed
		if (playertype == 1)
		{
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_SPACE))
			{
				spaceDown = true;
				if (throwableBomb)
				{
					throwTimer++;
					if (throwTimer == throwTimerMax)
					{
						if (TheGame::Instance()->getBombObject() != nullptr)
						{
							if (!TheGame::Instance()->getBombObject()->getBomb())
							{
								TheGame::Instance()->getBombObject()->setPosition(this->getPosition());
								TheGame::Instance()->getBombObject()->setToss(true);
								switch (playerFacing)
								{
								case NORTH:
									TheGame::Instance()->getBombObject()->setThrownFrom(NORTH);
									break;
								case SOUTH:
									TheGame::Instance()->getBombObject()->setThrownFrom(SOUTH);
									break;
								case WEST:
									TheGame::Instance()->getBombObject()->setThrownFrom(WEST);
									break;
								case EAST:
									TheGame::Instance()->getBombObject()->setThrownFrom(EAST);
									break;
								}
								TheGame::Instance()->getBombObject()->setBomb(true);
							}
						}
					}
				}
			}
		}
		if (playertype == 2)
		{
			if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_RSHIFT))
			{
				spaceDown = true;
				if (throwableBomb)
				{
					throwTimer++;
					if (throwTimer == throwTimerMax)
					{
						if (TheGame::Instance()->getBombObject() != nullptr)
						{
							if (!TheGame::Instance()->getBombObject()->getBomb())
							{
								TheGame::Instance()->getBombObject()->setPosition(this->getPosition());
								TheGame::Instance()->getBombObject()->setToss(true);
								switch (playerFacing)
								{
								case NORTH:
									TheGame::Instance()->getBombObject()->setThrownFrom(NORTH);
									break;
								case SOUTH:
									TheGame::Instance()->getBombObject()->setThrownFrom(SOUTH);
									break;
								case WEST:
									TheGame::Instance()->getBombObject()->setThrownFrom(WEST);
									break;
								case EAST:
									TheGame::Instance()->getBombObject()->setThrownFrom(EAST);
									break;
								}
								TheGame::Instance()->getBombObject()->setBomb(true);
							}
						}
					}
				}
			}
		}
		if (playertype == 1)
		{
			if (!TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_SPACE) && spaceDown)
			{
				if (TheGame::Instance()->getBombObject() != nullptr)
				{
					if (!TheGame::Instance()->getBombObject()->getBomb() && throwTimer < throwTimerMax) // If no bomb set and bomb has not been thrown
					{
						TheGame::Instance()->getBombObject()->setPosition(this->getPosition());
						TheGame::Instance()->getBombObject()->setBomb(true);
					}
				}

				throwTimer = 0;
				spaceDown = false;
			}
		}
		if (playertype == 2)
		{
			if (!TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_RSHIFT) && spaceDown)
			{
				if (TheGame::Instance()->getBombObject() != nullptr)
				{
					if (!TheGame::Instance()->getBombObject()->getBomb() && throwTimer < throwTimerMax) // If no bomb set and bomb has not been thrown
					{
						TheGame::Instance()->getBombObject()->setPosition(this->getPosition());
						TheGame::Instance()->getBombObject()->setBomb(true);
					}
				}

				throwTimer = 0;
				spaceDown = false;
			}
		}
		// Check I-Frames
		if (isInvul)
		{
			if (invFrame < invFrameMax)
			{
				invFrame++;
			}
			else if (invFrame >= invFrameMax)
			{
				isInvul = false;
				invFrame = 0;
			}
		}

		if (walkTimer < walkTimerMax)
		{
			walkTimer++;
		}
		else
		{
			walkTimer = 0;
		}

		// Check HP
		if (currentHealth == 0)
		{
			TheSoundManager::Instance()->load("../Assets/audios/8bit_bomb_explosion.wav", "playerdeath", sound_type::SOUND_SFX);
			TheSoundManager::Instance()->playSound("playerdeath", 0);
			setIsActive(false);
		}
	}
}

void Player::clean()
{
}

bool Player::getRequest()
{
	return requestBomb;
}

void Player::setRequest(bool request)
{
	requestBomb = request;
}

bool Player::getThrow()
{
	return throwableBomb;
}

void Player::setThrow(bool enable)
{
	throwableBomb = enable;
}

int Player::getHealth()
{
	return currentHealth;
}

void Player::changeHealth(bool lifeUp)
{
	if (lifeUp && currentHealth < 3)
	{
		currentHealth++;
	}
	else if (!lifeUp && currentHealth != 0)
	{
		currentHealth--;
	}
}

void Player::setKey(bool key)
{
	if (!getKey())
	{
		keyObtained = key;
	}
	else
	{
		secondKey = key;
	}
}

bool Player::getKey()
{
	return keyObtained;
}

bool Player::getKeyTwo()
{
	return secondKey;
}

void Player::setSpawn(bool spawned)
{
	beenSpawned = spawned;
}

bool Player::getSpawn()
{
	return beenSpawned;
}

void Player::setKeyEnemy(bool kill)
{
	keyEnemyKilled = kill;
}

bool Player::getKeyEnemy()
{
	return keyEnemyKilled;
}
