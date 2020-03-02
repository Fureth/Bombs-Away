#pragma once
#ifndef __Powerup__
#define __Powerup__

#include "GameObject.h"
#include "TextureManager.h"


class Powerup : public GameObject {
public:
	Powerup(int powerupType);
	//Powerup(int xPos, int yPos, int wallType);
	~Powerup();

	// Draw the object
	void draw();

	// Update the object
	void update();

	// remove anything that needs to be deleted
	void clean();

	bool getCollected();
	void setCollected();
	
private:
	bool isCollected = false;

};


#endif /* defined (__Powerup__) */