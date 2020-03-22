#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(glm::vec2 startPos, int enemyType)
{
	//TheTextureManager::Instance()->load("../Assets/textures/enemy.png", "enemy", TheGame::Instance()->getRenderer());
	// Snail enemy textures
	TheTextureManager::Instance()->load("../Assets/textures/walk-back.png", "snailUp", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-right.png", "snailRight", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-front.png", "snailDown", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/walk-left.png", "snailLeft", TheGame::Instance()->getRenderer());
	// Ghost Samurai texture
	TheTextureManager::Instance()->load("../Assets/textures/ghostSamurai.png", "ghostSamurai", TheGame::Instance()->getRenderer());
	// Boss texture
	TheTextureManager::Instance()->load("../Assets/textures/boss.png", "boss", TheGame::Instance()->getRenderer());
	setPosition(startPos);
	setPreviousPosition(getPosition());

	//glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy");
	glm::vec2 size = glm::vec2(64, 64);
	//setVelocity(glm::vec2(2, 2));
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(ENEMY);
	randomizeDirection();
	currentHealth = 1;
	this->enemyType = enemyType;
	switch (enemyType)
	{
	case 1: // Snail
		enemySpeed = 1;
		break;
	case 2: // Ghost Samurai
		enemySpeed = 4;
		break;
	case 3: // Boss
		enemySpeed = 2;
		currentHealth = 2;
		break;
	}
	setVelocity(glm::vec2(enemySpeed, enemySpeed));
	invFrameMax = 120;
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	//TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, 64, 64, TheGame::Instance()->getRenderer());
	int frameSelector = 0;
	int rowSelector = 1;
	switch(enemyType)
	{
	case 1: // Snail
		switch (getDirection())
		{
		case NORTH:
			textureSelect = "snailUp";
			break;
		case SOUTH:
			textureSelect = "snailDown";
			break;
		case WEST:
			textureSelect = "snailLeft";
			break;
		case EAST:
			textureSelect = "snailRight";
			break;
		}
		frameSelector = roamTimer / 20;
		switch (frameSelector)
		{
		case 0:
			TheTextureManager::Instance()->drawFrame(textureSelect, getPosition().x, getPosition().y, 64, 64, 1, 0, TheGame::Instance()->getRenderer());
			break;
		case 1:
			TheTextureManager::Instance()->drawFrame(textureSelect, getPosition().x, getPosition().y, 64, 64, 2, 0, TheGame::Instance()->getRenderer());
			break;
		default:
			break;
		}
		break;
	case 2: // Ghost Samurai
		switch (getDirection())
		{
		case NORTH:
			rowSelector = 1;
			break;
		case SOUTH:
			rowSelector = 2;
			break;
		case WEST:
			rowSelector = 3;
			break;
		case EAST:
			rowSelector = 4;
			break;
		default:
			rowSelector = 1;
			break;
		}
		frameSelector = roamTimer / 8;
		TheTextureManager::Instance()->drawFrame("ghostSamurai", getPosition().x, getPosition().y, 64, 64, rowSelector, frameSelector, TheGame::Instance()->getRenderer());
		break;
	case 3: // Boss
		switch (getDirection())
		{
		case NORTH:
			rowSelector = 1;
			break;
		case SOUTH:
			rowSelector = 2;
			break;
		case WEST:
			rowSelector = 3;
			break;
		case EAST:
			rowSelector = 4;
			break;
		default:
			rowSelector = 1;
			break;
		}
		frameSelector = roamTimer / 10;
		TheTextureManager::Instance()->drawFrame("boss", getPosition().x, getPosition().y, 64, 64, rowSelector, frameSelector, TheGame::Instance()->getRenderer());
		break;
	}

	
}

void Enemy::update()
{
	if (getIsActive())
	{
		// If colliding, change direction
		if (getIsColliding())
		{
			changeDirection();
			setIsColliding(false);
		}
		wander();
	}
	if (roamTimer < roamTimerMax)
	{
		roamTimer++;
	}
	else
	{
		roamTimer = 0;
	}
	if (isInvul)
	{
		invFrame++;
		if (invFrame >= invFrameMax)
		{
			invFrame = 0;
			isInvul = false;
		}
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
