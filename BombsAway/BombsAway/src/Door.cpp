#include "Door.h"
#include "Game.h"

Door::Door()
{
    TheTextureManager::Instance()->load("../Assets/textures/wallsanddoor.png", "wallsanddoor", TheGame::Instance()->getRenderer());

    glm::vec2 size = TheTextureManager::Instance()->getTextureSize("wall");
    setWidth(size.x);
    setHeight(size.y);
    setIsColliding(false);
    setType(GameObjectType::DOOR);
}

// Health indicates wall types: 0 = door, 1 = unbreakable, 2 = breakable
// 4 Unlock types:
// 1 = unlock key, proceed next level
// 2 = unlock key, switch level layout (must stay unlocked)
// 3 = unlock enemy death, proceed next level
// 4 = unlock key, remove said door to unblock path
// 1 "Dull" type:
// 5 = do nothing, pure aesthetic
Door::Door(int xPos, int yPos, int wallType, int unlockType)
{
    TheTextureManager::Instance()->load("../Assets/textures/wallsanddoor.png", "wallsanddoor", TheGame::Instance()->getRenderer());

    this->xPos = xPos;
    this->yPos = yPos;
    this->currentHealth = wallType;

    glm::vec2 size = glm::vec2(64, 64);
    setWidth(size.x);
    setHeight(size.y);
    setIsColliding(false);
	doorType = unlockType;
    setType(GameObjectType::DOOR);
}

Door::~Door()
{
}

void Door::draw()
{
    if (!isDestroyed)
    {
        TheTextureManager::Instance()->drawFrame("wallsanddoor", getPosition().x, getPosition().y, 64, 64, this->currentHealth + 1, 0, TheGame::Instance()->getRenderer());
    }
}

void Door::update()
{
	switch (doorType)
	{
	case 1: // Go to next level if key obtained
		if (Game::Instance()->getPlayerObject()->getKey())
		{
			Game::Instance()->GetFSM().pushState(new WinState);
		}
		break;
	case 2: // Transition based on level if key obtained
		if (TheGame::Instance()->getPlayerObject()->getKey())
		{
			switch (TheGame::Instance()->getMapInt())
			{
			case 1:
				TheGame::Instance()->setActiveMap(2);
				break;
			case 2:
				TheGame::Instance()->setActiveMap(1);
				break;
			default:
				break;
			}
			TheGame::Instance()->clearVectors(); // Clear map-specific vectors
			TheGame::Instance()->getActiveMap()->DrawMap(); // Re-populate map-specific vectors
		}
		break;
	case 3: // Go to next level if specific enemy killed
		if (TheGame::Instance()->getPlayerObject()->getKeyEnemy())
		{
			Game::Instance()->GetFSM().pushState(new WinState);
		}
		break;
	case 4: // Key removes door
		if (TheGame::Instance()->getPlayerObject()->getKeyTwo())
		{
			isDestroyed = true;
		}
		break;
	case 5: // Do nothing door
		break;
	default:
		break;
	}
}

void Door::clean()
{
}
