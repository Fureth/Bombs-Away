#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Bomb.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	
	// Draw the object
	void draw();

	// Update the object
	void update();

	// remove anything that needs to be deleted
	void clean();

    bool getRequest();
    void setRequest(bool request);
	const int m_iPlayerSpeed = 4;

	
	
private:
	
    bool requestBomb = false; // This may be unneeded due to refactoring of Game.cpp
	
};


#endif /* defined (__Player__) */