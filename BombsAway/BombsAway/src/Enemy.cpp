#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(glm::vec2 startPos, int enemyType)
{
	TheTextureManager::Instance()->load("../Assets/textures/enemy-idle.png", "enemy", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-back.png", "enemyUp", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-front.png", "enemyDn", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-left.png", "enemyLt", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-right.png", "enemyRt", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/boss.png", "boss", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/ghostSamurai.png", "ghost", TheGame::Instance()->getRenderer());
	
	setPosition(startPos);
	setPreviousPosition(getPosition());
	
	glm::vec2 size = glm::vec2(64, 64);
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(ENEMY);
	randomizeDirection();


	switch (enemyType)
	{
	case 1: // Snail
		currentHealth = 1;
		enemySpeed = 1;
		break;
	case 2: // Ghost Samurai
		currentHealth = 1;
		enemySpeed = 4;
		break;
	case 3: // Boss
		currentHealth = 2;
		enemySpeed = 2;
		keyEnemy = true;
		break;
	case 4: // Key Snail
		currentHealth = 1;
		enemySpeed = 1;
		keyEnemy = true;
		break;
	default:
		break;
	}

	this->enemyType = enemyType;
	setVelocity(glm::vec2(enemySpeed, enemySpeed));
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	int rowSelector = 0;
	int frameSelector = 0;
	switch (enemyType)
	{
	case 1: // Snail
		switch (getDirection())
		{
		case NORTH: // Up
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyUp", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyUp", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case SOUTH: // Down
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyDn", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyDn", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case EAST: // Right
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyRt", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyRt", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case WEST: // Left
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyLt", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyLt", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		}
		break;
	case 2: // Ghost
		frameSelector = frameTimer / 8;
		switch (getDirection())
		{
		case NORTH: // Up
			rowSelector = 1;
			break;
		case SOUTH: // Down
			rowSelector = 2;
			break;
		case EAST: // Right
			rowSelector = 4;
			break;
		case WEST: // Left
			rowSelector = 3;
			break;
		}
		TheTextureManager::Instance()->drawFrame("ghost", getPosition().x, getPosition().y, 64, 64, rowSelector, frameSelector, TheGame::Instance()->getRenderer());
		break;
	case 3: // Boss
		frameSelector = frameTimer / 10;
		if (!isInvul || invFrame % 10 > 5)
		{
			switch (getDirection())
			{
			case NORTH: // Up
				rowSelector = 1;
				break;
			case SOUTH: // Down
				rowSelector = 2;
				break;
			case EAST: // Right
				rowSelector = 4;
				break;
			case WEST: // Left
				rowSelector = 3;
				break;
			}
			TheTextureManager::Instance()->drawFrame("boss", getPosition().x, getPosition().y, 64, 64, rowSelector, frameSelector, TheGame::Instance()->getRenderer());
		}
		break;
	case 4: // Key Snail
		switch (getDirection())
		{
		case NORTH: // Up
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyUp", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyUp", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case SOUTH: // Down
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyDn", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyDn", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case EAST: // Right
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyRt", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyRt", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		case WEST: // Left
			if (frameTimer > frameTimerMid)
			{
				TheTextureManager::Instance()->drawFrame("enemyLt", getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			}
			else
			{
				TheTextureManager::Instance()->drawFrame("enemyLt", getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			}
			break;
		}
		break;
	}

}

void Enemy::update()
{
	if (getIsActive())
	{
		frameTimer++;
		if (frameTimer >= frameTimerMax)
		{
			frameTimer = 0;
		}
		// If colliding, change direction
		if (getIsColliding())
		{
			changeDirection();
			setIsColliding(false);
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
		
		wander();
	}

}

void Enemy::clean()
{

}

// On spawn, will choose a random direction to move in
// Upon hitting a wall, will choose a different direction to move in
void Enemy::wander()
{
	setPreviousPosition(getPosition());
	switch (currentDirection)
	{
	case NORTH: // Subtract y
		setPosition(glm::vec2(getPosition().x, getPosition().y - getVelocity().y));
		break;
	case EAST: // Add x
		setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y));
		break;
	case SOUTH: // Add y
		setPosition(glm::vec2(getPosition().x, getPosition().y + getVelocity().y));
		break;
	case WEST: // Subtract x
		setPosition(glm::vec2(getPosition().x - getVelocity().x, getPosition().y));
		break;
	default:
		break;
	}
	// BOUNDS CHECK
	if (getPosition().y <= 210) // Top of screen
	{
		setPosition(glm::vec2(getPosition().x, 210));
		changeDirection();
	}
	if (getPosition().y >= (978 - getHeight())) // Bottom of screen
	{
		setPosition(glm::vec2(getPosition().x, (978 - getHeight())));
		changeDirection();
	}
	if (getPosition().x <= 0) // Left of screen
	{
		setPosition(glm::vec2(0, getPosition().y));
		changeDirection();
	}
	if (getPosition().x >= (1280 - getWidth())) // Right of screen
	{
		setPosition(glm::vec2((1280 - getWidth()), getPosition().y));
		changeDirection();
	}
}

void Enemy::randomizeDirection()
{
	int temp = rand() % 4;
	switch (temp)
	{
	case 0:
		currentDirection = NORTH;
		break;
	case 1:
		currentDirection = EAST;
		break;
	case 2:
		currentDirection = SOUTH;
		break;
	case 3:
		currentDirection = WEST;
		break;
	default:
		currentDirection = NORTH;
		break;
	}
}

void Enemy::changeDirection()
{
	Direction tempDirection = currentDirection;
	while (tempDirection == currentDirection)
	{
		int temp = rand() % 4;
		switch (temp)
		{
		case 0:
			currentDirection = NORTH;
			break;
		case 1:
			currentDirection = EAST;
			break;
		case 2:
			currentDirection = SOUTH;
			break;
		case 3:
			currentDirection = WEST;
			break;
		default:
			currentDirection = NORTH;
			break;
		}
	}
}

Direction Enemy::getDirection()
{
	return currentDirection;
}
