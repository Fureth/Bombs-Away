#pragma once
#ifndef __Hole__
#define __Hole__

#include "GameObject.h"
#include "TextureManager.h"

class Hole : public GameObject {
public:
	Hole();
	Hole(int xPos, int yPos);
	~Hole();

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