#pragma once
#ifndef __Floor__
#define __Floor__

#include "GameObject.h"
#include "TextureManager.h"

class Floor : public GameObject {
public:
    Floor();
    Floor(int xPos, int yPos);
    ~Floor();

    // Draw the object
    void draw();

    // Update the object
    void update();

    // remove anything that needs to be deleted
    void clean();

    //void setDestruction(bool status);
    //bool getDestruction();

    int getX();
    int getY();

private:
    //bool isDestroyed = false;
    int xPos, yPos;

};


#endif /* defined (__Hole__) */