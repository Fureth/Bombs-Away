#pragma once
#ifndef __Wall__
#define __Wall__

#include "GameObject.h"
#include "TextureManager.h"

class Wall : public GameObject {
public:
    Wall();
	Wall(int xPos, int yPos);
    ~Wall();

    // Draw the object
    void draw();

    // Update the object
    void update();

    // remove anything that needs to be deleted
    void clean();

	void setDestruction(bool status);
	bool getDestruction();

	int getX();
	int getY();

private:
    bool isDestroyed = false;
	int xPos, yPos;
    
};


#endif /* defined (__Wall__) */