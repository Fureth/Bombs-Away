#include "Map.h"
#include "Game.h"
#include "TextureManager.h"


Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(int arr[MAP_HEIGHT][MAP_WIDTH])
{
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			currentMap[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type;
	Wall* newWall;
	Enemy* newEnemy;
	Powerup* newPowerup;
    Door* newDoor;
	Hole* newHole;


	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			type = currentMap[row][column];
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0: // Empty space
				break;
			case 1: // Basic wall
				newWall = new Wall(column, row, 2);
				newWall->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getWallVector()->push_back(newWall);
				newWall = nullptr;
				break;
			case 2: // Unbreakable wall
				newWall = new Wall(column, row, 1);
				newWall->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getWallVector()->push_back(newWall);
				newWall = nullptr;
				break;
            case 3: // Door
                newDoor = new Door(column, row, 0);
                newDoor->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
                TheGame::Instance()->getDoorVector()->push_back(newDoor);
                newDoor = nullptr;
                break;
			case 4: // Wall with health
				// Make wall
				newWall = new Wall(column, row, 2);
				newWall->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getWallVector()->push_back(newWall);
				newWall = nullptr;
				// Make health
				newPowerup = new Powerup(0);
				newPowerup->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getPowerupVector()->push_back(newPowerup);
				newPowerup = nullptr;
				break;
			case 5: // Wall with key
				// Make wall
				newWall = new Wall(column, row, 2);
				newWall->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getWallVector()->push_back(newWall);
				newWall = nullptr;
				// Make key
				newPowerup = new Powerup(1);
				newPowerup->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getPowerupVector()->push_back(newPowerup);
				newPowerup = nullptr;
				break;
			case 6: // Health on floor
				newPowerup = new Powerup(0);
				newPowerup->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getPowerupVector()->push_back(newPowerup);
				newPowerup = nullptr;
				break;
<<<<<<< HEAD
<<<<<<< HEAD
=======
			case 7:
				newPowerup = new Powerup(2);
				newPowerup->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getPowerupVector()->push_back(newPowerup);
				newPowerup = nullptr;
				break;
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> b839997980093adeb310aba82ba329fc2aa93d91
>>>>>>> master
			case 8: // Enemy A
				newEnemy = new Enemy(glm::vec2(64 * column, 210 + (64 * row)));
=======
			case 7:
				newPowerup = new Powerup(2);
				newPowerup->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getPowerupVector()->push_back(newPowerup);
				newPowerup = nullptr;
				break;
			case 8: // Snail
				newEnemy = new Enemy(glm::vec2(64 * column, 210 + (64 * row)), 1);
>>>>>>> dc3582c195962cae77a3339080af0a0c60d66708
				TheGame::Instance()->getEnemyVector()->push_back(newEnemy);
				newEnemy = nullptr;
				break;
			case 9: // Player
				TheGame::Instance()->getPlayerObject()->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				break;
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> b839997980093adeb310aba82ba329fc2aa93d91
>>>>>>> master
			case 10: // Holes
				newHole = new Hole(column, row);
				newHole->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getHoleVector()->push_back(newHole);
				newHole = nullptr;
				break;
<<<<<<< HEAD
			case 11: // Ghost Samurai
				newEnemy = new Enemy(glm::vec2(64 * column, 210 + (64 * row)), 2);
				TheGame::Instance()->getEnemyVector()->push_back(newEnemy);
				newEnemy = nullptr;
				break;
			case 12: // Boss
				newEnemy = new Enemy(glm::vec2(64 * column, 210 + (64 * row)), 3);
				TheGame::Instance()->getEnemyVector()->push_back(newEnemy);
				newEnemy = nullptr;
				break;
>>>>>>> dc3582c195962cae77a3339080af0a0c60d66708
=======
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> b839997980093adeb310aba82ba329fc2aa93d91
>>>>>>> master
			default:
				break;

			}
		}
	}
}

