#include "Game.h"
#include "Floor.h"

Floor::Floor(int xPos, int yPos)
{
    TheTextureManager::Instance()->load("../Assets/textures/whiteFloor.png", "floor", TheGame::Instance()->getRenderer());

    this->xPos = xPos;
    this->yPos = yPos;

    glm::vec2 size = glm::vec2(64, 64);
    setWidth(size.x);
    setHeight(size.y);
    //setIsColliding(false);
    setType(FLOOR);
}

Floor::~Floor()
{
}

void Floor::draw()
{
    TheTextureManager::Instance()->drawFrame("floor", getPosition().x, getPosition().y, 64, 64, 1, 1, TheGame::Instance()->getRenderer());
}

void Floor::update()
{

}

void Floor::clean()
{
}


int Floor::getX()
{
    return xPos;
}

int Floor::getY()
{
    return yPos;
}
