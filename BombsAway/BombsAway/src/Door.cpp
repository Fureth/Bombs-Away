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
Door::Door(int xPos, int yPos, int wallType)
{
    TheTextureManager::Instance()->load("../Assets/textures/wallsanddoor.png", "wallsanddoor", TheGame::Instance()->getRenderer());

    this->xPos = xPos;
    this->yPos = yPos;
    this->currentHealth = wallType;

    glm::vec2 size = glm::vec2(64, 64);
    setWidth(size.x);
    setHeight(size.y);
    setIsColliding(false);
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
    //if (getIsColliding())
    //{
    //    setIsColliding(false);
    //    setDestruction(true);
    //}
}

void Door::clean()
{
}
