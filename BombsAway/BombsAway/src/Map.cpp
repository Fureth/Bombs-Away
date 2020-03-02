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
				newWall = new Wall(column, row);
				newWall->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getWallVector()->push_back(newWall);
				newWall = nullptr;
				break;
			case 2: // Unbreakable wall
				break;
			case 8: // Enemy A
				newEnemy = new Enemy(glm::vec2(64 * column, 210 + (64 * row)));
				TheGame::Instance()->getEnemyVector()->push_back(newEnemy);
				newEnemy = nullptr;
				break;
			case 9: // Player
				TheGame::Instance()->getPlayerObject()->setPosition(glm::vec2(64 * column, 210 + (64 * row)));
				break;
			default:
				break;

			}
		}
	}
}

