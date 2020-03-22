#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Bomb.h"
#include "Direction.h"

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
	bool getThrow();
	void setThrow(bool enable);
	const int m_iPlayerSpeed = 4;
	bool spaceDown = false;

	// Health functions
	int getHealth();
	void changeHealth(bool lifeUp);
	
private:
	//Timer variables for walking animations
	const int walkTimerMax = 40;
	int walkTimer = 0;
	
	const int deathTimerMax = 90;
	int deathTimer = 0;

	const int throwTimerMax = 90;
	int throwTimer = 0;

    bool requestBomb = false; // This may be unneeded due to refactoring of Game.cpp
	bool throwableBomb = false;

	Direction playerFacing = SOUTH;
};


#endif /* defined (__Player__) */