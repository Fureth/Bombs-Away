#pragma once
#ifndef __Door__
#define __Door__

#include "GameObject.h"
#include "TextureManager.h"

class Door : public GameObject {
public:
    Door();
    Door(int xPos, int yPos, int wallType, int unlockType);
    ~Door();

    // Draw the object
    void draw();

    // Update the object
    void update();

    // remove anything that needs to be deleted
    void clean();

    //void setDestruction(bool status);
    //bool getDestruction();

    //int getX();
    //int getY();
    int xPos, yPos;
	int doorType;
	bool unlocked = false;

private:
    bool isDestroyed = false;
    

};


#endif /* defined (__Door__) */
