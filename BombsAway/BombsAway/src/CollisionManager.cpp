#include "CollisionManager.h"
#include "TextureManager.h"
#include "Game.h"

// Not used currently, may refactor this code
int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::basicCollisionCheck(GameObject* object1, GameObject* object2)
{
	// Positions of objects 1 & 2
	//glm::vec2 P1 = object1->getPosition();
	//glm::vec2 P2 = object2->getPosition();

	// Unused, used for circular collision checks
	/*float halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5;
	float halfWidths = (object1->getWidth() + object2->getWidth()) * 0.5;*/

	// Object 1's rect wall positions
	float obj1Top = object1->getPosition().y;
	float obj1Bottom = object1->getPosition().y + object1->getHeight();
	float obj1Left = object1->getPosition().x;
	float obj1Right = object1->getPosition().x + object1->getWidth();

	// Object 2's rect wall positions
	float obj2Top = object2->getPosition().y;
	float obj2Bottom = object2->getPosition().y + object2->getHeight();
	float obj2Left = object2->getPosition().x;
	float obj2Right = object2->getPosition().x + object2->getWidth();

	

	// CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights) || CollisionManager::squaredDistance(P1, P2) < (halfWidths * halfWidths)

	// Player-based collisions
	if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left) && object1->getType() == PLAYER)
	{
		if (!object2->getIsColliding())
		{
			//object1->setIsColliding(true);
			object2->setIsColliding(true);

			glm::vec2 oldPosition = object1->getPreviousPosition();
			
			switch (object2->getType())
			{
			case WALL:
				//std::cout << "Collision with Wall!" << std::endl;
				
				object1->setPosition(oldPosition);
				// Y-position collision check
				if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_W))
				{
					object1->setPosition(glm::vec2(object1->getPosition().x, object1->getPosition().y - object1->getVelocity().y));
					float obj1Top = object1->getPosition().y;
					float obj1Bottom = object1->getPosition().y + object1->getHeight();
					float obj1Left = object1->getPosition().x;
					float obj1Right = object1->getPosition().x + object1->getWidth();
					if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
					{
						object1->setPosition(oldPosition);
					}
					if (object1->getPosition().y <= 210) // Top of screen
					{
						object1->setPosition(glm::vec2(object1->getPosition().x, 210));
					}
				}
				if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_S))
				{
					object1->setPosition(glm::vec2(object1->getPosition().x, object1->getPosition().y + object1->getVelocity().y));
					float obj1Top = object1->getPosition().y;
					float obj1Bottom = object1->getPosition().y + object1->getHeight();
					float obj1Left = object1->getPosition().x;
					float obj1Right = object1->getPosition().x + object1->getWidth();
					if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
					{
						object1->setPosition(oldPosition);
					}
					if (object1->getPosition().y >= (978 - object1->getHeight())) // Bottom of screen minus player height
					{
						object1->setPosition(glm::vec2(object1->getPosition().x, (978 - object1->getHeight())));
					}
				}

				object1->setPreviousPosition(object1->getPosition());
				oldPosition = object1->getPreviousPosition();
				
				// X-position collision check
				if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_A))
				{
					object1->setPosition(glm::vec2(object1->getPosition().x - object1->getVelocity().x, object1->getPosition().y));
					float obj1Top = object1->getPosition().y;
					float obj1Bottom = object1->getPosition().y + object1->getHeight();
					float obj1Left = object1->getPosition().x;
					float obj1Right = object1->getPosition().x + object1->getWidth();
					if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
					{
						object1->setPosition(oldPosition);
					}
					if (object1->getPosition().x <= 0) // Left side of screen
					{
						object1->setPosition(glm::vec2(0, object1->getPosition().y));
					}
				}
				if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_D))
				{
					object1->setPosition(glm::vec2(object1->getPosition().x + object1->getVelocity().x, object1->getPosition().y));
					float obj1Top = object1->getPosition().y;
					float obj1Bottom = object1->getPosition().y + object1->getHeight();
					float obj1Left = object1->getPosition().x;
					float obj1Right = object1->getPosition().x + object1->getWidth();
					if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
					{
						object1->setPosition(oldPosition);
					}
					if (object1->getPosition().x >= (1280 - object1->getWidth())) // Right side of screen minus player width
					{
						object1->setPosition(glm::vec2((1280 - object1->getWidth()), object1->getPosition().y));
					}
				}
				object1->setPreviousPosition(object1->getPosition());
				object2->setIsColliding(false);
				break;
			case BOMB:
				std::cout << "Collision with Bomb!" << std::endl;
				break;
			case ENEMY:
				std::cout << "Collision with Enemy!" << std::endl;
				if (object1->getType() == PLAYER && !object1->isInvul)
				{
					object1->changeHealth(false);
					object1->isInvul = true;
				}
				break;
			case POWERUP:
				std::cout << "Collected powerup!\n";
				object2->setIsColliding(false);
				break;
			default:
				std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}

	// Bomb explosion-based collisions
	if (object1->getType() == EXPLOSION)
	{
		// Set explosion 'radius'
		float obj1Top = object1->getPosition().y;
		float obj1Bottom = object1->getPosition().y + object1->getHeight();
		float obj1Left = object1->getPosition().x;
		float obj1Right = object1->getPosition().x + object1->getWidth();

		if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
		{
			switch (object2->getType())
			{
			case WALL:
				if (object2->getHealth() == 2)
				{
					std::cout << "Explosion on wall!" << std::endl;
					object2->setIsColliding(true);
				}
				break;
			case PLAYER:
				if (object2->getIsActive() &&  !object2->isInvul)
				{
					std::cout << "You take damage!" << std::endl;
					object2->changeHealth(false);
					object2->isInvul = true;
				}
				break;
            case ENEMY:
				if (!object2->isInvul)
				{
					object2->currentHealth -= 1;
					object2->isInvul = true;
				}
				if (object2->currentHealth == 0)
				{
					std::cout << "Enemy dies!" << std::endl;
					object2->setIsActive(false);
				}
                break;
			default:
				std::cout << "Explosion on unknown type!" << std::endl;
				break;
			}
		}
	}

	// Bomb based collisions
	if (object1->getType() == BOMB)
	{
		if (!(obj1Top >= obj2Bottom || obj1Bottom <= obj2Top || obj1Left >= obj2Right || obj1Right <= obj2Left))
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::tileCollisionCheck(GameObject* object, int tileMap[12][20])
{
	int objLeft = (object->getPosition().x ) / 64;
	int objRight = (object->getPosition().x + object->getWidth() - 1) / 64;
	int objTop = (object->getPosition().y - 210) / 64;
	int objBottom = (object->getPosition().y + object->getHeight() - 211) / 64;

	if (objLeft < 0)
	{
		objLeft = 0;
	}
	if (objRight > WINDOW_WIDTH/64)
	{
		objRight = WINDOW_WIDTH/64;
	}
	if (objTop < 0)
	{
		objTop = 0;
	}
	if (objBottom > (WINDOW_HEIGHT - 210) / 64)
	{
		objBottom = (WINDOW_HEIGHT - 210) / 64;
	}

	glm::vec2 oldPosition = object->getPreviousPosition();
	
	for (int i = objLeft; i <= objRight; i++)
	{
		for (int j = objTop; j <= objBottom; j++)
		{
			int tileType = tileMap[j][i];
			if (Game::Instance()->checkForKeystroke(SDL_SCANCODE_F))
				std::cout << i << " " << j << std::endl;
			if (tileType == 1 || tileType == 2 || tileType == 3 || tileType == 4 || tileType == 5 || tileType == 10) // 1, 2, 4, 5 = Wall, 3 = Door, 10 = Hole
			{
				//std::cout << "Collision with Wall!" << std::endl;
				if (object->getType() == ENEMY)
				{
					object->setPosition(object->getPreviousPosition());
				}
                //if (tileType == DOOR)
                //{
                //    Game::Instance()->GetFSM().pushState(new WinState());
                //}
				return true;
			}
			
		}
	}
	return false;
}

bool CollisionManager::playerCollisionMovement(GameObject* object, int tileMap[12][20])
{
	glm::vec2 oldPosition = object->getPreviousPosition();
	object->setPosition(oldPosition);

	// Y-position check
	if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_W))
	{
		object->setPosition(glm::vec2(object->getPosition().x, object->getPosition().y - object->getVelocity().y));
		if (tileCollisionCheck(object, tileMap))
		{
			object->setPosition(oldPosition);
		}
		if (object->getPosition().y <= 210) // Top of screen
		{
			object->setPosition(glm::vec2(object->getPosition().x, 210));
		}
	}
	if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_S))
	{
		object->setPosition(glm::vec2(object->getPosition().x, object->getPosition().y + object->getVelocity().y));
		if (tileCollisionCheck(object, tileMap))
		{
			object->setPosition(oldPosition);
		}
		if (object->getPosition().y >= (978 - object->getHeight())) // Bottom of screen
		{
			object->setPosition(glm::vec2(object->getPosition().x, (978 - object->getHeight())));
		}
	}

	// Change previous position based on y-position results
	object->setPreviousPosition(object->getPosition());
	oldPosition = object->getPreviousPosition();
	
	// X-position check
	if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_A))
	{
		object->setPosition(glm::vec2(object->getPosition().x - object->getVelocity().x, object->getPosition().y));
		if (tileCollisionCheck(object, tileMap))
		{
			object->setPosition(oldPosition);
		}
		if (object->getPosition().x <= 0) // Left of screen
		{
			object->setPosition(glm::vec2(0, object->getPosition().y));
		}
	}
	if (TheGame::Instance()->checkForKeystroke(SDL_SCANCODE_D))
	{
		object->setPosition(glm::vec2(object->getPosition().x + object->getVelocity().x, object->getPosition().y));
		if (tileCollisionCheck(object, tileMap))
		{
			object->setPosition(oldPosition);
		}
		if (object->getPosition().x >= (1280 - object->getWidth())) // Right of screen
		{
			object->setPosition(glm::vec2((1280 - object->getWidth()), object->getPosition().y));
		}
	}
	return false;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
